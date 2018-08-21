/***************************************************************************
* Klassenname LevelOne
* Date
* Autor(en) Hein, Köhler, Meister
*
* Diese Klasse ist eine Unterklasse des BasicState und verwaltet den
* Spiel-Zustand "Level Eins".
**************************************************************************/
#include "LevelOne.h"

//Konstruktoren (Definition)
LevelOne::LevelOne(){

}

LevelOne::LevelOne(sf::RenderWindow *pRenderWindow, sf::Event *pStateEvent,
    GUIManager *pGUI):mpStateGUIManager(pGUI){
  gpBasicStateWindow = pRenderWindow;
  gpBasicStateEvent  = pStateEvent;
}

//Destruktor (Definition)
LevelOne::~LevelOne(){ 

  mpStateGUIManager->deleteGUIObjects();
  pBackButton = nullptr;
  pContinueButton = nullptr;
  pExitButton = nullptr;

  delete mpPlayer;
  delete mpMouseSprite;
  delete mpMouseTexture;
  delete mpAsteroidManager;
  delete mpCollisionSystem;
  delete mpPauseClock;
  delete mpPanelSprite;
  delete mpPanelTexture;
  delete mpAchievements;
  delete mpLevelOneFont;
  delete mpTimeRemainingText;
  delete mpChronometer;
  delete mpBonusManager;
  delete mpMainSettings;
  delete mpBackgroundTextureLevelOne;
  delete mpBackgroundSpriteLevelOne;
  delete mpPauseMenuText;


  mpPlayer                    = nullptr;
  mpMouseSprite               = nullptr;
  mpMouseTexture              = nullptr;
  mpAsteroidManager           = nullptr;
  mpCollisionSystem           = nullptr;
  mpPauseClock                = nullptr;
  mpPanelSprite               = nullptr;
  mpPanelTexture              = nullptr;
  mpAchievements              = nullptr;
  mpLevelOneFont              = nullptr;
  mpTimeRemainingText         = nullptr;
  mpChronometer               = nullptr;
  mpBonusManager              = nullptr;
  mpMainSettings              = nullptr;
  mpBackgroundTextureLevelOne = nullptr;
  mpBackgroundSpriteLevelOne  = nullptr;
  mpPauseMenuText             = nullptr;

  delete mpMusicLevelOne;
  mpMusicLevelOne = nullptr;

}

//Klassenmethoden
//Grundfunktionen
void LevelOne::handleEvents(){

  mpPlayer->handleEvents();
  mpAsteroidManager->handleEvents();
  mpBonusManager->handleEvents();

  //Pausenzustand durch Betätigen der Escape-Taste initialisieren
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
    /*PauseClock dient hier zur kurzen Zeitverzögerung, damit Pausenzustand mit 
      gleicher Taste gestartet und beendet werden kann.*/
    if (mpPauseClock->getElapsedTime().asMilliseconds() > 1 
        && getPauseEnabled() == false){

      //Pausenmenü laden
      loadPauseMenu();

      //Musik stoppen
      mpMusicLevelOne->pause();

      //Pausenzustand initialisieren
      setPauseEnabled(true);

      //Spielzeit pausieren
      mpChronometer->pause();

      //PauseClock zurücksetzen
      mpPauseClock->restart();
    }
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
    if (mpPauseClock->getElapsedTime().asMilliseconds() > 1
        && getPauseEnabled() == true){

      //Pausenzustand beenden
      setPauseEnabled(false);

      //Pausenmenü löschen
      deletePauseMenu();

      //Musik fortsetzen
      mpMusicLevelOne->play();

      //Spielzeit fortsetzen
      mpChronometer->resume();

      //PauseClock zurücksetzen
      mpPauseClock->restart();
    }
  }

  if (mpStateGUIManager->getGUIObject("Pause/BackToMenu")->getIsClickedGUIObject() == true){
    setNextState("State/Menu");
  }

  if (mpStateGUIManager->getGUIObject("Pause/Continue")->getIsClickedGUIObject() == true){
    setPauseEnabled(false);
    deletePauseMenu();

    mpMusicLevelOne->play();

    mpChronometer->resume();
  }

  if (mpStateGUIManager->getGUIObject("Pause/Exit")->getIsClickedGUIObject() == true){
    gpBasicStateWindow->close();
  }
}

