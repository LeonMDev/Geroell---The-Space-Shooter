/***************************************************************************
* Klassenname LevelSolved
* Date
* Autor(en) Hein, Köhler, Meister
*
* Diese Klasse ist eine Unterklasse des BasicState und verwaltet den
* Zustand "Level Solved". Sie verwaltet die Speicherung des Spielstands,
* zeigt bisherige Achievements an und leitet entweder zum nächsten Level
* oder zurück zum Hauptmenü weiter.
**************************************************************************/
#include "LevelSolved.h"
#include <iostream>

//Konstruktor (Definition)
LevelSolved::LevelSolved(){

}

LevelSolved::LevelSolved(sf::RenderWindow *pRenderWindow, sf::Event *pStateEvent,
    GUIManager *pGUI) :mpStateGUIManager(pGUI){
  gpBasicStateWindow = pRenderWindow;
  gpBasicStateEvent  = pStateEvent;

  //Initialisierung von Text
  if (!mLevelSolvedFont.loadFromFile("Data/Font/04B_30__.ttf")){
    std::string error("Could not load Font for mLevelSolvedFont from: ");
    error.append("Data/Font/04B_30__.ttf");
    error.append("\n");
    error.append("Check data path and image file formats!");
    throw std::exception(error.c_str());
  }

  //Text Spielername
  mLevelSolvedText[0].setFont(mLevelSolvedFont);
  mLevelSolvedText[0].setCharacterSize(24);
  mLevelSolvedText[0].setPosition(20, 200);

  //Text erreichte Punkte
  mLevelSolvedText[1].setFont(mLevelSolvedFont);
  mLevelSolvedText[1].setCharacterSize(24);
  mLevelSolvedText[1].setPosition(20, 250);

  //Text erreichtes Level
  mLevelSolvedText[2].setFont(mLevelSolvedFont);
  mLevelSolvedText[2].setCharacterSize(24);
  mLevelSolvedText[2].setPosition(20, 300);
}

//Destruktor (Definition)
LevelSolved::~LevelSolved(){

  mpStateGUIManager->deleteGUIObjects();
  pBackButton = nullptr;
  pNextLevelThree = nullptr;
  pNextLevelTwo = nullptr;
  pSaveGame = nullptr;
  pHighScoreList = nullptr;

  delete mpAchievements;
  delete mpSaveGame;
  delete mpMainSettings;

  mpAchievements    = nullptr;
  mpSaveGame        = nullptr;
  mpMainSettings    = nullptr;

  delete mpMusicMenu;
  mpMusicMenu = nullptr;


}

//Klassenmethoden
//Grundfunktionen
void LevelSolved::handleEvents(){

  //MainButtons des States
  //"Click"->BackToMenu
  if (mpStateGUIManager->getGUIObject("LevelSolved/BackToMenu")->getIsClickedGUIObject() == true){
    setNextState("State/Menu");
  }

  //"Click"->SaveGame
  if (mpStateGUIManager->getGUIObject("LevelSolved/SaveGame")->getIsClickedGUIObject() == true){
    
    //Ermöglicht das Abspeichern des Spielstands zwischen den Leveln, in .txt-Datei
    saveGame();

    //Erzeugen eines Schriftzuges, der als Prüfanzeige dient, sobald der Spielstand gespeichert wurde
    mLevelSolvedText[3].setFont(mLevelSolvedFont);
    mLevelSolvedText[3].setCharacterSize(36);
    if (mLanguageOptions == 1){
      mLevelSolvedText[3].setPosition(65.f + mpStateGUIManager->getGUIObject("LevelSolved/SaveGame")
        ->getSpriteGUIObject().getTextureRect().width / 2.f, 570.f + mpStateGUIManager
        ->getGUIObject("LevelSolved/SaveGame")->getSpriteGUIObject().getTextureRect().height);
      mLevelSolvedText[3].setString("Gespeichert!");
    }
    else if (mLanguageOptions == 2){
      mLevelSolvedText[3].setPosition(155.f + mpStateGUIManager->getGUIObject("LevelSolved/SaveGame")
        ->getSpriteGUIObject().getTextureRect().width / 2.f, 570.f + mpStateGUIManager
        ->getGUIObject("LevelSolved/SaveGame")->getSpriteGUIObject().getTextureRect().height);
      mLevelSolvedText[3].setString("Saved!");
    }
    else if (mLanguageOptions == 3){
      mLevelSolvedText[3].setPosition(85.f + mpStateGUIManager->getGUIObject("LevelSolved/SaveGame")
        ->getSpriteGUIObject().getTextureRect().width / 2.f, 570.f + mpStateGUIManager
        ->getGUIObject("LevelSolved/SaveGame")->getSpriteGUIObject().getTextureRect().height);
      mLevelSolvedText[3].setString("Enregistre!");
    }
  }

  //Abrufen der Achievementsinformationen
  if (mpAchievements->getLevel() == 1){
    if (mpStateGUIManager->getGUIObject("LevelSolved/NextLevelTwo")->getIsClickedGUIObject() == true){
      setNextState("State/LevelTwo");
    }
  }

  if (mpAchievements->getLevel() == 2){
    if (mpStateGUIManager->getGUIObject("LevelSolved/NextLevelThree")->getIsClickedGUIObject() == true){
      setNextState("State/LevelThree");
    }
  }

  if (mpAchievements->getLevel() == 3){
    if (mpStateGUIManager->getGUIObject("LevelSolved/HighscoreList")->getIsClickedGUIObject() == true){
      setNextState("State/Highscore");
    }
  }
}

