/***************************************************************************
* Klassenname LoadGame
* Date
* Autor(en) Hein, Köhler, Meister
*
* Diese Klasse ist eine Unterklasse des BasicState und lädt den Spielstand
* eines Spielers.
**************************************************************************/
#include "LoadGame.h"

//Konstruktoren (Definition)
LoadGame::LoadGame(){

}

LoadGame::LoadGame(sf::RenderWindow *pRenderWindow, sf::Event *pEvent,
    GUIManager *pGUI) :mpStateGUIManager(pGUI){
  gpBasicStateWindow = pRenderWindow;
  gpBasicStateEvent  = pEvent;

  //Initialisierung Text
  if (!mLoadGameFont.loadFromFile("Data/Font/04B_30__.ttf")){
    std::string error("Could not load Font for mLoadGameFont from: ");
    error.append("Data/Font/04B_30__.ttf");
    error.append("\n");
    error.append("Check data path and image file formats!");
    throw std::exception(error.c_str());
  }

  //Text Load Game
  mLoadGameText[0].setFont(mLoadGameFont);
  mLoadGameText[0].setCharacterSize(50);
  mLoadGameText[0].setStyle(sf::Text::Bold | sf::Text::Underlined);
  mLoadGameText[0].setPosition(20,40);

  mLoadGameText[1].setFont(mLoadGameFont);
  mLoadGameText[1].setCharacterSize(24);

  mLoadGameText[2].setFont(mLoadGameFont);
  mLoadGameText[2].setCharacterSize(24);
  mLoadGameText[2].setPosition(20, 110);
}

//Destruktor (Definition)
LoadGame::~LoadGame(){

  mpStateGUIManager->deleteGUIObjects();
  pContinueLevelTwo = nullptr;
  pContinueLevelThree = nullptr;
  pBackButton = nullptr;
  pLoadGame = nullptr;
  pRequestPlayerName = nullptr;

  delete mpSaveGame;
  delete mpLoadedGame;
  delete mpAchievements;
  delete mpMainSettings;

  mpSaveGame         = nullptr;
  mpLoadedGame       = nullptr;
  mpAchievements     = nullptr;
  mpMainSettings     = nullptr;

  delete mpMusicMenu;
  mpMusicMenu = nullptr;

}

//Klassenmethoden (Definition)
//Grundfunktionen
void LoadGame::handleEvents(){

  //GUIObject Funktionen des LoadGame States
  //"Click"->Back To Menu
  if (mpStateGUIManager->getGUIObject("LoadGame/BackToMenu")->getIsClickedGUIObject() == true){
    setNextState("State/Menu");
  }

  //Abrufen des Spielstands über die jeweilige .txt-Datei
  if (mpStateGUIManager->getGUIObject("LoadGame/LoadGame")->getIsClickedGUIObject() == true){
    loadSaveGame();

    /*Je nachdem, welches Level im SaveGame gespeichert wurde, wird der entsprechende Button
      zum nächsten Level initialisiert*/
    //SolvedLevel = LevelOne -> NextLevel = LevelTwo
    if (mpLoadedGame->getLevel() == 1){
      std::string sContinueLevelTwo = "";

      if (mLanguageOptions == 1){
        sContinueLevelTwo = "Level 2 weiter";
      }
      else if (mLanguageOptions == 2){
        sContinueLevelTwo = "Continue Level 2";
      }
      else if (mLanguageOptions == 3){
        sContinueLevelTwo = "Continuer Niveau 2";
      }
      //GUI (ContinueLevelTwo) initialisieren
      pContinueLevelTwo = new Button("LoadGame/ContinueLevelTwo", sf::Vector2f(100, 100),
          sf::Vector2f(1, 1), "Data/Textures/GUI/Button/ButtonTexture.png", sContinueLevelTwo);

      //Button ausrichten
      pContinueLevelTwo->setPositionGUIObject(sf::Vector2f(350.f + pContinueLevelTwo->
          getSpriteGUIObject().getTextureRect().width / 4, 530.f));

      //Button registrieren
      mpStateGUIManager->registerGUIObject(pContinueLevelTwo);
    }

    //SolvedLevel = LevelTwo -> NextLevel = LevelThree
    if (mpLoadedGame->getLevel() == 2){
      std::string sContinueLevelThree = "";

      if (mLanguageOptions == 1){
        sContinueLevelThree = "Level 3 weiter";
      }
      else if (mLanguageOptions == 2){
        sContinueLevelThree = "Continue Level 3";
      }
      else if (mLanguageOptions == 3){
        sContinueLevelThree = "Continuer Niveau 3";
      }

      //GUI (ContinueLevelThree) initialisieren
      pContinueLevelThree = new Button("LoadGame/ContinueLevelThree", sf::Vector2f(100, 100),
          sf::Vector2f(1, 1), "Data/Textures/GUI/Button/ButtonTexture.png", sContinueLevelThree);

      //Button ausrichten
      pContinueLevelThree->setPositionGUIObject(sf::Vector2f(350.f + pContinueLevelThree->
          getSpriteGUIObject().getTextureRect().width / 4, 530.f));

      //Button registrieren
      mpStateGUIManager->registerGUIObject(pContinueLevelThree);
    }
  }

  //In SaveGame gespeicherte Achievements laden und mit LevelTwo fortsetzen
  if (mpStateGUIManager->getGUIObject("LoadGame/ContinueLevelTwo")->
      getIsClickedGUIObject() == true){
    loadReachedAchievements();
    setNextState("State/LevelTwo");
  }

  //In SaveGame gespeicherte Achievements laden und mit LevelThree fortsetzen
  if (mpStateGUIManager->getGUIObject("LoadGame/ContinueLevelThree")->
    getIsClickedGUIObject() == true){
    loadReachedAchievements();
    setNextState("State/LevelThree");
  }
}