void LevelOne::update(float fFrametime){

  mpMouseSprite->setPosition(static_cast<sf::Vector2f>(sf::Mouse::
    getPosition(*gpBasicStateWindow)));

  /*Damit "PausenZustand" funktioniert, muss beim Initialisieren das "Updaten" aller
    relevanten Objekte gestoppt werden.*/
  if (getPauseEnabled() == false){
    mpPlayer->update(fFrametime);
    mpAsteroidManager->update(fFrametime);
    mpBonusManager->update(fFrametime);
    mpCollisionSystem->update(fFrametime);

    //Spielzeit soll ebenfalls nur aktualisiert werden, sofern Engine nicht im PausenZustand
    updateRemainingTime(getAvailableTime());
  }

  //Sobald die Lebenspunkte des Players auf Null sinken, soll der "GameOver"-State initialisiert werden
  if (mpPlayer->getPlayerIsAlive() == false){
    setNextState("State/GameOver");

    //Bisher erreichte Achievements sollen gespeichert werden
    saveReachedAchievements();
  }

  /*Zeitbegrenzung für LevelOne initialisieren, sobald die Zeit abgelaufen ist,
    wird der "LevelSolved"-Zustand aufgerufen*/
  if (mpChronometer->getElapsedTime().asSeconds() > getAvailableTime()){
    saveReachedAchievements();

    setNextState("State/LevelSolved");
  }

}

void LevelOne::render(){

  gpBasicStateWindow->draw(*mpBackgroundSpriteLevelOne);
  mpPlayer->render(gpBasicStateWindow);
  mpAsteroidManager->render(gpBasicStateWindow);
  mpBonusManager->render(gpBasicStateWindow);
  gpBasicStateWindow->draw(*mpTimeRemainingText);

  //Verwaltung der Sichtbarkeit des Mauszeigers
  if (getPauseEnabled() == true){
    gpBasicStateWindow->setMouseCursorVisible(true);
    gpBasicStateWindow->draw(*mpPanelSprite);
    gpBasicStateWindow->draw(*mpPauseMenuText);
  }
  else{
    gpBasicStateWindow->setMouseCursorVisible(false);
  
  }

}

//Setter
void LevelOne::setAvailableTime(float fAvailableTime){
  mAvailableTime = fAvailableTime;
}

void LevelOne::setPauseEnabled(bool bEnablePause){
  mPause = bEnablePause;
}

//Getter
float LevelOne::getAvailableTime(){
  return mAvailableTime;
}

bool LevelOne::getPauseEnabled(){
  return mPause;
}

