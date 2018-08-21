/***************************************************************************
* Klassenname PrePlayState
* Date
* Autor(en) Hein, Köhler, Meister
*
* Diese Klasse ist eine Unterklasse des BasicState und ist der Zustand vor
* dem eigentlichen Spiel. Hier werden die Spieleinstellungen wie 
* ControlSettings, Spielername etc. verwaltet.
**************************************************************************/
#include "PrePlayState.h"
#include <iostream>

//Konstruktoren (Definition)
PrePlayState::PrePlayState(){

}

PrePlayState::PrePlayState(sf::RenderWindow *pRenderWindow, sf::Event *pEvent,
    GUIManager *pGUI):mpStateGUIManager(pGUI){
  gpBasicStateWindow = pRenderWindow;
  gpBasicStateEvent  = pEvent;

  //Initialisierung Text
  if (!mPreGameFont.loadFromFile("Data/Font/04B_30__.ttf")){
    std::string error("Could not load Font for mPreGameFont from: ");
    error.append("Data/Font/04B_30__.ttf");
    error.append("\n");
    error.append("Check data path and image file formats!");
    throw std::exception(error.c_str());
  }

  //Text PreGame Settings
  mPreGameText[0].setFont(mPreGameFont);
  mPreGameText[0].setCharacterSize(50);
  mPreGameText[0].setStyle(sf::Text::Bold | sf::Text::Underlined);

  mPreGameText[1].setFont(mPreGameFont);
  mPreGameText[1].setCharacterSize(24);
}

//Destruktor (Definition)
PrePlayState::~PrePlayState(){

  mpStateGUIManager->deleteGUIObjects();
  pBackButton = nullptr;
  pControlSettingsButton = nullptr;
  pStartButton = nullptr;
  pRequestPlayerName = nullptr;

  delete mpAchievements;
  delete mpMainSettings;

  mpAchievements    = nullptr;
  mpMainSettings    = nullptr;

  delete mpMusicMenu;
  mpMusicMenu = nullptr;

}

//Klassenmethoden (Definition)
//Grundfunktionen
void PrePlayState::handleEvents(){

  //GUIObject Funktionen des PrePlay States
  //"Click"->Back To Menu
  if (mpStateGUIManager->getGUIObject("PreGame/BackToMenu")->getIsClickedGUIObject() == true){
    setNextState("State/Menu");
  }

  //"Click"->ControlSettings
  if (mpStateGUIManager->getGUIObject("PreGame/ControlSettings")->getIsClickedGUIObject() == true){
    setNextState("State/ControlSettings");
  }

  //"Click"->"GameState" LevelOne
  if (mpStateGUIManager->getGUIObject("PreGame/StartGame")->getIsClickedGUIObject() == true){

    //Prüfen, ob Spielername eingegeben wurde bzw. die Textbox einen Wert enthält
    std::string sPlayerName = mpStateGUIManager->getGUIObject("PreGame/RequestPlayerName")
        ->getTextGUIObject().getString();
    if (sPlayerName != ""){

      //Bei Wechsel in State "LevelOne" wird Wert auf "1" gesetzt
      setLevel(1);

      //DefaultAchievements erstellen, sobald LevelOne gestartet wird
      createAchievements();

      delete mpAchievements;
      mpAchievements = nullptr;

      //Übergang State "LevelOne"
      setNextState("State/LevelOne");
    }
    //Falls Textbox keinen Wert enthält, erscheint Hinweis
    else{
      /*Erzeugung eines Schriftzugs, der als Prüfanzeige dient, sobald die Textbox
        (RequestPlayerName) einen leeren Wert besitzt*/
      mPreGameText[2].setFont(mPreGameFont);
      if (mLanguageOptions == 1){
        mPreGameText[2].setString("Bitte gib Deinen Namen ein!");
      }
      else if (mLanguageOptions == 2){
        mPreGameText[2].setString("Please Enter Your Name!");
      }
      else if (mLanguageOptions == 3){
        mPreGameText[2].setString("Entrez Votre Nom!");
      }

      mPreGameText[2].setCharacterSize(24);
      mPreGameText[2].setPosition(400.f + mpStateGUIManager->getGUIObject("PreGame/StartGame")
          ->getSpriteGUIObject().getTextureRect().width / 3.f - 20.f, 300.f + mpStateGUIManager->
          getGUIObject("PreGame/StartGame")->getSpriteGUIObject().getTextureRect().height + 75.f);
    }
  }

  //"Click"->Textbox(RequestPlayerName)
  /*Sobald die Textbox erneut aktiviert wurde, für eine erneute Eingabe des Spielernamens,
    soll die Prüfanzeige wieder auf "Null" gesetzt werden.*/
  if (mpStateGUIManager->getGUIObject("PreGame/RequestPlayerName")->getIsActiveGUIObject() == true){
    mPreGameText[2].setString("");
  }
}

void PrePlayState::update(float fFrametime){

}

void PrePlayState::render(){
  gpBasicStateWindow->draw(mPreGameText[0]);
  gpBasicStateWindow->draw(mPreGameText[1]);
  gpBasicStateWindow->draw(mPreGameText[2]);
}

//Setter
void PrePlayState::setLevel(int iLevel){
  mLevel = iLevel;
}

//Getter
int PrePlayState::getLevel(){
  return mLevel;
}

