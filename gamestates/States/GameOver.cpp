/***************************************************************************
* Klassenname GameOver
* Date
* Autor(en) Hein, Köhler, Meister
*
* Diese Klasse ist eine Unterklasse des BasicState und verwaltet die
* den Zustand "Game Over".
**************************************************************************/
#include "GameOver.h"

//Konstruktoren (Definition)
GameOver::GameOver(){

}

GameOver::GameOver(sf::RenderWindow *pRenderWindow, sf::Event *pStateEvent,
    GUIManager *pGUI) :mpStateGUIManager(pGUI){
  gpBasicStateWindow = pRenderWindow;
  gpBasicStateEvent  = pStateEvent;

  //Initialisierung von Text
  if (!mGameOverFont.loadFromFile("Data/Font/04B_30__.ttf")){
    std::string error("Could not load Font for mGameOverFont from: ");
    error.append("Data/Font/04B_30__.ttf");
    error.append("\n");
    error.append("Check data path and image file formats!");
    throw std::exception(error.c_str());
  }

  //Text Spielername
  mGameOverText[0].setFont(mGameOverFont);
  mGameOverText[0].setCharacterSize(24);
  mGameOverText[0].setPosition(20, 200);

  //Text erreichte Punkte
  mGameOverText[1].setFont(mGameOverFont);
  mGameOverText[1].setCharacterSize(24);
  mGameOverText[1].setPosition(20, 250);

  //Text erreichtes Level
  mGameOverText[2].setFont(mGameOverFont);
  mGameOverText[2].setCharacterSize(24);
  mGameOverText[2].setPosition(20, 300);
}

//Destruktor (Definition)
GameOver::~GameOver(){

  mpStateGUIManager->deleteGUIObjects();
  pBackButton = nullptr;

  delete mpAchievements;
  delete mpMainSettings;

  mpAchievements = nullptr;
  mpMainSettings = nullptr;

  delete mpMusicGameOver;
  mpMusicGameOver = nullptr;

}

//Klassenmethoden (Definition)
//Grundfunktionen
void GameOver::handleEvents(){
  if (mpStateGUIManager->getGUIObject("GameOver/BackToMenu")->getIsClickedGUIObject() == true){
    setNextState("State/Menu");
  }
}

void GameOver::update(float fFrametime){

}

void GameOver::render(){
  gpBasicStateWindow->draw(mGameOverText[0]);
  gpBasicStateWindow->draw(mGameOverText[1]);
  gpBasicStateWindow->draw(mGameOverText[2]);
  gpBasicStateWindow->draw(mGameOverText[3]);

  gpBasicStateWindow->draw(mAchievementsText[0]);
  gpBasicStateWindow->draw(mAchievementsText[1]);
  gpBasicStateWindow->draw(mAchievementsText[2]);
}