//Spezifische Funktionen
void LevelOne::enterState(){

  //GameObjects initiieren/laden (Reihenfolge bedeutsam!)
  mpPlayer = new Player(std::string("Data/Textures/GameObjects/Player/player.png"),
    sf::Vector2f(640, 670));
  
  mpBackgroundTextureLevelOne = new sf::Texture;
  mpBackgroundSpriteLevelOne = new sf::Sprite;

  if (!mpBackgroundTextureLevelOne->loadFromFile("Data/Textures/backgroundLevel.png")){
    std::string error("Could not load Texture for mpBackgroundTextureLevelOne from: ");
    error.append("Data/Textures/backgroundLevel.png");
    error.append("\n");
    error.append("Check data path and image file formats!");
    throw std::exception(error.c_str());
  }
  mpBackgroundSpriteLevelOne->setTexture(*mpBackgroundTextureLevelOne);

  mpAsteroidManager = new AsteroidManager();
  mpAsteroidManager->setSpawnLevel(1);
  mpBonusManager = new BonusManager();
  mpBonusManager->setSpawnLevel(1);
  mpCollisionSystem = new CollisionSystem(mpPlayer, mpAsteroidManager->getAsteroidsList(),
    mpBonusManager->getBonusList(), mpBonusManager->getWeaponUpgradeList());

  mpMouseTexture = new sf::Texture;
  mpMouseSprite = new sf::Sprite;

  mpPanelTexture = new sf::Texture;
  mpPanelSprite = new sf::Sprite;

  if (!mpPanelTexture->loadFromFile("Data/Textures/GUI/Panel/Panel.png")){
    std::string error("Could not load Texture for mpPanelTexture from: ");
    error.append("Data/Textures/GUI/Panel/Panel.png");
    error.append("\n");
    error.append("Check data path and image file formats!");
    throw std::exception(error.c_str());
  }
  mpPanelSprite->setTexture(*mpPanelTexture);
  mpPanelSprite->setPosition(640 - mpPanelSprite->getGlobalBounds().width / 2, 100);
  
  //MainSettings laden (bei Programmstart mit Defaultwerten, sonst bereits gespeicherte
  mpMainSettings = new MainSettings();
  *mpMainSettings = BinaryData::readBinaryFile<MainSettings>("Data/Bin/Settings/mainsettings.bin");
  
  //Musik-Instanz initiieren
  mpMusicLevelOne = new sf::Music;
  if (!mpMusicLevelOne->openFromFile("Data/Sounds/Music/backgroundLevel1.ogg")){
    std::string error("Could not load Music for mpMusicLevelOne from: ");
    error.append("Data/Sounds/Music/backgroundLevel1.ogg");
    error.append("\n");
    error.append("Check data path. Remember, that only wav, flac, ogg, mp3 are supported!");
    throw std::exception(error.c_str());
  }

  //Hintergrund-Musik
  //Lautstärke je nach geladenen MainSettings setzen
  mpMusicLevelOne->setVolume(mpMainSettings->getMusicVolume());
  mpMusicLevelOne->setLoop(true);

  sf::SoundSource::Status musicStatus = mpMusicLevelOne->getStatus();
  if (musicStatus == sf::SoundSource::Status::Paused &&
    mpMainSettings->getIsMusicEnabled() == true){
    mpMusicLevelOne->play();
  }
  else if (musicStatus == sf::SoundSource::Status::Playing &&
    mpMainSettings->getIsMusicEnabled() == false){
    mpMusicLevelOne->stop();
  }
  else if (musicStatus == sf::SoundSource::Status::Stopped
    && mpMainSettings->getIsMusicEnabled() == true){
    mpMusicLevelOne->play();
  }

  mLanguageOptions = mpMainSettings->getLanguage();

  //Pausenzustand deaktivieren
  setPauseEnabled(false);

  //Achievements Instanz zur weiteren Verwendung initialisieren und .txt Datei laden
  loadAchievements();

  //Zeit-Instanzen initialisieren
  mpPauseClock  = new sf::Clock;
  mpChronometer = new sfClockTool::Chronometer();

  //Spielzeit in RenderWindow darstellen
  mpTimeRemainingText = new sf::Text;
  mpLevelOneFont      = new sf::Font;
  if (!mpLevelOneFont->loadFromFile("Data/Font/04B_30__.ttf")){
    std::string error("Could not load Font for mpLevelOneFont from: ");
    error.append("Data/Font/04B_30__.ttf");
    error.append("\n");
    error.append("Check data path and image file formats!");
    throw std::exception(error.c_str());
  }
  mpTimeRemainingText->setFont(*mpLevelOneFont);
  mpTimeRemainingText->setPosition(1000,20);
  mpTimeRemainingText->setCharacterSize(24);

  //Für das Level verfügbare Spielzeit initialisieren
  setAvailableTime(30.f);

  //Chronometer bei Betreten des Levels starten
  mpChronometer->resume();

}

void LevelOne::leaveState(){

  //Mauszeiger soll wieder sichtbar sein, beim Verlassen des States
  gpBasicStateWindow->setMouseCursorVisible(true);

  mpStateGUIManager->deleteGUIObjects();
  pBackButton = nullptr;
  pContinueButton = nullptr;
  pExitButton = nullptr;

  setNextState("");

  delete mpPlayer;
  delete mpMouseSprite;
  delete mpMouseTexture;
  delete mpAsteroidManager;
  delete mpCollisionSystem;
  delete mpPauseClock;
  delete mpPanelSprite;
  delete mpPanelTexture;
  delete mpAchievements;
  delete mpLevelOneFont;
  delete mpTimeRemainingText;
  delete mpChronometer;
  delete mpBonusManager;
  delete mpMainSettings;
  delete mpBackgroundTextureLevelOne;
  delete mpBackgroundSpriteLevelOne;
  delete mpPauseMenuText;

  mpPlayer                    = nullptr;
  mpMouseSprite               = nullptr;
  mpMouseTexture              = nullptr;
  mpAsteroidManager           = nullptr;
  mpCollisionSystem           = nullptr;
  mpPauseClock                = nullptr;
  mpPanelSprite               = nullptr;
  mpPanelTexture              = nullptr;
  mpAchievements              = nullptr;
  mpLevelOneFont              = nullptr;
  mpTimeRemainingText         = nullptr;
  mpChronometer               = nullptr;
  mpBonusManager              = nullptr;
  mpMainSettings              = nullptr;
  mpBackgroundTextureLevelOne = nullptr;
  mpBackgroundSpriteLevelOne  = nullptr;
  mpPauseMenuText             = nullptr;

  mpMusicLevelOne->stop();
  delete mpMusicLevelOne;
  mpMusicLevelOne = nullptr;
}

