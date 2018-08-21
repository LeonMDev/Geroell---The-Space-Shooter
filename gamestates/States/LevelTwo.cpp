/***************************************************************************
* Klassenname LevelTwo
* Date
* Autor(en) Hein, Köhler, Meister
*
* Diese Klasse ist eine Unterklasse des BasicState und verwaltet den
* Spiel-Zustand "Level Zwei".
**************************************************************************/
#include "LevelTwo.h"

//Konstruktoren (Definition)
LevelTwo::LevelTwo(){

}

LevelTwo::LevelTwo(sf::RenderWindow *pRenderWindow, sf::Event *pStateEvent,
  GUIManager *pGUI) :mpStateGUIManager(pGUI){
  gpBasicStateWindow = pRenderWindow;
  gpBasicStateEvent = pStateEvent;
}

//Destruktor (Definition)
LevelTwo::~LevelTwo(){

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
  delete mpLevelTwoFont;
  delete mpTimeRemainingText;
  delete mpChronometer;
  delete mpMainSettings;
  delete mpBonusManager;
  delete mpBackgroundTextureLevelTwo;
  delete mpBackgroundSpriteLevelTwo;
  delete mpPauseMenuText;


  mpPlayer = nullptr;
  mpMouseSprite = nullptr;
  mpMouseTexture = nullptr;
  mpAsteroidManager = nullptr;
  mpCollisionSystem = nullptr;
  mpPauseClock = nullptr;
  mpPanelSprite = nullptr;
  mpPanelTexture = nullptr;
  mpAchievements = nullptr;
  mpLevelTwoFont = nullptr;
  mpTimeRemainingText = nullptr;
  mpChronometer = nullptr;
  mpMainSettings = nullptr;
  mpBonusManager = nullptr;
  mpBackgroundTextureLevelTwo = nullptr;
  mpBackgroundSpriteLevelTwo = nullptr;
  mpPauseMenuText = nullptr;

  delete mpMusicLevelTwo;
  mpMusicLevelTwo = nullptr;
}

//Klassenmethoden
//Grundfunktionen
void LevelTwo::handleEvents(){
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
      mpMusicLevelTwo->pause();

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
      mpMusicLevelTwo->play();

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

    mpMusicLevelTwo->play();

    mpChronometer->resume();
  }

  if (mpStateGUIManager->getGUIObject("Pause/Exit")->getIsClickedGUIObject() == true){
    gpBasicStateWindow->close();
  }
}

void LevelTwo::update(float fFrametime){
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

  /*Zeitbegrenzung für LevelTwo initialisieren, sobald die Zeit abgelaufen ist,
  wird der "LevelSolved"-Zustand aufgerufen*/
  if (mpChronometer->getElapsedTime().asSeconds() > getAvailableTime()){
    saveReachedAchievements();

    setNextState("State/LevelSolved");
  }
}