//Spezifische Funktionen
void GameOver::enterState(){

  //Überschrift "Game Over" initialisieren
  mGameOverText[3].setFont(mGameOverFont);
  mGameOverText[3].setPosition(sf::Vector2f(20,40));
  mGameOverText[3].setCharacterSize(50);
  mGameOverText[3].setFillColor(sf::Color::White);
  mGameOverText[3].setStyle(sf::Text::Bold);

  //MainSettings laden (bei Programmstart mit Defaultwerten, sonst bereits gespeicherte
  mpMainSettings = new MainSettings();
  *mpMainSettings = BinaryData::readBinaryFile<MainSettings>("Data/Bin/Settings/mainsettings.bin");
  
  //Musik-Instanz initiieren
  mpMusicGameOver = new sf::Music;
  if (!mpMusicGameOver->openFromFile("Data/Sounds/Music/backgroundGameOver.ogg")){
    std::string error("Could not load Music for mpMusicGameOver from: ");
    error.append("Data/Sounds/Music/backgroundGameOver.ogg");
    error.append("\n");
    error.append("Check data path. Remember, that only wav, flac, ogg, mp3 are supported!");
    throw std::exception(error.c_str());
  }
  
  //Hintergrund-Musik
  //Lautstärke je nach geladenen MainSettings setzen
  mpMusicGameOver->setVolume(mpMainSettings->getMusicVolume());
  mpMusicGameOver->setLoop(true);

  sf::SoundSource::Status musicStatus = mpMusicGameOver->getStatus();
  if (musicStatus == sf::SoundSource::Status::Paused &&
    mpMainSettings->getIsMusicEnabled() == true){
    mpMusicGameOver->play();
  }
  else if (musicStatus == sf::SoundSource::Status::Playing &&
    mpMainSettings->getIsMusicEnabled() == false){
    mpMusicGameOver->stop();
  }
  else if (musicStatus == sf::SoundSource::Status::Stopped
    && mpMainSettings->getIsMusicEnabled() == true){
    mpMusicGameOver->play();
  }

  mLanguageOptions = mpMainSettings->getLanguage();
  std::string sBackButtonString = "";
  std::string sSaveApplyString = "";

  if (mLanguageOptions == 1){
    mGameOverText[0].setString("Spielername: ");
    mGameOverText[1].setString("Erreichte Punkte: ");
    mGameOverText[2].setString("Aktuelles Level: ");
    mGameOverText[3].setString("GAME OVER");

    sBackButtonString = "Zurueck";
  }
  else if (mLanguageOptions == 2){
    mGameOverText[0].setString("Player Name: ");
    mGameOverText[1].setString("Achieved Game Score: ");
    mGameOverText[2].setString("Current Level: ");
    mGameOverText[3].setString("GAME OVER");

    sBackButtonString = "Back";
  }
  else if (mLanguageOptions == 3){
    mGameOverText[0].setString("Nom Du Joueu: ");
    mGameOverText[1].setString("Score de Jeu: ");
    mGameOverText[2].setString("Niveau Actuel: ");
    mGameOverText[3].setString("GAME OVER");

    sBackButtonString = "Retour";
  }

  loadReachedAchievements();

  //GUI (Button) initialisieren
  pBackButton = new Button("GameOver/BackToMenu", sf::Vector2f(100, 100),
    sf::Vector2f(1, 1), "Data/Textures/GUI/Button/ButtonTexture.png", sBackButtonString);

  //Button ausrichten
  pBackButton->setPositionGUIObject(sf::Vector2f(222.f - pBackButton->getSpriteGUIObject().
      getTextureRect().width / 2.f, 530.f));

  //Button registrieren
  mpStateGUIManager->registerGUIObject(pBackButton);
}

void GameOver::leaveState(){
  mpStateGUIManager->deleteGUIObjects();
  pBackButton = nullptr;

  setNextState("");

  delete mpAchievements;
  delete mpMainSettings;

  mpAchievements = nullptr;
  mpMainSettings = nullptr;

  mpMusicGameOver->stop();
  delete mpMusicGameOver;
  mpMusicGameOver = nullptr;
}

void GameOver::loadReachedAchievements(){
  mpAchievements = new Achievements();

  FileHandler fhAchievements("Data/Achievements/achievements.txt");

  Achievements *readAchievements = fhAchievements.readAchievements();
  *mpAchievements = *readAchievements;

  //Konvertieren float in String
  float fReachedScorePlayer = mpAchievements->getReachedScorePlayer();
  std::ostringstream ostrScore;
  ostrScore << fReachedScorePlayer;
  std::string sReachedScorePlayer(ostrScore.str());

  //Konvertieren Integer in String
  int iCurrentLevel = mpAchievements->getLevel();
  std::ostringstream ostrLevel;
  ostrLevel << iCurrentLevel;
  std::string sSolvedLevel(ostrLevel.str());

  //Achievements als String im RenderWindow darstellen
  mAchievementsText[0].setFont(mGameOverFont);
  mAchievementsText[0].setString(mpAchievements->getPlayerName());
  mAchievementsText[0].setCharacterSize(24);
  mAchievementsText[0].setPosition(450, 200);

  mAchievementsText[1].setFont(mGameOverFont);
  mAchievementsText[1].setString(sReachedScorePlayer);
  mAchievementsText[1].setCharacterSize(25);
  mAchievementsText[1].setPosition(450, 250);

  mAchievementsText[2].setFont(mGameOverFont);
  mAchievementsText[2].setString(sSolvedLevel);
  mAchievementsText[2].setCharacterSize(25);
  mAchievementsText[2].setPosition(450,300);
}