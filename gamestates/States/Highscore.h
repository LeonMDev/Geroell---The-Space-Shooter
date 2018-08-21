#ifndef _HIGHSCORE_H_
#define _HIGHSCORE_H_

#include <SFML\Graphics.hpp>
#include <SFML\Audio\Music.hpp>
#include <vector>
#include <string>
#include <fstream>

#include "..\..\..\GUI\GUISystem\GUIManager.h"
#include "..\..\..\GUI\GUIObjects\Button.h"
#include "..\BasicState.h"
#include "..\..\Core\MainSettings.h"
#include "..\..\..\Tools\BinaryData.h"

class Highscore : public BasicState{
public:
  //Konstruktoren (Deklaration)
  Highscore();

  /********************************************************************
  * Konstruktorname: Highscore
  * Parameter: RenderWindow *pRenderWindow, Event *pStateEvent,
  *            GUIManager *pGUI
  * Rückgabe:  -
  * Dieser Konstruktor erstellt ein Objekt der Klasse GameOver
  * mit der Übergabe des RenderWindow, des Events und eines
  * GUI-Managers.
  ********************************************************************/
  Highscore(sf::RenderWindow *pRenderWindow, sf::Event *pStateEvent,
      GUIManager *pGUI);

  //Destruktor (Deklaration)
  virtual ~Highscore();

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
  MainSettings *mpMainSettings;
  sf::Music    *mpMusicHighscore;

  //GUIObject Instanzen
  Button *pBackButton;

  std::vector<std::string> mHighscoreVector;
  sf::Text mHighscoreText[15];
  sf::Text mTitleText;
  sf::Font mHighscoreFont;
  int      mLanguageOptions;
};

#endif //HIGHSCORE_H