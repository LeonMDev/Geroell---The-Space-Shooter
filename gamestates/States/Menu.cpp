/***************************************************************************
* Klassenname Menu
* Date
* Autor(en) Hein, Köhler, Meister
*
* Diese Klasse ist eine Unterklasse des BasicState. In dieser Klasse 
* wird der Zustand des Hauptmenüs verwaltet.
**************************************************************************/
#include "Menu.h"

//Konstruktoren (Definition)
Menu::Menu(){

}

Menu::Menu(sf::RenderWindow *pRenderWindow, sf::Event *pStateEvent, 
    GUIManager *pGUI): mpStateGUIManager(pGUI){
  gpBasicStateWindow = pRenderWindow;
  gpBasicStateEvent  = pStateEvent;

}

//Destruktor (Definition)
Menu::~Menu(){

  mpStateGUIManager->deleteGUIObjects();
  pExitButton = nullptr;
  pCreditsButton = nullptr;
  pStartButton = nullptr;
  pOptionsButton = nullptr;
  pLoadGame = nullptr;
  pHelpButton = nullptr;
  pHighscoreButton = nullptr;

  delete mpMainSettings;
  mpMainSettings    = nullptr;

  delete mpMusicMenu;
  mpMusicMenu = nullptr;

}

//Klassenmethoden (Definition)
//Grundfunktionen
void Menu::handleEvents(){

  //Navigation des Menüs in die entsprechenden States über Button-Funktion
  //Wenn der "Exit"-Button gedrückt wird, soll sich das Fenster schließen
  if (mpStateGUIManager->getGUIObject("Menu/Exit")->getIsClickedGUIObject() == true){
    gpBasicStateWindow->close();
  }

  //"Click"-> Credits
  if (mpStateGUIManager->getGUIObject("Menu/Credits")->getIsClickedGUIObject() == true){
    setNextState("State/Credits");
  }

  //"Click"-> Options
  if (mpStateGUIManager->getGUIObject("Menu/Options")->getIsClickedGUIObject() == true){
    setNextState("State/Options");
  }

  //"Click" -> Start
  if (mpStateGUIManager->getGUIObject("Menu/Start")->getIsClickedGUIObject() == true){
    setNextState("State/PreGame");
  }

  //"Click"-> Load Game
  if (mpStateGUIManager->getGUIObject("Menu/LoadGame")->getIsClickedGUIObject() == true){
    setNextState("State/LoadGame");
  }

  //"Click"-> Highscore
  if (mpStateGUIManager->getGUIObject("Menu/Highscore")->getIsClickedGUIObject() == true){
    setNextState("State/Highscore");
  }

  //"Click"-> Help
  if (mpStateGUIManager->getGUIObject("Menu/Help")->getIsClickedGUIObject() == true){
    setNextState("State/Help");
  }
}

void Menu::update(float fFrametime){

}

void Menu::render(){

}

//Spezifische Funktionen