void LevelOne::loadAchievements(){
  mpAchievements = new Achievements();
  FileHandler fhAchievements("Data/Achievements/achievements.txt");
  Achievements *readAchievements = fhAchievements.readAchievements();
  *mpAchievements = *readAchievements;
}

void LevelOne::saveReachedAchievements(){
  FileHandler fhAchievements("Data/Achievements/achievements.txt");

  mpAchievements->setLevel(1);
  mpAchievements->setReachedScorePlayer(mpPlayer->getPlayerScore());

  fhAchievements.writeAchievements(mpAchievements);
}

void LevelOne::loadPauseMenu(){

  std::string sBackButtonString = "";
  std::string sContinueString   = "";
  std::string sExitString       = "";

  if (mLanguageOptions == 1){
    sBackButtonString = "Hauptmenue";
    sContinueString   = "Fortsetzen";
    sExitString       = "Beenden";
  }
  else if (mLanguageOptions == 2){
    sBackButtonString = "Main Menu";
    sContinueString   = "Continue";
    sExitString       = "Exit";
  }
  else if (mLanguageOptions == 3){
    sBackButtonString = "Menu Principal";
    sContinueString   = "Continuer";
    sExitString       = "Sortie";
  }

  //GUI (Button) initialisieren
  pBackButton = new Button("Pause/BackToMenu", sf::Vector2f(100, 100),
      sf::Vector2f(1, 1), "Data/Textures/GUI/Button/ButtonTexture.png", sBackButtonString);
  pContinueButton = new Button("Pause/Continue", sf::Vector2f(100, 100),
      sf::Vector2f(1, 1), "Data/Textures/GUI/Button/ButtonTexture.png", sContinueString);
  pExitButton = new Button("Pause/Exit", sf::Vector2f(100, 100),
      sf::Vector2f(1, 1), "Data/Textures/GUI/Button/ButtonTexture.png", sExitString);

  //Button ausrichten
  pBackButton->setPositionGUIObject(sf::Vector2f(640.f - pBackButton->getSpriteGUIObject().
    getTextureRect().width / 2.f, 300.f));
  pContinueButton->setPositionGUIObject(sf::Vector2f(640.f - pContinueButton->getSpriteGUIObject().
    getTextureRect().width / 2.f, 200.f));
  pExitButton->setPositionGUIObject(sf::Vector2f(640.f - pExitButton->getSpriteGUIObject().
    getTextureRect().width / 2.f, 400.f));

  //Button registrieren
  mpStateGUIManager->registerGUIObject(pBackButton);
  mpStateGUIManager->registerGUIObject(pContinueButton);
  mpStateGUIManager->registerGUIObject(pExitButton);

  //Überschrift des Pausenmenüs
  mpPauseMenuText = new sf::Text;
  mpPauseMenuText->setFont(*mpLevelOneFont);
  mpPauseMenuText->setPosition(sf::Vector2f(775.f - pBackButton->getSpriteGUIObject().
    getTextureRect().width / 2.f, 150.f));
  mpPauseMenuText->setCharacterSize(36);
  mpPauseMenuText->setFillColor(sf::Color::Black);
  mpPauseMenuText->setStyle(sf::Text::Bold);
  mpPauseMenuText->setString("Pause");
}

void LevelOne::deletePauseMenu(){
  mpStateGUIManager->deleteGUIObjects();
  pBackButton     = nullptr;
  pContinueButton = nullptr;
  pExitButton     = nullptr;

  delete mpPauseMenuText;
  mpPauseMenuText = nullptr;
}

double LevelOne::getFloatPrecision(double dValue, double dPrecision){
  return(floor((dValue * pow(10, dPrecision) + 0.5)) / pow(10, dPrecision));
}

void LevelOne::updateRemainingTime(float fAvailableTime){
  float fTimeRemaining = fAvailableTime - mpChronometer->getElapsedTime().asSeconds();

  //Precision -> Float-Wert wird auf zwei Stellen nach dem Komma gerundet und in String konvertiert
  std::ostringstream ostrTimeRemaining;
  ostrTimeRemaining << getFloatPrecision(fTimeRemaining, 2);
  std::string sTimeRemaining(ostrTimeRemaining.str());

  //Spielzeit in RenderWindow darstellen
  if (mLanguageOptions == 1){
    mpTimeRemainingText->setString("Zeit: " + sTimeRemaining);
  }
  else if (mLanguageOptions == 2){
    mpTimeRemainingText->setString("Time: " + sTimeRemaining);
  }
  else if (mLanguageOptions == 3){
    mpTimeRemainingText->setString("Temps: " + sTimeRemaining);
  }
}