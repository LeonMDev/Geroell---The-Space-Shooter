/***************************************************************************
* Klassenname StateManager
* Date
* Autor(en) Hein, Köhler, Meister
*
* Diese Klasse verwaltet alle State-Objekte. Sie wird bei Programmstart
* in der Klasse Framework initialisiert.
**************************************************************************/
#include "StateManager.h"

#include "../GameStates/States/Menu.h"
#include "../GameStates/States/Credits.h"
#include "../GameStates/States/Options.h"
#include "../GameStates/States/PrePlayState.h"
#include "../GameStates/States/LoadGame.h"
#include "../GameStates/States/ControlSettings.h"
#include "../GameStates/States/LevelOne.h"
#include "../GameStates/States/LevelTwo.h"
#include "../GameStates/States/LevelThree.h"
#include "../GameStates/States/GameOver.h"
#include "../GameStates/States/LevelSolved.h"
#include "../GameStates/States/Highscore.h"
#include "../GameStates/States/Help.h"

//Konstruktoren (Definition)
StateManager::StateManager(){
}

StateManager::StateManager(sf::RenderWindow *pRenderWindow, sf::Event *pStateEvent):
    mpStateWindow(pRenderWindow), mpStateEvent(pStateEvent){
  loadSettings();
  
  //Hintergrund-Textur laden und entsprechend das Sprite setzen
  if (!mBackgroundTexture.loadFromFile("Data/Textures/background.jpg")){
    std::string error("Could not load Texture for mBackgroundTexture from: ");
    error.append("Data/Textures/background.jpg");
    error.append("\n");
    error.append("Check data path and image file formats!");
    throw std::exception(error.c_str());
  }
  mBackgroundSprite.setTexture(mBackgroundTexture);

  //Basis-Instanz des derzeitigen "Zustands" initialisieren
  mpCurrentState   = new BasicState();

  //GUIManager-Instanz initialisieren
  mpMainGUIManager = new GUIManager(pRenderWindow, pStateEvent);

  //Zustände erstellen
  //1.Schritt: Instanzen initialisieren
  Menu *pMenu            = new Menu(pRenderWindow, pStateEvent, mpMainGUIManager);
  Credits *pCredits      = new Credits(pRenderWindow, pStateEvent, mpMainGUIManager);
  Options *pOptions      = new Options(pRenderWindow, pStateEvent, mpMainGUIManager);
  PrePlayState *pPreGame = new PrePlayState(pRenderWindow, pStateEvent, mpMainGUIManager);
  LoadGame *pLoadGame    = new LoadGame(pRenderWindow, pStateEvent, mpMainGUIManager);
  ControlSettings *pControlSettings = new ControlSettings(pRenderWindow, pStateEvent, mpMainGUIManager);
  LevelOne *pLevelOne    = new LevelOne(pRenderWindow, pStateEvent, mpMainGUIManager);
  LevelTwo *pLevelTwo    = new LevelTwo(pRenderWindow, pStateEvent, mpMainGUIManager);
  LevelThree *pLevelThree = new LevelThree(pRenderWindow, pStateEvent, mpMainGUIManager);
  GameOver *pGameOver    = new GameOver(pRenderWindow, pStateEvent, mpMainGUIManager);
  LevelSolved *pLevelSolved = new LevelSolved(pRenderWindow, pStateEvent, mpMainGUIManager);
  Highscore *pHighscore = new Highscore(pRenderWindow, pStateEvent, mpMainGUIManager);
  Help *pHelp = new Help(pRenderWindow, pStateEvent, mpMainGUIManager);

  //2.Schritt: Zustände/ Instanzen über IDs der Map(global) hinzufügen:
  addState("State/Menu", pMenu);
  addState("State/Credits", pCredits);
  addState("State/Options", pOptions);
  addState("State/PreGame", pPreGame);
  addState("State/LoadGame", pLoadGame);
  addState("State/ControlSettings", pControlSettings);
  addState("State/LevelOne", pLevelOne);
  addState("State/LevelTwo", pLevelTwo);
  addState("State/LevelThree", pLevelThree);
  addState("State/GameOver", pGameOver);
  addState("State/LevelSolved", pLevelSolved);
  addState("State/Highscore", pHighscore);
  addState("State/Help", pHelp);

  //Default-State setzen, der bei Programmstart aufgerufen wird
  setState("State/Menu");
}

//Destruktor (Definition)
StateManager::~StateManager(){

  clearStateMap();
  delete mpCurrentState;
  mpCurrentState = nullptr;
  
  delete mpMainGUIManager;
  delete mpMainSettings;
  delete mpPlaySettings;

  mpMainGUIManager = nullptr;
  mpMainSettings   = nullptr;
  mpPlaySettings   = nullptr;

  
}

