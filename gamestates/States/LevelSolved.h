#ifndef _LEVELSOLVED_H_
#define _LEVELSOLVED_H_

#include <SFML\Graphics.hpp>
#include <SFML\Audio\Music.hpp>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>

#include "../../../GUI/GUISystem/GUIManager.h"
#include "../../../GUI/GUIObjects/Button.h"
#include "../BasicState.h"
#include "../../Core/Achievements.h"
#include "../../Core/MainSettings.h"
#include "../../../Tools/BinaryData.h"
#include "../../../Tools/FileHandler.h"

class LevelSolved :public BasicState{
public:
  //Konstruktoren (Deklaration)
  LevelSolved();

  /********************************************************************
  * Konstruktorname: LevelSolved
  * Parameter: RenderWindow *pRenderWindow, Event *pStateEvent,
  *            GUIManager *pGUI
  * Rückgabe:  -
  * Dieser Konstruktor erstellt ein Objekt der Klasse GameOver
  * mit der Übergabe des RenderWindow, des Events und eines
  * GUI-Managers.
  ********************************************************************/
  LevelSolved(sf::RenderWindow *pRenderWindow, sf::Event *pStateEvent,
      GUIManager *pGUI);

  //Destruktor (Deklaration)
  virtual ~LevelSolved();

  //Klassenmethoden (Deklaration), geerbt von der Basisklasse BasicState
  //Grundfunktionen zum Darstellen des Objektes
  void handleEvents();
  void update(float fFrametime);
  void render();

  //Spezifische Funktionen
  void enterState();
  void leaveState();

  /********************************************************************
  * Methodenname: loadReachedAchievements
  * Parameter: -
  * Rückgabe:  -
  * Diese Funktion lädt die Achievements Datei zur weiteren Verwendung.
  ********************************************************************/
  void loadReachedAchievements();

  /********************************************************************
  * Methodenname: saveGame
  * Parameter: -
  * Rückgabe:  -
  * Diese Funktion speichert den aktuellen Spielstand.
  ********************************************************************/
  void saveGame();

private:
  //Klassenattribute
  GUIManager   *mpStateGUIManager;
  Achievements *mpAchievements;
  Achievements *mpSaveGame;
  MainSettings *mpMainSettings;
  sf::Music    *mpMusicMenu;

  //GUIObject Instanzen
  Button *pBackButton;
  Button *pNextLevelTwo;
  Button *pNextLevelThree;
  Button *pSaveGame;
  Button *pHighScoreList;

  sf::Text mLevelSolvedText[7];
  sf::Text mAchievementsText[3];
  sf::Font mLevelSolvedFont;

  float       mReachedScore;
  int         mSolvedLevel;
  int         mLanguageOptions;
  std::string mPlayerName;
};

#endif //LEVELSOLVED_H