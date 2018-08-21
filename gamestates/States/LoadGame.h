#ifndef _LOADGAME_H_
#define _LOADGAME_H_

#include <SFML\Graphics.hpp>
#include <SFML\Audio\Music.hpp>
///////////////////////////////
#include <iostream>
///////////////////////////////

#include "../../../GUI/GUISystem/GUIManager.h"
#include "../../../GUI/GUIObjects/Button.h"
#include "../../../GUI/GUIObjects/Textbox.h"
#include "../BasicState.h"
#include "../../Core/Achievements.h"
#include "../../Core/MainSettings.h"
#include "../../../Tools/BinaryData.h"
#include "../../../Tools/FileHandler.h"

class LoadGame :public BasicState{
public:
  //Konstruktoren (Deklaration)
  LoadGame();

  /********************************************************************
  * Konstruktorname: LoadGame
  * Parameter: RenderWindow *pRenderWindow, Event *pStateEvent,
  *            GUIManager *pGUI
  * R�ckgabe:  -
  * Dieser Konstruktor erstellt ein Objekt der Klasse LoadGame mit der
  * �bergabe des RenderWindow, des Events und eines GUI-Managers.
  ********************************************************************/
  LoadGame(sf::RenderWindow *pRenderWindow, sf::Event *pStateEvent,
    GUIManager *pGUI);

  //Destruktor (Deklaratation)
  virtual ~LoadGame();

  //Klassenmethoden (Deklaration), geerbt von der Basisklasse BasicState
  //Grundfunktionen zum Darstellen des Objektes
  void handleEvents();
  void update(float fFrametime);
  void render();

  //Spezifische Funktionen
  void enterState();
  void leaveState();

  /********************************************************************
  * Methodenname: loadSaveGame
  * Parameter: -
  * R�ckgabe:  -
  * Diese Funktion l�dt den aktuellen Spielstand aus .txt-Datei.
  ********************************************************************/
  void loadSaveGame();

  /********************************************************************
  * Methodenname: loadReachedAchievements
  * Parameter: -
  * R�ckgabe:  -
  * Diese Funktion l�dt die erreichten Achievements.
  ********************************************************************/
  void loadReachedAchievements();

private:
  //Klassenattribute
  GUIManager   *mpStateGUIManager;
  Achievements *mpSaveGame;
  Achievements *mpLoadedGame;
  Achievements *mpAchievements;
  MainSettings *mpMainSettings;
  sf::Music    *mpMusicMenu;

  //GUIObject Instanzen
  Button *pBackButton;
  Button *pLoadGame;
  Button *pContinueLevelTwo;
  Button *pContinueLevelThree;
  Textbox *pRequestPlayerName;


  sf::Text mLoadGameText[3];
  sf::Font mLoadGameFont;
  int      mLevel;
  int      mLanguageOptions;
};
#endif //LOADGAME_H