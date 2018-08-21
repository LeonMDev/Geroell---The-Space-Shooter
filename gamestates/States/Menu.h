#ifndef _MENU_H_
#define _MENU_H_

#include <SFML\Graphics.hpp>
#include <SFML\Audio\Music.hpp>
#include <iostream>

#include "../../../GUI/GUISystem/GUIManager.h"
#include "../../../GUI/GUIObjects/Button.h"
#include "../../../GUI/GUIObjects/Checkbox.h"
#include "../BasicState.h"
#include "../../Core/MainSettings.h"
#include "../../../Tools/BinaryData.h"

class Menu :public BasicState{
public:
  //Konstruktor (Deklaration)
  Menu();

  /********************************************************************
  * Konstruktorname: Menu
  * Parameter: RenderWindow *pRenderWindow, Event *pStateEvent, 
  *            GUIManager *pGUI
  * Rückgabe:  -
  * Dieser Konstruktor erstellt ein Objekt der Klasse Menu mit der
  * Übergabe des RenderWindow, des Events und eines GUI-Managers.
  ********************************************************************/
  Menu(sf::RenderWindow *pRenderWindow, sf::Event *pStateEvent, 
      GUIManager *pGUI);

  //Destruktor (Deklaration)
  virtual ~Menu();

  //Klassenmethoden (Deklaration), geerbt von der Basisklasse BasicState
  //Grundfunktionen zum Darstellen des Objektes
  void update(float fFrametime);
  void render();
  void handleEvents();

  //Spezifische Funktionen
  void enterState();
  void leaveState();

private:
  //Klassenattribute
  GUIManager   *mpStateGUIManager;
  MainSettings *mpMainSettings;
  sf::Music    *mpMusicMenu;

  //GUIObject Instanzen
  Button *pExitButton;
  Button *pCreditsButton;
  Button *pStartButton;
  Button *pOptionsButton;
  Button *pLoadGame;
  Button *pHelpButton;
  Button *pHighscoreButton;

  int mLanguageOptions;
};
#endif //MENU_H