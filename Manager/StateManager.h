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
  * Rückgabe:  -
  * Dieser Konstruktor erstellt ein Objekt der Klasse StateManager mit der
  * Übergabe des RenderWindow und des Events
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
  * Rückgabe:  -
  * Diese Funktion integriert Zustände in das Programm.
  ********************************************************************/
  void addState(std::string sStateID, BasicState* state);

  /********************************************************************
  * Methodenname: setState
  * Parameter: string sStateID
  * Rückgabe:  -
  * Diese Funktion ruft den Zustand mit der übergebenen stateID auf.
  ********************************************************************/
  void setState(std::string sStateID);

  /********************************************************************
  * Methodenname: loadSettings
  * Parameter: -
  * Rückgabe:  -
  * Diese Funktion lädt die Main- und PlaySettings mit Defaultwerten aus
  * den jeweiligen .bin-Dateien, sobald StateManager initiiert wird.
  ********************************************************************/
  void loadSettings();

  /********************************************************************
  * Methodenname: clearStateMap();;
  * Parameter: -
  * Rückgabe:  -
  * Diese Funktion iteriert über die Map der States und ruft
  * entsprechend für die jeweiligen Pointer die "delete" Methode auf,
  * um den durch die Erzeugung der States allokierten Speicher wieder freizugeben.
  * Zusätzlich wird die Map im Anschluss mit der clear()-Methode geleert;
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