void LoadGame::update(float fFrametime){

}

void LoadGame::render(){
  gpBasicStateWindow->draw(mLoadGameText[0]);
  gpBasicStateWindow->draw(mLoadGameText[1]);
  gpBasicStateWindow->draw(mLoadGameText[2]);
}

//Spezifische Funktionen
void LoadGame::enterState(){

  //MainSettings laden (bei Programmstart mit Defaultwerten, sonst bereits gespeicherte
  mpMainSettings = new MainSettings();
  *mpMainSettings = BinaryData::readBinaryFile<MainSettings>("Data/Bin/Settings/mainsettings.bin");

  //Musik-Instanz initiieren
  mpMusicMenu = new sf::Music;
  if (!mpMusicMenu->openFromFile("Data/Sounds/Music/backgroundMenu.ogg")){
    std::string error("Could not load Music for mpMusicMenu from: ");
    error.append("Data/Sounds/Music/backgroundMenu.ogg");
    error.append("\n");
    error.append("Check data path. Remember, that only wav, flac, ogg, mp3 are supported!");
    throw std::exception(error.c_str());
  }

  //Hintergrund-Musik
  //Lautstärke je nach geladenen MainSettings setzen
  mpMusicMenu->setVolume(mpMainSettings->getMusicVolume());
  mpMusicMenu->setLoop(true);

  sf::SoundSource::Status musicStatus = mpMusicMenu->getStatus();
  if (musicStatus == sf::SoundSource::Status::Paused &&
    mpMainSettings->getIsMusicEnabled() == true){
    mpMusicMenu->play();
  }
  else if (musicStatus == sf::SoundSource::Status::Playing &&
    mpMainSettings->getIsMusicEnabled() == false){
    mpMusicMenu->stop();
  }
  else if (musicStatus == sf::SoundSource::Status::Stopped
    && mpMainSettings->getIsMusicEnabled() == true){
    mpMusicMenu->play();
  }

  //Spracheinstellungen
  mLanguageOptions = mpMainSettings->getLanguage();
  std::string sDescriptionLoadGame = "";
  std::string sBackButtonString = "";
  std::string sLoadGameString = "";
  std::string sPlayerName = "";

  
  if (mLanguageOptions == 1){
    mLoadGameText[0].setString("Spiel laden");
    mLoadGameText[1].setPosition(200.f, 360.f);
    mLoadGameText[1].setString("Gib bitte Deinen Namen ein: ");
    sDescriptionLoadGame.append("Wie man ein Spiel laedt: \n");
    sDescriptionLoadGame.append
        ("Um ein Spiel zu laden, schreibe bitte Deinen Namen \nin die angezeigte Textbox.\n");
    sDescriptionLoadGame.append
        ("Anschliessend druecke 'Lade Spiel' um Deine gespeicherten \nDaten zu laden.\n");
    sDescriptionLoadGame.append
      ("Eine Schaltflaeche, die Dich zu Deinem naechsten Level \nbringt, erscheint.");
    mLoadGameText[2].setString(sDescriptionLoadGame);

    sBackButtonString = "Hauptmenue";
    sLoadGameString = "Spiel laden";
    sPlayerName = "Spielername";
  }
  else if (mLanguageOptions == 2){
    mLoadGameText[0].setString("Load Game");
    mLoadGameText[1].setPosition(270.f, 360.f);
    mLoadGameText[1].setString("Enter Your Name: ");
    sDescriptionLoadGame.append("How to load a game: \n");
    sDescriptionLoadGame.append
        ("To load a game, please enter your name in \nthe shown textbox.\n");
    sDescriptionLoadGame.append
        ("Afterwards click 'Load Game' to load your \nsaved achievements.\n");
    sDescriptionLoadGame.append
        ("A button will appear, that leads you to your Level.");
    mLoadGameText[2].setString(sDescriptionLoadGame);


    sBackButtonString = "MainMenu";
    sLoadGameString = "Load Game";
    sPlayerName = "Player Name";
  }
  else if (mLanguageOptions == 3){
    mLoadGameText[0].setString("Chargement du jeu");
    mLoadGameText[1].setPosition(270.f, 360.f);
    mLoadGameText[1].setString("Entrez votre nom: ");
    sDescriptionLoadGame.append("Comment charger un jeu: \n");
    sDescriptionLoadGame.append
      ("Pour charger un jeu, entrez votre nom dans la \nzone de texte affichee.\n");
    sDescriptionLoadGame.append
      ("Ensuite, cliquez sur 'Charger le jeu' pour charger \nvos realisations enregistrees.\n");
    sDescriptionLoadGame.append
      ("Un bouton apparaitra, qui vous menera a votre \nniveau.");
    mLoadGameText[2].setString(sDescriptionLoadGame);
    sBackButtonString = "Menu Principal";
    sLoadGameString = "Chargement Du Jeu";
    sPlayerName = "Nom Du Joueu";
  }

  //GUI (Button) initialisieren
  pBackButton = new Button("LoadGame/BackToMenu", sf::Vector2f(100, 100),
      sf::Vector2f(1, 1), "Data/Textures/GUI/Button/ButtonTexture.png", sBackButtonString);
  pLoadGame = new Button("LoadGame/LoadGame", sf::Vector2f(100, 100),
      sf::Vector2f(1, 1), "Data/Textures/GUI/Button/ButtonTexture.png", sLoadGameString);

  //Button ausrichten
  pBackButton->setPositionGUIObject(sf::Vector2f(222.f- pBackButton->getSpriteGUIObject().
      getTextureRect().width / 2, 530.f));
  pLoadGame->setPositionGUIObject(sf::Vector2f(350.f + pLoadGame->getSpriteGUIObject().
      getTextureRect().width/4, 530.f));

  //Button registrieren
  mpStateGUIManager->registerGUIObject(pBackButton);
  mpStateGUIManager->registerGUIObject(pLoadGame);

  //GUI (Textbox) initialisieren
  pRequestPlayerName = new Textbox("LoadGame/RequestPlayerName", sf::Vector2f(100, 100),
    sf::Vector2f(375.f, 50.f), sPlayerName);

  //Textbox ausrichten
  pRequestPlayerName->setTextboxPosition(sf::Vector2f(475.f - pLoadGame->getSpriteGUIObject().
      getTextureRect().width/2.f, 400.f));

  //Textbox registrieren
  mpStateGUIManager->registerGUIObject(pRequestPlayerName);
}

