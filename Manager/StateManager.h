#ifndef _STATEMANAGER_H_
#define _STATEMANAGER_H_

#include <SFML\Graphics.hpp>
#include <map>
#include <iostream>

#include "../../GUI/GUISystem/GUIManager.h"
#include "../GameStates/BasicState.h"
#include "../Core/MainSettings.h"
#include "../Core/PlaySettings.h"
#include "../../Tools/BinaryData.h"

class StateManager{
public:
  //Konstruktoren (Deklaration)
  StateManager();

  /********************************************************************
  * Konstruktorname: StateManager
  * Parameter: RenderWindow *pRenderWindow, Event *pStateEvent
  * R�ckgabe:  -
  * Dieser Konstruktor erstellt ein Objekt der Klasse StateManager mit der
  * �bergabe des RenderWindow und des Events
  ********************************************************************/
  StateManager(sf::RenderWindow *pRenderWindow, sf::Event *pStateEvent);

  //Destruktor (Deklaration)
  virtual ~StateManager();

  //Klassenmethoden
  //Grundfunktionen zum Darstellen des Objektes
  void handleEvents();
  void update(float fFrametime);
  void render();

  //Spezifische Funktionen

  /********************************************************************
  * Methodenname: addState
  * Parameter: string sStateID, BasicState* state
  * R�ckgabe:  -
  * Diese Funktion integriert Zust�nde in das Programm.
  ********************************************************************/
  void addState(std::string sStateID, BasicState* state);

  /********************************************************************
  * Methodenname: setState
  * Parameter: string sStateID
  * R�ckgabe:  -
  * Diese Funktion ruft den Zustand mit der �bergebenen stateID auf.
  ********************************************************************/
  void setState(std::string sStateID);

  /********************************************************************
  * Methodenname: loadSettings
  * Parameter: -
  * R�ckgabe:  -
  * Diese Funktion l�dt die Main- und PlaySettings mit Defaultwerten aus
  * den jeweiligen .bin-Dateien, sobald StateManager initiiert wird.
  ********************************************************************/
  void loadSettings();

  /********************************************************************
  * Methodenname: clearStateMap();;
  * Parameter: -
  * R�ckgabe:  -
  * Diese Funktion iteriert �ber die Map der States und ruft
  * entsprechend f�r die jeweiligen Pointer die "delete" Methode auf,
  * um den durch die Erzeugung der States allokierten Speicher wieder freizugeben.
  * Zus�tzlich wird die Map im Anschluss mit der clear()-Methode geleert;
  ********************************************************************/
  void clearStateMap();


  //Globale Klassenvariablen
  std::map<std::string, BasicState*>           gStateMap;
  std::map<std::string, BasicState*>::iterator gStateIt;

private:
  //Klassenattribute
  sf::RenderWindow *mpStateWindow;
  sf::Event        *mpStateEvent;
  BasicState       *mpCurrentState;
  GUIManager       *mpMainGUIManager;
  MainSettings     *mpMainSettings;
  PlaySettings     *mpPlaySettings;  

  sf::Sprite  mBackgroundSprite;
  sf::Texture mBackgroundTexture;
  std::string mCurrentStateIDString;
};
#endif //STATEMANAGER_H