void LevelSolved::update(float fFrametime){

}

void LevelSolved::render(){
  gpBasicStateWindow->draw(mLevelSolvedText[0]);
  gpBasicStateWindow->draw(mLevelSolvedText[1]);
  gpBasicStateWindow->draw(mLevelSolvedText[2]);
  gpBasicStateWindow->draw(mLevelSolvedText[3]);
  gpBasicStateWindow->draw(mLevelSolvedText[4]);
  gpBasicStateWindow->draw(mLevelSolvedText[5]);
  gpBasicStateWindow->draw(mLevelSolvedText[6]);

  gpBasicStateWindow->draw(mAchievementsText[0]);
  gpBasicStateWindow->draw(mAchievementsText[1]);
  gpBasicStateWindow->draw(mAchievementsText[2]);
}

//Spezifische Funktionen
void LevelSolved::enterState(){
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
  std::string sBackButtonString = "";
  std::string sSaveApplyString = "";

  if (mLanguageOptions == 1){
    mLevelSolvedText[0].setString("Spielername: ");
    mLevelSolvedText[1].setString("Erreichte Punkte: ");
    mLevelSolvedText[2].setString("Beendetes Level: ");

    sBackButtonString = "Zurueck";
  }
  else if (mLanguageOptions == 2){
    mLevelSolvedText[0].setString("Player Name: ");
    mLevelSolvedText[1].setString("Achieved GameScore: ");
    mLevelSolvedText[2].setString("Solved Level: ");

    sBackButtonString = "Back";
  }
  else if (mLanguageOptions == 3){
    mLevelSolvedText[0].setString("Nom Du Joueu: ");
    mLevelSolvedText[1].setString("Score de Jeu: ");
    mLevelSolvedText[2].setString("Niveau fini: ");

    sBackButtonString = "Retour";
  }

  /*Bereits erreichte Achievements laden, um entsprechend zum nächsten Level weiterleiten
    oder den Spielstand mit den aktuellen Erfolgen speichern zu können.*/
  loadReachedAchievements();

  //GUI (Button) initialisieren
  pBackButton = new Button("LevelSolved/BackToMenu", sf::Vector2f(100, 100),
    sf::Vector2f(1, 1), "Data/Textures/GUI/Button/ButtonTexture.png", sBackButtonString);

  //Button ausrichten
  pBackButton->setPositionGUIObject(sf::Vector2f(222.f - pBackButton->getSpriteGUIObject().
      getTextureRect().width / 2.f, 530.f));

  //Button registrieren
  mpStateGUIManager->registerGUIObject(pBackButton);

  /*Je nachdem welches Level absolviert wurde, werden entsprechend unterschiedliche GUIObjekte
    initialisiert, hier LevelOne*/
  if (mpAchievements->getLevel() == 1){
    std::string sNextLevelTwoString = "";
    std::string sSaveGame = "";

    //Überschrift "Level Solved 1" initialisieren
    mLevelSolvedText[4].setFont(mLevelSolvedFont);
    mLevelSolvedText[4].setPosition(sf::Vector2f(20,40));
    mLevelSolvedText[4].setCharacterSize(50);
    mLevelSolvedText[4].setFillColor(sf::Color::White);
    mLevelSolvedText[4].setStyle(sf::Text::Bold);

    if (mLanguageOptions == 1){
      mLevelSolvedText[4].setString("LEVEL 1 GESCHAFFT");
      sNextLevelTwoString = "Level 2";
      sSaveGame = "Spiel speichern";
    }
    else if (mLanguageOptions == 2){
      mLevelSolvedText[4].setString("SOLVED LEVEL 1");
      sNextLevelTwoString = "Level 2";
      sSaveGame = "Save Current Game";
    }
    else if (mLanguageOptions == 3){
      mLevelSolvedText[4].setString("RESOLU NIVEAU 1");
      sNextLevelTwoString = "Niveau 2";
      sSaveGame = "Sauvegarder le jeu";
    }

    //Beim Absolvieren von LevelOne wird Button initialisiert, der zu LevelTwo weiterleitet
    //GUI (Button) initialisieren
    pNextLevelTwo = new Button("LevelSolved/NextLevelTwo", sf::Vector2f(100, 100),
        sf::Vector2f(1, 1), "Data/Textures/GUI/Button/ButtonTexture.png", sNextLevelTwoString);
    pSaveGame = new Button("LevelSolved/SaveGame", sf::Vector2f(100, 100),
        sf::Vector2f(1, 1), "Data/Textures/GUI/Button/ButtonTexture.png", sSaveGame);

    //Ausrichten
    pNextLevelTwo->setPositionGUIObject(sf::Vector2f(135.f + pNextLevelTwo->getSpriteGUIObject().
        getTextureRect().width / 4.f, 420.f));
    pSaveGame->setPositionGUIObject(sf::Vector2f(350.f + pSaveGame->getSpriteGUIObject().
        getTextureRect().width / 4.f, 530.f));

    //Button registrieren
    mpStateGUIManager->registerGUIObject(pNextLevelTwo);
    mpStateGUIManager->registerGUIObject(pSaveGame);
  }

  /*Je nachdem welches Level absolviert wurde, werden entsprechend unterschiedliche GUIObjekte
  initialisiert, hier LevelTwo*/
  if (mpAchievements->getLevel() == 2){
    std::string sNextLevelThreeString = "";
    std::string sSaveGame = "";

    //Überschrift "Level Solved 2" initialisieren
    mLevelSolvedText[5].setFont(mLevelSolvedFont);
    mLevelSolvedText[5].setPosition(sf::Vector2f(20.f,40.f));
    mLevelSolvedText[5].setCharacterSize(50);
    mLevelSolvedText[5].setFillColor(sf::Color::White);
    mLevelSolvedText[5].setStyle(sf::Text::Bold);
    if (mLanguageOptions == 1){
      mLevelSolvedText[5].setString("LEVEL 2 GESCHAFFT");
      sNextLevelThreeString = "Level 3";
      sSaveGame = "Spiel speichern";
    }
    else if (mLanguageOptions == 2){
      mLevelSolvedText[5].setString("SOLVED LEVEL 2");
      sNextLevelThreeString = "Level 3";
      sSaveGame = "Save Current Game";
    }
    else if (mLanguageOptions == 3){
      mLevelSolvedText[5].setString("RESOLU NIVEAU 2");
      sNextLevelThreeString = "Niveau 3";
      sSaveGame = "Sauvegarder le jeu";
    }

    //Beim Absolvieren von LevelTwo wird Button initialisiert, der zu LevelThree weiterleitet
    //GUI (Button) initialisieren
    pNextLevelThree = new Button("LevelSolved/NextLevelThree", sf::Vector2f(100, 100),
      sf::Vector2f(1, 1), "Data/Textures/GUI/Button/ButtonTexture.png", sNextLevelThreeString);
    pSaveGame = new Button("LevelSolved/SaveGame", sf::Vector2f(100, 100),
      sf::Vector2f(1, 1), "Data/Textures/GUI/Button/ButtonTexture.png", sSaveGame);

    //Ausrichten
    pNextLevelThree->setPositionGUIObject(sf::Vector2f(135.f + pNextLevelThree->getSpriteGUIObject().
      getTextureRect().width / 4.f, 420.f));
    pSaveGame->setPositionGUIObject(sf::Vector2f(350.f + pSaveGame->getSpriteGUIObject().
      getTextureRect().width / 4.f, 530.f));

    //Button registrieren
    mpStateGUIManager->registerGUIObject(pNextLevelThree);
    mpStateGUIManager->registerGUIObject(pSaveGame);
  }

  /*Je nachdem welches Level absolviert wurde, werden entsprechend unterschiedliche GUIObjekte
  initialisiert, hier LevelThree*/
  if (mpAchievements->getLevel() == 3){
    std::string sHighScoreString = "";

    //Überschrift "Level Solved 3" initialisieren
    mLevelSolvedText[6].setFont(mLevelSolvedFont);
    mLevelSolvedText[6].setPosition(sf::Vector2f(20, 40));
    mLevelSolvedText[6].setCharacterSize(50);
    mLevelSolvedText[6].setFillColor(sf::Color::White);
    mLevelSolvedText[6].setStyle(sf::Text::Bold);
    if (mLanguageOptions == 1){
      mLevelSolvedText[6].setString("LEVEL 3 GESCHAFFT");
      sHighScoreString = "Highscore Liste";
    }
    else if (mLanguageOptions == 2){
      mLevelSolvedText[6].setString("SOLVED LEVEL 3");
      sHighScoreString = "Highscore List";
    }
    else if (mLanguageOptions == 3){
      mLevelSolvedText[6].setString("RESOLU NIVEAU 3");
      sHighScoreString = "Liste De Pointage";
    }

    //Beim Absolvieren von LevelThree wird Button initialisiert, der zum HighScore weiterleitet
    //GUI (Button) initialisieren
    pHighScoreList = new Button("LevelSolved/HighscoreList", sf::Vector2f(100, 100),
      sf::Vector2f(1, 1), "Data/Textures/GUI/Button/ButtonTexture.png", sHighScoreString);

    //Ausrichten
    pHighScoreList->setPositionGUIObject(sf::Vector2f(135.f + pHighScoreList->getSpriteGUIObject().
      getTextureRect().width / 4.f, 420.f));

    //Button registrieren
    mpStateGUIManager->registerGUIObject(pHighScoreList);

    /*Anmerkung: Nach Absolvieren von LevelThree wird kein(!) SaveGame-Button initialisiert,
                 sondern das Spiel wird beim Entern des LevelSolved State in dem Fall
                 automatisch gespeichert.*/
    saveGame();

    //Den Score in das Format 'XXX-Name' bringen, wobei XXX den erreichten Score repräsentiert
    int iPointsInteger = int(mpAchievements->getReachedScorePlayer());
    std::string sScore = std::to_string(iPointsInteger) + "_" + mpAchievements->getPlayerName();

    //Highscore einlesen und in Vector einfügen, damit die alten Scores nicht überschrieben werden
    std::string sEntry = "";
    std::vector<std::string> vecHighscore;
    std::ifstream ifstrReadHighscore("Data/Highscore/highscore.txt");
    if (ifstrReadHighscore.is_open()){
      while (getline(ifstrReadHighscore, sEntry)){
        vecHighscore.push_back(sEntry);
      }
      ifstrReadHighscore.close();
    }

    //Stelle im Vector, an welcher wir den letzten Score finden, der größer als der neue Eintrag ist
    int iLowerScore = 0;
    int iFoundUnderlined = 0;

    /*Durch Vector iterieren und nach Unterstrich suchen. Danach String in Substrings vor und nach dem
    Unterstrich unterteilen. Der Beginn des Strings ist der Score und wird genutzt, um den neuen Score
    einzusortieren.*/
    for (unsigned int i = 0; i < vecHighscore.size(); i++){
      std::string sVectorString = vecHighscore[i];
      iFoundUnderlined = sVectorString.find("_");

      //Wenn String gefunden wurde
      if (iFoundUnderlined != std::string::npos){

        //String aufteilen
        std::string sName = sVectorString.substr(iFoundUnderlined + 1);
        std::string sPoints = sVectorString.substr(0, iFoundUnderlined);
        int iScore = stoi(sPoints);

        if (iScore >= mpAchievements->getReachedScorePlayer()){
          iLowerScore = i;
        }
      }
    }

    //Ist nichts größer als der neue Score, wird dieser an erster Stelle eingefügt
    if (vecHighscore.size() > 0){
      std::string sVectorString = vecHighscore[0];
      iFoundUnderlined = sVectorString.find("_");
      std::string sPoints = sVectorString.substr(0, iFoundUnderlined);
      int iScore = stoi(sPoints);

      if (mpAchievements->getReachedScorePlayer() < iScore && iLowerScore == 0){
        iLowerScore++;
      }
    }

    //Objekt an richtiger Stelle in Vector einfügen
      vecHighscore.insert(vecHighscore.begin() + iLowerScore, sScore);
      
    //Vector schreiben
    std::ofstream ofstrWriteHighscore("Data/Highscore/highscore.txt", std::ofstream::out | std::ofstream::trunc);
    if (ofstrWriteHighscore.is_open()){
      for (unsigned int i = 0; i< vecHighscore.size(); i++){
        ofstrWriteHighscore << vecHighscore[i] << "\n";
      }
    }
    ofstrWriteHighscore.close();
  }
}