//Klassenmethoden (Definition)
//Grundfunktionen
void StateManager::handleEvents(){
  if (mpCurrentState != NULL){
    mpMainGUIManager->handleGUI();
    mpCurrentState->handleEvents();
  }
}

void StateManager::update(float fFrametime){
  if (mpCurrentState != NULL){
    if (mpCurrentState->getNextState().length() != NULL){
      setState(mpCurrentState->gNextState);
    }
    mpMainGUIManager->updateGUI();
    mpCurrentState->update(fFrametime);  
    }
}

void StateManager::render(){
  if (mpCurrentState != NULL){
    mpStateWindow->draw(mBackgroundSprite);
    mpCurrentState->render();
    mpMainGUIManager->renderGUI();
  }
}

//Spezifische Funktionen
void StateManager::addState(std::string sStateID, BasicState* state){
  gStateIt = gStateMap.find(sStateID);
  if (gStateIt != gStateMap.end()){
    std::string error("State mit ID: ");
    error.append(sStateID);
    error.append(" existiert bereits.");
    throw std::exception(error.c_str());
  }
  gStateMap[sStateID] = state;
}

void StateManager::setState(std::string sStateID){
  gStateIt = gStateMap.find(sStateID);
  if (gStateIt != gStateMap.end()){
    if (gStateIt->second != NULL){
      mpCurrentState->leaveState();
      mpCurrentState = gStateIt->second;
      mpCurrentState->enterState();
    }
  }
}

void StateManager::loadSettings(){
  /*Bei Programmstart MainSettings laden. Sollten diese nicht vorhanden sein,
    werden neue Settings mit Standardwerten erstellt und gespeichert.*/
  mpMainSettings  = new MainSettings();
  *mpMainSettings = BinaryData::readBinaryFile<MainSettings>("Data/Bin/Settings/mainsettings.bin");

  /*MainSettings bei Start mit Standardwerten aufrufen und bisher gespeicherte
    mainsettings.bin überschreiben, damit bei Programmstart immer die Defaultwerte gelten.*/
  mpMainSettings->setMusicEnabled(true);
  mpMainSettings->setSoundEffEnabled(true);
  mpMainSettings->setMusicVolume(10);
  mpMainSettings->setSoundEffVolume(10);
  mpMainSettings->setLanguage(1);

  BinaryData::writeBinaryFile<MainSettings>("Data/Bin/Settings/mainsettings.bin", 
      *mpMainSettings);

  if (mpMainSettings == NULL){
    mpMainSettings = new MainSettings(10, true, 10, true, 1);
    BinaryData::writeBinaryFile<MainSettings>("Data/Bin/Settings/mainsettings.bin", 
        *mpMainSettings);
  }

  /*Bei Programmstart PlaySettings laden. Sollten diese nicht vorhanden sein,
    werden neue Settings mit Standardwerten erstellt und gespeichert.*/
  mpPlaySettings = new PlaySettings();
  *mpPlaySettings = BinaryData::readBinaryFile<PlaySettings>("Data/Bin/Settings/playsettings.bin");

  if (mpPlaySettings == NULL){
    mpPlaySettings = new PlaySettings(sf::Keyboard::Left, sf::Keyboard::Right, 
        sf::Keyboard::Space);
    BinaryData::writeBinaryFile<PlaySettings>("Data/Bin/Settings/playsettings.bin",
        *mpPlaySettings);
  }

  /*PlaySettings bei Start mit Standardwerten aufrufen und bisher gespeicherte
    playsettings.bin überschreiben, damit bei Programmstart immer die Default-Werte
    gelten*/
  mpPlaySettings->setKeyPlayerMoveLeft(sf::Keyboard::Left);
  mpPlaySettings->setKeyPlayerMoveRight(sf::Keyboard::Right);
  mpPlaySettings->setKeyPlayerFireWeapon(sf::Keyboard::Space);

  BinaryData::writeBinaryFile<PlaySettings>("Data/Bin/Settings/playsettings.bin",
      *mpPlaySettings);
}


void StateManager::clearStateMap(){
  //Allokierten Speicher der GUIObjects freigeben:
  for (gStateIt = gStateMap.begin(); gStateIt != gStateMap.end(); ++gStateIt)
  {
    delete gStateIt->second;
    gStateIt->second = nullptr;
  }
  mpCurrentState = NULL;

  //Map leeren:
  gStateMap.clear();
}