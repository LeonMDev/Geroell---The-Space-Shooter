#ifndef _PREPLAYSTATE_H_
#define _PREPLAYSTATE_H_

#include <SFML\Audio\Music.hpp>

#include "../../../GUI/GUISystem/GUIManager.h"
#include "../BasicState.h"
#include "../../../GUI/GUIObjects/Button.h"
#include "../../../GUI/GUIObjects/Textbox.h"
#include "../../Core/Achievements.h"
#include "../../Core/MainSettings.h"
#include "../../../Tools/FileHandler.h"
#include "../../../Tools/BinaryData.h"

class PrePlayState :public BasicState{
public:
  //Konstruktoren (Deklaration)
  PrePlayState();

  /********************************************************************
  * Konstruktorname: PrePlayState
  * Parameter: RenderWindow *pRenderWindow, Event *pStateEvent,
  *            GUIManager *pGUI
  * Rückgabe:  -
  * Dieser Konstruktor erstellt ein Objekt der Klasse PrePlayState mit der
  * Übergabe des RenderWindow, des Events und eines GUI-Managers.
  ********************************************************************/
  PrePlayState(sf::RenderWindow *pRenderWindow, sf::Event *pStateEvent,
      GUIManager *pGUI);

  //Destruktor (Deklaration)
  virtual ~PrePlayState();

  //Klassenmethoden (Deklaration), geerbt von der Basisklasse BasicState
  //Grundfunktionen zum Darstellen des Objektes
  void handleEvents();
  void update(float fFrametime);
  void render();

  //Setter
  void setLevel(int iLevel);

  //Getter
  int getLevel();

  //Spezifische Funktionen
  void enterState();
  void leaveState();

  /********************************************************************
  * Methodenname: createAchievements
  * Parameter: -
  * Rückgabe:  -
  * Diese Funktion erstellt ein Objekt vom Typ Achievememts mit 
  * Default-Werten.
  ********************************************************************/
  void createAchievements();

private:
  //Klassenattribute
  GUIManager   *mpStateGUIManager;
  Achievements *mpAchievements;
  MainSettings *mpMainSettings;
  sf::Music    *mpMusicMenu;

  //GUIObject Instanzen
  Button  *pBackButton;
  Button  *pControlSettingsButton;
  Button  *pStartButton;
  Textbox *pRequestPlayerName;

  sf::Text mPreGameText[4];
  sf::Font mPreGameFont;
  int      mLevel;
  int      mLanguageOptions;
};
#endif //PREPLAYSTATE_H