#ifndef _CREDITS_H_
#define _CREDITS_H_

#include <SFML\Graphics.hpp>
#include <SFML\Audio\Music.hpp>

#include "../../../GUI/GUISystem/GUIManager.h"
#include "../../../GUI/GUIObjects/Button.h"
#include "../BasicState.h"
#include "../../Core/MainSettings.h"
#include "../../../Tools/BinaryData.h"

class Credits :public BasicState{
public:
  //Konstruktor (Deklaration)
  Credits();

  /********************************************************************
  * Konstruktorname: Credits
  * Parameter: RenderWindow *pRenderWindow, Event *pStateEvent, 
  *            GUIManager *pGUI
  * Rückgabe:  -
  * Dieser Konstruktor erstellt ein Objekt der Klasse Credits mit der
  * Übergabe des RenderWindow, des Events und eines GUI-Managers.
  ********************************************************************/
  Credits(sf::RenderWindow *pRenderWindow, sf::Event *pStateEvent, 
      GUIManager *pGUI);

  //Destruktor (Deklaration)
  virtual ~Credits();

  //Klassenmethoden (Deklaration), geerbt von der Basisklasse BasicState
  //Grundfunktionen zum Darstellen des Objektes
  void update(float fFrametime);
  void render();
  void handleEvents();

  //Spezifische Funktionen
  void createPanelGraphic();
  void enterState();
  void leaveState();

private:
  //Klassenattribute
  GUIManager   *mpStateGUIManager;
  MainSettings *mpMainSettings;
  sf::Music    *mpMusicMenu;

  //GUIObject Instanzen
  Button *pBackButton;

  sf::Text mCreditsText[4];
  sf::Font mCreditsFont;
  sf::VertexArray mQuads;
  sf::VertexArray mLines;
  int         mLanguageOptions;
};
#endif //CREDITS_H