void LevelSolved::leaveState(){
  mpStateGUIManager->deleteGUIObjects();
  pBackButton = nullptr;
  pNextLevelThree = nullptr;
  pNextLevelTwo = nullptr;
  pSaveGame = nullptr;
  pHighScoreList = nullptr;

  setNextState("");

  delete mpAchievements;
  delete mpSaveGame;
  delete mpMainSettings;

  mpAchievements = nullptr;
  mpSaveGame = nullptr;
  mpMainSettings = nullptr;

  mLevelSolvedText[3].setString("");
  mLevelSolvedText[4].setString("");
  mLevelSolvedText[5].setString("");
  mLevelSolvedText[6].setString("");

  mpMusicMenu->stop();
  delete mpMusicMenu;
  mpMusicMenu = nullptr;
}

void LevelSolved::loadReachedAchievements(){
  /*Laden der bisher erreichten Erfolge, damit diese im "LevelSolved"-State im
    RenderWindow dargestellt werden können.*/
  mpAchievements = new Achievements();

  FileHandler fhAchievements("Data/Achievements/achievements.txt");

  Achievements *readAchievements = fhAchievements.readAchievements();
  *mpAchievements = *readAchievements;

  //Konvertierung von float in String
  float fReachedScorePlayer = mpAchievements->getReachedScorePlayer();
  std::ostringstream ostrScore;
  ostrScore << fReachedScorePlayer;
  std::string sReachedScorePlayer(ostrScore.str());

  //Konvertierung von Integer in String
  int iSolvedLevel = mpAchievements->getLevel();
  std::ostringstream ostrLevel;
  ostrLevel << iSolvedLevel;
  std::string sSolvedLevel(ostrLevel.str());

  //Einbinden der konvertierten Werte in TextArrays
  mAchievementsText[0].setFont(mLevelSolvedFont);
  mAchievementsText[0].setString(mpAchievements->getPlayerName());
  mAchievementsText[0].setCharacterSize(24);
  mAchievementsText[0].setPosition(450, 200);

  mAchievementsText[1].setFont(mLevelSolvedFont);
  mAchievementsText[1].setString(sReachedScorePlayer);
  mAchievementsText[1].setCharacterSize(24);
  mAchievementsText[1].setPosition(450, 250);

  mAchievementsText[2].setFont(mLevelSolvedFont);
  mAchievementsText[2].setString(sSolvedLevel);
  mAchievementsText[2].setCharacterSize(24);
  mAchievementsText[2].setPosition(450, 300);
}

void LevelSolved::saveGame(){
  mpSaveGame = new Achievements();

  mpSaveGame->setLevel(mpAchievements->getLevel());
  mpSaveGame->setPlayerName(mpAchievements->getPlayerName());
  mpSaveGame->setReachedScorePlayer(mpAchievements->getReachedScorePlayer());

  /*Folgende Methode ermöglicht speichern/laden des Spielstands unter Verwendung des Spielernamens.
    Dafür wird der entsprechende Dateipfad des SaveGames über einen Stringstream mit dem anfangs
    eingegebenen Spielernamen verknüpft.*/
  std::string sNameSaveGame = "";
  sNameSaveGame.append("Data/SaveGame/");
  sNameSaveGame.append(mpAchievements->getPlayerName());
  sNameSaveGame.append(".txt");

  //SaveGame .txt-Datei überschreiben/speichern
  FileHandler fhSaveGame(sNameSaveGame);
  fhSaveGame.writeAchievements(mpSaveGame);

  //SaveGame einlesen
  Achievements *pReadSaveGame = fhSaveGame.readAchievements();
}