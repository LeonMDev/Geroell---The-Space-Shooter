#ifndef _HELP_H_
#define _HELP_H_

#include <SFML\Graphics.hpp>
#include <SFML\Audio\Music.hpp>
///////////////////////////////
#include <iostream>
///////////////////////////////

#include "../../../GUI/GUISystem/GUIManager.h"
#include "../../../GUI/GUIObjects/Button.h"
#include "../BasicState.h"
#include "../../Core/MainSettings.h"
#include "../../../Tools/BinaryData.h"

class Help :public BasicState{
public:
  //Konstruktor (Deklaration)
  Help();

  /********************************************************************
  * Konstruktorname: Credits
  * Parameter: RenderWindow *pRenderWindow, Event *pStateEvent,
  *            GUIManager *pGUI
  * Rückgabe:  -
  * Dieser Konstruktor erstellt ein Objekt der Klasse Credits mit der
  * Übergabe des RenderWindow, des Events und eines GUI-Managers.
  ********************************************************************/
  Help(sf::RenderWindow *pRenderWindow, sf::Event *pStateEvent,
    GUIManager *pGUI);

  //Destruktor (Deklaration)
  virtual ~Help();

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
  sf::Texture  *mpPanelTexture;
  sf::Sprite   *mpPanelSprite;
  sf::Texture  *mpHealthBonusTexture;
  sf::Sprite   *mpHealthBonusSprite;
  sf::Texture  *mpLowUpgradeTexture;
  sf::Sprite   *mpLowUpgradeSprite;
  sf::Texture  *mpHighUpgradeTexture;
  sf::Sprite   *mpHighUpgradeSprite;

  //GUIObject Instanzen
  Button *pBackButton;

  sf::Text mHelpText[6];
  sf::Font mHelpFont;
  sf::VertexArray mQuads;
  sf::VertexArray mLines;
  int mLanguageOptions;
};
#endif //HELP_H