//Spezifische Funktionen
void PrePlayState::enterState(){
  
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
  std::string sButtonTexturePath = "";
  std::string sBackButtonString = "";
  std::string sControlSettings = "";
  std::string sStartString = "";
  std::string sPlayerNameString = "";

  if (mLanguageOptions == 1){
    mPreGameText[0].setString("PreGame Einstellungen");
    mPreGameText[0].setPosition(20, 40);
    mPreGameText[1].setString("Gib bitte Deinen Namen ein: ");
    mPreGameText[1].setPosition(200, 175);
    sButtonTexturePath = "Data/Textures/GUI/Button/ButtonTexture.png";
    sBackButtonString = "Hauptmenue";
    sControlSettings = "Steuerung";
    sStartString = "Start Level 1";
    sPlayerNameString = "Spielername";
  }
  else if (mLanguageOptions == 2){
    mPreGameText[0].setString("PreGame Settings");
    mPreGameText[0].setPosition(130, 40);
    mPreGameText[1].setString("Please Enter Your Name: ");
    mPreGameText[1].setPosition(220, 175);
    sButtonTexturePath = "Data/Textures/GUI/Button/ButtonTexture.png";
    sBackButtonString = "Main Menu";
    sControlSettings = "Control Settings";
    sStartString = "Start Level 1";
    sPlayerNameString = "Player Name";
  }
  else if (mLanguageOptions == 3){
    mPreGameText[0].setString("Parametres De Pre-Jeu");
    mPreGameText[0].setPosition(125, 40);
    mPreGameText[1].setString("Entrez Votre Nom: ");
    mPreGameText[1].setPosition(402, 175);
    sButtonTexturePath = "Data/Textures/GUI/Button/ButtonTextureFrench.png";
    sBackButtonString = "Menu Principal";
    sControlSettings = "Parametres De Controle";
    sStartString = "Commence Le Niveau Un";
    sPlayerNameString = "Nom Du Joueu";
  }

  //GUI (Button) initialisieren
  pBackButton = new Button("PreGame/BackToMenu", sf::Vector2f(100, 100),
      sf::Vector2f(1, 1), sButtonTexturePath, sBackButtonString);
  pControlSettingsButton = new Button("PreGame/ControlSettings", sf::Vector2f(100,100),
      sf::Vector2f(1, 1), sButtonTexturePath, sControlSettings);
  pStartButton = new Button("PreGame/StartGame", sf::Vector2f(100, 100),
      sf::Vector2f(1, 1), sButtonTexturePath, sStartString);

  //Button ausrichten
  if (mLanguageOptions == 1 || mLanguageOptions == 2){
    pBackButton->setPositionGUIObject(sf::Vector2f(222.f - pBackButton->getSpriteGUIObject().
        getTextureRect().width / 2.f, 530.f));
    pControlSettingsButton->setPositionGUIObject(sf::Vector2f(450.f - pControlSettingsButton->
        getSpriteGUIObject().getTextureRect().width / 2,385.f));
    pStartButton->setPositionGUIObject(sf::Vector2f(350.f + pStartButton->getSpriteGUIObject().
        getTextureRect().width / 4, 530.f));
  }
  else if (mLanguageOptions == 3){
    pBackButton->setPositionGUIObject(sf::Vector2f(284.5f - pBackButton->getSpriteGUIObject().
      getTextureRect().width / 2.f, 530.f));
    pControlSettingsButton->setPositionGUIObject(sf::Vector2f(565.625f - pControlSettingsButton->
      getSpriteGUIObject().getTextureRect().width / 2.f, 385.f));
    pStartButton->setPositionGUIObject(sf::Vector2f(443.75f + pStartButton->getSpriteGUIObject().
      getTextureRect().width / 4.f, 530.f));
  }

  //Button registrieren
  mpStateGUIManager->registerGUIObject(pBackButton);
  mpStateGUIManager->registerGUIObject(pControlSettingsButton);
  mpStateGUIManager->registerGUIObject(pStartButton);

  //GUI (Textbox) initialisieren
  pRequestPlayerName = new Textbox("PreGame/RequestPlayerName", sf::Vector2f(100, 100),
      sf::Vector2f(375, 50), sPlayerNameString);

  //Textbox ausrichten
  if (mLanguageOptions == 1){
    pRequestPlayerName->setTextboxPosition(sf::Vector2f(525.f - mPreGameText[1].getLocalBounds().
        width / 2.f, 230.f));
  }
  else if (mLanguageOptions == 2){
    pRequestPlayerName->setTextboxPosition(sf::Vector2f(505.f - mPreGameText[1].getLocalBounds().
      width / 2.f, 230.f));
  }
  else if (mLanguageOptions == 3){
    pRequestPlayerName->setTextboxPosition(sf::Vector2f(565.625f - mPreGameText[1].getLocalBounds().
      width / 2.f, 230.f));
  }
  
  //Textbox registrieren
  mpStateGUIManager->registerGUIObject(pRequestPlayerName);
}

void PrePlayState::leaveState(){
  mpStateGUIManager->deleteGUIObjects();
  pBackButton            = nullptr;
  pControlSettingsButton = nullptr;
  pStartButton           = nullptr;
  pRequestPlayerName     = nullptr;

  setNextState("");

  delete mpAchievements;
  delete mpMainSettings;

  mpAchievements = nullptr;
  mpMainSettings = nullptr;

  mpMusicMenu->stop();
  delete mpMusicMenu;
  mpMusicMenu = nullptr;

}

void PrePlayState::createAchievements(){

  //Standard- bzw. Default-Werte für Achievements Zwischenspeicher erstellen
  mpAchievements = new Achievements();
  FileHandler fhAchievements("Data/Achievements/achievements.txt");

  //Achievements mit Werten belegen
  mpAchievements->setLevel(mLevel);
  mpAchievements->setPlayerName(mpStateGUIManager->getGUIObject("PreGame/RequestPlayerName")->
      getTextGUIObject().getString());
  mpAchievements->setReachedScorePlayer(0);

  //Datei schreiben bzw. überschreiben
  fhAchievements.writeAchievements(mpAchievements);
}