#ifndef _LEVELTHREE_H_
#define _LEVELTHREE_H_

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <sstream>
#include <iostream>

#include "../../../GUI/GUISystem/GUIManager.h"
#include "../../../GUI/GUIObjects/Button.h"
#include "../BasicState.h"
#include "../../Manager/AsteroidManager.h"
#include "../../Manager/BonusManager.h"
#include "../../GameObjects/Player.h"
#include "../../Core/CollisionSystem.h"
#include "../../Core/Achievements.h"
#include "../../Core/MainSettings.h"
#include "../../../Tools/BinaryData.h"
#include "../../../Tools/FileHandler.h"
#include "../../../Tools/Chronometer.h"

class LevelThree : public BasicState{
public:
  //Konstruktoren (Deklaration)
  LevelThree();

  /********************************************************************
  * Konstruktorname: LevelOne
  * Parameter: RenderWindow *pRenderWindow, Event *pStateEvent,
  *            GUIManager *pGUI
  * Rückgabe:  -
  * Dieser Konstruktor erstellt ein Objekt der Klasse LevelOne
  * mit der Übergabe des RenderWindow, des Events und eines
  * GUI-Managers.
  ********************************************************************/
  LevelThree(sf::RenderWindow *pRenderWindow, sf::Event *pStateEvent,
    GUIManager *pGUI);

  //Destruktor (Deklaration)
  virtual ~LevelThree();

  //Klassenmethoden (Deklaration), geerbt von der Basisklasse BasicState
  //Grundfunktionen zum Darstellen des Objektes
  void handleEvents();
  void update(float fFrametime);
  void render();

  //Setter
  void setAvailableTime(float fAvailableTime);
  void setPauseEnabled(bool bEnablePause);

  //Getter
  float getAvailableTime();
  bool getPauseEnabled();

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
  * Methodenname: saveReachedAchievements
  * Parameter: -
  * Rückgabe:  -
  * Diese Funktion speichert die erreichten Achievements.
  ********************************************************************/
  void saveReachedAchievements();

  /********************************************************************
  * Methodenname: loadPauseMenu
  * Parameter: -
  * Rückgabe:  -
  * Diese Funktion lädt das Pausenmenü.
  ********************************************************************/
  void loadPauseMenu();
  void deletePauseMenu();

  /********************************************************************
  * Methodenname: getFloatPrecision
  * Parameter: double dValue, double dPrecision
  * Rückgabe:  double
  * Diese Funktion berechnet die Nachkommastellen bzw. Floatpräzision.
  ********************************************************************/
  double getFloatPrecision(double dValue, double dPrecision);

  /********************************************************************
  * Methodenname: updateRemainingTime
  * Parameter: float fAvailableTime
  * Rückgabe:  -
  * Diese Funktion berechnet die verbleibende Spielzeit.
  ********************************************************************/
  void updateRemainingTime(float fAvailableTime);

private:
  //Klassenattribute
  GUIManager      *mpStateGUIManager;
  Achievements    *mpAchievements;
  Player          *mpPlayer;
  AsteroidManager *mpAsteroidManager;
  BonusManager    *mpBonusManager;
  CollisionSystem *mpCollisionSystem;
  MainSettings    *mpMainSettings;

  sf::Texture *mpMouseTexture;
  sf::Sprite  *mpMouseSprite;
  sf::Texture *mpBackgroundTextureLevelThree;
  sf::Sprite  *mpBackgroundSpriteLevelThree;
  sf::Texture *mpPanelTexture;
  sf::Sprite  *mpPanelSprite;
  sf::Text    *mpPauseMenuText;
  sf::Music   *mpMusicLevelThree;

  sf::Clock                *mpPauseClock;
  sfClockTool::Chronometer *mpChronometer;
  sf::Text                 *mpTimeRemainingText;
  sf::Font                 *mpLevelThreeFont;

  //GUIObject Instanzen
  Button *pBackButton;
  Button *pContinueButton;
  Button *pExitButton;

  float mAvailableTime;
  bool  mPause;
  int   mLanguageOptions;
};
#endif //LEVELTHREE_H