void LoadGame::leaveState(){

  mpStateGUIManager->deleteGUIObjects();
  pContinueLevelTwo   = nullptr;
  pContinueLevelThree = nullptr;
  pBackButton         = nullptr;
  pLoadGame           = nullptr;
  pRequestPlayerName  = nullptr;

  setNextState("");

  delete mpSaveGame;
  delete mpLoadedGame;
  delete mpAchievements;
  delete mpMainSettings;

  mpSaveGame = nullptr;
  mpLoadedGame = nullptr;
  mpAchievements = nullptr;
  mpMainSettings = nullptr;

  mpMusicMenu->stop();
  delete mpMusicMenu;
  mpMusicMenu = nullptr;
}

void LoadGame::loadSaveGame(){

  //Aktuellen Spielstand aus .txt Datei lesen/laden
  mpSaveGame = new Achievements();
  std::string sEnteredPlayerName;
  sEnteredPlayerName = mpStateGUIManager->getGUIObject("LoadGame/RequestPlayerName")
      ->getTextGUIObject().getString();
  
  //Verknüpfung des in LoadGame-Textbox eingegebenen Namens mit Dateipfad des gespeicherten Spiels
  std::string sNameSavedGame = "";
  sNameSavedGame.append("Data/SaveGame/");
  sNameSavedGame.append(sEnteredPlayerName);
  sNameSavedGame.append(".txt");
  FileHandler fhSaveGame(sNameSavedGame);
  Achievements *pReadSaveGame = fhSaveGame.readAchievements();

  mpLoadedGame = new Achievements();
  mpLoadedGame = fhSaveGame.readAchievements();
}

void LoadGame::loadReachedAchievements(){
  mpAchievements = new Achievements();

  FileHandler fhAchievements("Data/Achievements/achievements.txt");

  Achievements *pReadAchievements = fhAchievements.readAchievements();
  *mpAchievements = *pReadAchievements;
  mpAchievements->setLevel(mpLoadedGame->getLevel());
  mpAchievements->setPlayerName(mpLoadedGame->getPlayerName());
  mpAchievements->setReachedScorePlayer(mpLoadedGame->getReachedScorePlayer());

  fhAchievements.writeAchievements(mpAchievements);
}