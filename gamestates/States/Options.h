#ifndef _OPTIONS_H_
#define _OPTIONS_H_

#include <SFML\Graphics.hpp>
#include <SFML\Audio\Music.hpp>
#include <sstream>

#include "../../../GUI/GUISystem/GUIManager.h"
#include "../../../GUI/GUIObjects/Button.h"
#include "../../../GUI/GUIObjects/Checkbox.h"
#include "../../../GUI/GUIObjects/Textbox.h"
#include "../BasicState.h"
#include "../../Core/MainSettings.h"
#include "../../../Tools/BinaryData.h"

class Options :public BasicState{
public:
  //Konstruktoren (Deklaration)
  Options();

  /********************************************************************
  * Konstruktorname: Options
  * Parameter: RenderWindow *pRenderWindow, Event *pStateEvent,
  *            GUIManager *pGUI
  * Rückgabe:  -
  * Dieser Konstruktor erstellt ein Objekt der Klasse Options mit der
  * Übergabe des RenderWindow, des Events und eines GUI-Managers.
  ********************************************************************/
  Options(sf::RenderWindow *pRenderWindow, sf::Event *pStateEvent,
      GUIManager *pGUI);

  //Destruktor (Deklaration)
  virtual ~Options();

  //Klassenmethoden (Deklaration), geerbt von der Basisklasse BasicState
  //Grundfunktionen zum Darstellen des Objektes
  void handleEvents();
  void update(float fFrametime);
  void render();

  //Spezifische Funktionen 
  void enterState();
  void leaveState();

private:
  //Klassenattribute
  GUIManager   *mpStateGUIManager;
  MainSettings *mpOptionsSettings;
  sf::Music    *mpMusicMenu;

  //GUIObject Instanzen
  Checkbox     *mpMusicToggle;
  Checkbox     *mpSoundEffToggle;
  Button       *pEnglishButton;
  Button       *pGermanButton;
  Button       *pFrenchButton;
  Button       *mpBackButton;
  Button       *mpSaveApplyButton;
  Textbox      *pMusicVolumeTextbox;
  Textbox      *pSoundEffVolumeTextbox;

  sf::Text mOptionsText[10];
  sf::Font mOptionsFont;

  int mLanguageOptions;

};
#endif //OPTIONS_H