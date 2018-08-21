#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <sstream>
#include <iostream>

#include "../../../GUI/GUISystem/GUIManager.h"
#include "../../../GUI/GUIObjects/Button.h"
#include "../BasicState.h"
#include "../../Core/Achievements.h"
#include "../../Core/MainSettings.h"
#include "../../../Tools/FileHandler.h"
#include "../../../Tools/BinaryData.h"

class GameOver :public BasicState{
public:
  //Konstruktor (Deklaration)
  GameOver();

  /********************************************************************
  * Konstruktorname: GameOver
  * Parameter: RenderWindow *pRenderWindow, Event *pStateEvent,
  *            GUIManager *pGUI
  * Rückgabe:  -
  * Dieser Konstruktor erstellt ein Objekt der Klasse GameOver
  * mit der Übergabe des RenderWindow, des Events und eines
  * GUI-Managers.
  ********************************************************************/
  GameOver(sf::RenderWindow *pRenderWindow, sf::Event *pStateEvent,
      GUIManager *pGUI);

  //Destruktor (Deklaration)
  virtual ~GameOver();

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

private:
  //Klassenattribute
  GUIManager   *mpStateGUIManager;
  Achievements *mpAchievements;
  MainSettings *mpMainSettings;
  sf::Music    *mpMusicGameOver;

  //GUIObject Instanzen
  Button *pBackButton;

  sf::Text mGameOverText[4];
  sf::Text mAchievementsText[3];
  sf::Font mGameOverFont;

  float       mReachedScore;
  int         mCurrentLevel;
  int         mLanguageOptions;
  std::string mPlayerName;
};
#endif //GAMEOVER_H