//GUI-Elemente des Hauptmenüs initialisieren
void Menu::enterState(){

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
  std::string sExitButtonString = "";
  std::string sCreditsString    = "";
  std::string sStartButton      = "";
  std::string sOptionsString    = "";
  std::string sLoadGame         = "";
  std::string sHelpButtonString = "";
  std::string sHighscoreString  = "";

  if (mLanguageOptions == 1){
    sExitButtonString = "Spiel verlassen";
    sCreditsString = "Credits";
    sStartButton = "Spiel starten";
    sOptionsString = "Optionen";
    sLoadGame = "Spiel laden";
    sHelpButtonString = "Hilfe";
    sHighscoreString = "Highscore";
  }
  else if (mLanguageOptions == 2){
    sExitButtonString = "Exit";
    sCreditsString = "Credits";
    sStartButton = "Start Game";
    sOptionsString = "Options";
    sLoadGame = "Load Game";
    sHelpButtonString = "Help";
    sHighscoreString = "Highscore";
  }
  else if (mLanguageOptions == 3){
    sExitButtonString = "Sortie";
    sCreditsString = "Credits";
    sStartButton = "Demarrer Jeu";
    sOptionsString = "Options";
    sLoadGame = "Chargement Du Jeu";
    sHelpButtonString = "Aider";
    sHighscoreString = "Sore Eleve";
  }

  //GUI-Element (Button) initialisieren
  pExitButton    = new Button("Menu/Exit", sf::Vector2f(100, 100),
      sf::Vector2f(1, 1), "Data/Textures/GUI/Button/ButtonTexture.png", sExitButtonString);
  pCreditsButton = new Button("Menu/Credits", sf::Vector2f(100, 100),
      sf::Vector2f(1, 1), "Data/Textures/GUI/Button/ButtonTextureCredits.png", sCreditsString);
  pStartButton   = new Button("Menu/Start", sf::Vector2f(100, 100),
      sf::Vector2f(1, 1), "Data/Textures/GUI/Button/ButtonTexture.png", sStartButton);
  pOptionsButton = new Button("Menu/Options", sf::Vector2f(100, 100),
      sf::Vector2f(1, 1), "Data/Textures/GUI/Button/ButtonTexture.png", sOptionsString);
  pLoadGame      = new Button("Menu/LoadGame", sf::Vector2f(100, 100),
      sf::Vector2f(1, 1), "Data/Textures/GUI/Button/ButtonTexture.png", sLoadGame);
  pHelpButton    = new Button("Menu/Help", sf::Vector2f(100, 100),
      sf::Vector2f(1, 1), "Data/Textures/GUI/Button/ButtonTexture.png", sHelpButtonString);
  pHighscoreButton = new Button("Menu/Highscore", sf::Vector2f(100, 100),
      sf::Vector2f(1, 1), "Data/Textures/GUI/Button/ButtonTexture.png", sHighscoreString);

  //Button ausrichten
  pExitButton->setPositionGUIObject(sf::Vector2f(350.f 
      - pExitButton->getSpriteGUIObject().getTextureRect().width / 2.f, 565.f));
  pCreditsButton->setPositionGUIObject(sf::Vector2f(1120.f 
      - pCreditsButton->getSpriteGUIObject().getTextureRect().width / 2.f, 633.f));
  pStartButton->setPositionGUIObject(sf::Vector2f(350.f 
      - pStartButton->getSpriteGUIObject().getTextureRect().width / 2.f, 65.f));
  pOptionsButton->setPositionGUIObject(sf::Vector2f(350.f 
      - pOptionsButton->getSpriteGUIObject().getTextureRect().width / 2, 265.f));
  pLoadGame->setPositionGUIObject(sf::Vector2f(350.f
      - pLoadGame->getSpriteGUIObject().getTextureRect().width / 2.f, 165.f));
  pHelpButton->setPositionGUIObject(sf::Vector2f(350.f
      - pHelpButton->getSpriteGUIObject().getTextureRect().width / 2.f, 465.f));
  pHighscoreButton->setPositionGUIObject(sf::Vector2f(350.f
      - pHighscoreButton->getSpriteGUIObject().getTextureRect().width / 2.f, 365.f));

  //Objekte registrieren
  mpStateGUIManager->registerGUIObject(pExitButton);
  mpStateGUIManager->registerGUIObject(pCreditsButton);
  mpStateGUIManager->registerGUIObject(pStartButton);
  mpStateGUIManager->registerGUIObject(pOptionsButton);
  mpStateGUIManager->registerGUIObject(pLoadGame);
  mpStateGUIManager->registerGUIObject(pHelpButton);  
  mpStateGUIManager->registerGUIObject(pHighscoreButton);
}

void Menu::leaveState(){
  
  mpStateGUIManager->deleteGUIObjects();
  pExitButton = nullptr;
  pCreditsButton = nullptr;
  pStartButton = nullptr;
  pOptionsButton = nullptr;
  pLoadGame = nullptr;
  pHelpButton = nullptr;
  pHighscoreButton = nullptr;
  
  setNextState("");

  delete mpMainSettings;
  mpMainSettings = nullptr;

  mpMusicMenu->stop();
  delete mpMusicMenu;
  mpMusicMenu = nullptr;

}