void LevelTwo::render(){
  gpBasicStateWindow->draw(*mpBackgroundSpriteLevelTwo);
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
void LevelTwo::setAvailableTime(float fAvailableTime){
  mAvailableTime = fAvailableTime;
}

void LevelTwo::setPauseEnabled(bool bEnablePause){
  mPause = bEnablePause;
}

//Getter
float LevelTwo::getAvailableTime(){
  return mAvailableTime;
}

bool LevelTwo::getPauseEnabled(){
  return mPause;
}

//Spezifische Funktionen
void LevelTwo::enterState(){

  //GameObjects initiieren/laden (Reihenfolge bedeutsam!)
  mpPlayer = new Player(std::string("Data/Textures/GameObjects/Player/player.png"),
    sf::Vector2f(640, 670));

  mpBackgroundTextureLevelTwo = new sf::Texture;
  mpBackgroundSpriteLevelTwo = new sf::Sprite;

  if (!mpBackgroundTextureLevelTwo->loadFromFile("Data/Textures/backgroundLevel2.png")){
    std::string error("Could not load Texture for mpBackgroundTextureLevelTwo from: ");
    error.append("Data/Textures/backgroundLevel2.png");
    error.append("\n");
    error.append("Check data path and image file formats!");
    throw std::exception(error.c_str());
  }
  mpBackgroundSpriteLevelTwo->setTexture(*mpBackgroundTextureLevelTwo);

  mpAsteroidManager = new AsteroidManager();
  mpBonusManager = new BonusManager();
  mpAsteroidManager->setSpawnLevel(2);
  mpBonusManager->setSpawnLevel(2);
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
  mpMusicLevelTwo = new sf::Music;
  if (!mpMusicLevelTwo->openFromFile("Data/Sounds/Music/backgroundLevel2.ogg")){
    std::string error("Could not load Music for mpMusicLevelTwo from: ");
    error.append("Data/Sounds/Music/backgroundLevel2.ogg");
    error.append("\n");
    error.append("Check data path. Remember, that only wav, flac, ogg, mp3 are supported!");
    throw std::exception(error.c_str());
  }

  //Hintergrund-Musik
  //Lautstärke je nach geladenen MainSettings setzen
  mpMusicLevelTwo->setVolume(mpMainSettings->getMusicVolume());
  mpMusicLevelTwo->setLoop(true);

  sf::SoundSource::Status musicStatus = mpMusicLevelTwo->getStatus();
  if (musicStatus == sf::SoundSource::Status::Paused &&
    mpMainSettings->getIsMusicEnabled() == true){
    mpMusicLevelTwo->play();
  }
  else if (musicStatus == sf::SoundSource::Status::Playing &&
    mpMainSettings->getIsMusicEnabled() == false){
    mpMusicLevelTwo->stop();
  }
  else if (musicStatus == sf::SoundSource::Status::Stopped
    && mpMainSettings->getIsMusicEnabled() == true){
    mpMusicLevelTwo->play();
  }
  
  mLanguageOptions = mpMainSettings->getLanguage();

  //Pausenzustand deaktivieren
  setPauseEnabled(false);

  //Achievements Instanz zur weiteren Verwendung initialisieren und .txt Datei laden
  loadReachedAchievements();
  mpPlayer->setPlayerScore(mpAchievements->getReachedScorePlayer());

  //Zeit-Instanzen initialisieren
  mpPauseClock  = new sf::Clock;
  mpChronometer = new sfClockTool::Chronometer();

  //Spielzeit in RenderWindow darstellen
  mpTimeRemainingText = new sf::Text;
  mpLevelTwoFont      = new sf::Font;
  if (!mpLevelTwoFont->loadFromFile("Data/Font/04B_30__.ttf")){
    std::string error("Could not load Font for mpLevelTwoFont from: ");
    error.append("Data/Font/04B_30__.ttf");
    error.append("\n");
    error.append("Check data path and image file formats!");
    throw std::exception(error.c_str());
  }
  mpTimeRemainingText->setFont(*mpLevelTwoFont);
  mpTimeRemainingText->setPosition(1000, 20);
  mpTimeRemainingText->setCharacterSize(24);

  //Für das Level verfügbare Spielzeit initialisieren
  setAvailableTime(60.f);

  //Chronometer bei Betreten des Levels starten
  mpChronometer->resume();

}

void LevelTwo::leaveState(){

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
  delete mpLevelTwoFont;
  delete mpTimeRemainingText;
  delete mpChronometer;
  delete mpMainSettings;
  delete mpBonusManager;
  delete mpBackgroundTextureLevelTwo;
  delete mpBackgroundSpriteLevelTwo;
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
  mpLevelTwoFont              = nullptr;
  mpTimeRemainingText         = nullptr;
  mpChronometer               = nullptr;
  mpMainSettings              = nullptr;
  mpBonusManager              = nullptr;
  mpBackgroundTextureLevelTwo = nullptr;
  mpBackgroundSpriteLevelTwo  = nullptr;
  mpPauseMenuText             = nullptr;

  mpMusicLevelTwo->stop();
  delete mpMusicLevelTwo;
  mpMusicLevelTwo = nullptr;
}

void LevelTwo::loadReachedAchievements(){
  mpAchievements = new Achievements();
  FileHandler fhAchievements("Data/Achievements/achievements.txt");
  Achievements *readAchievements = fhAchievements.readAchievements();
  *mpAchievements = *readAchievements;
}

void LevelTwo::saveReachedAchievements(){
  FileHandler fhAchievements("Data/Achievements/achievements.txt");

  mpAchievements->setLevel(2);
  mpAchievements->setReachedScorePlayer(mpPlayer->getPlayerScore());

  fhAchievements.writeAchievements(mpAchievements);
}

void LevelTwo::loadPauseMenu(){

  std::string sBackButtonString = "";
  std::string sContinueString = "";
  std::string sExitString = "";

  if (mLanguageOptions == 1){
    sBackButtonString = "Hauptmenue";
    sContinueString = "Fortsetzen";
    sExitString = "Beenden";
  }
  else if (mLanguageOptions == 2){
    sBackButtonString = "Main Menu";
    sContinueString = "Continue";
    sExitString = "Exit";
  }
  else if (mLanguageOptions == 3){
    sBackButtonString = "Menu Principal";
    sContinueString = "Continuer";
    sExitString = "Sortie";
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
  mpPauseMenuText->setFont(*mpLevelTwoFont);
  mpPauseMenuText->setPosition(sf::Vector2f(775.f - pBackButton->getSpriteGUIObject().
    getTextureRect().width / 2.f, 150.f));
  mpPauseMenuText->setCharacterSize(36);
  mpPauseMenuText->setFillColor(sf::Color::Black);
  mpPauseMenuText->setStyle(sf::Text::Bold);
  mpPauseMenuText->setString("Pause");
}

void LevelTwo::deletePauseMenu(){
  mpStateGUIManager->deleteGUIObjects();
  pBackButton = nullptr;
  pContinueButton = nullptr;
  pExitButton = nullptr;

  delete mpPauseMenuText;
  mpPauseMenuText = nullptr;
}

double LevelTwo::getFloatPrecision(double dValue, double dPrecision){
  return(floor((dValue * pow(10, dPrecision) + 0.5)) / pow(10, dPrecision));
}

void LevelTwo::updateRemainingTime(float fAvailableTime){
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