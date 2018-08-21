#ifndef _CONTROLSETTINGS_H_
#define _CONTROLSETTINGS_H_

#include <SFML\Graphics.hpp>
#include <SFML\Audio\Music.hpp>

#include "../../../GUI/GUISystem/GUIManager.h"
#include "../../../GUI/GUIObjects/Button.h"
#include "../../../GUI/GUIObjects/Textbox.h"
#include "../BasicState.h"
#include "../../Core/PlaySettings.h"
#include "../../Core/MainSettings.h"
#include "../../../Tools/BinaryData.h"

class ControlSettings :public BasicState{
public:
  //Konstruktoren (Deklaration)
  ControlSettings();

  /********************************************************************
  * Konstruktorname: ControlSettings
  * Parameter: RenderWindow *pRenderWindow, Event *pStateEvent,
  *            GUIManager *pGUI
  * Rückgabe:  -
  * Dieser Konstruktor erstellt ein Objekt der Klasse ControlSettings 
  * mit der Übergabe des RenderWindow, des Events und eines 
  * GUI-Managers.
  ********************************************************************/
  ControlSettings(sf::RenderWindow *pRenderWindow, sf::Event *pStateEvent,
      GUIManager *pGUI);

  //Destruktor (Deklaration)
  virtual ~ControlSettings();

  //Klassenmethoden (Deklaration), geerbt von der Basisklasse BasicState
  //Grundfunktionen zum Darstellen des Objektes
  void handleEvents();
  void update(float fFrametime);
  void render();

  //Setter
  void setKeyMoveLeft(sf::Keyboard::Key keyMoveLeft);
  void setKeyMoveRight(sf::Keyboard::Key keyMoveRight);
  void setKeyFireWeapon(sf::Keyboard::Key keyFireWeapon);

  //Getter
  const sf::Keyboard::Key getKeyMoveLeft();
  const sf::Keyboard::Key getKeyMoveRight();
  const sf::Keyboard::Key getKeyFireWeapon();

  //Spezifische Funktionen
  void enterState();
  void leaveState();

private:
  //Klassenattribute
  GUIManager   *mpStateGUIManager;
  PlaySettings *mpPlaySettings;
  MainSettings *mpMainSettings;
  sf::Music    *mpMusicMenu;

  //GUIObject Instanzen
  Button  *pBackButton;
  Button  *pSaveApplyButton;
  Textbox *pMoveLeft;
  Textbox *pMoveRight;
  Textbox *pFireWeapon;

  sf::Text mControlSettingsText[5];
  sf::Font mControlSettingsFont;

  sf::Keyboard::Key mKeySetMoveLeft;
  sf::Keyboard::Key mKeySetMoveRight;
  sf::Keyboard::Key mKeySetFireWeapon;

  std::string mMoveLeftString;
  std::string mMoveRightString;
  std::string mFireWeaponString;
  int         mLanguageOptions;
};
#endif //CONTROLSETTINGS_H