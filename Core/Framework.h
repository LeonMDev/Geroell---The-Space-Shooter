#ifndef _FRAMEWORK_H_
#define _FRAMEWORK_H_

#include <SFML\Graphics.hpp>
#include <sstream>

#include "../Manager/StateManager.h"
#include "../GameObjects/Player.h"

class Framework{
public:
  //Konstruktor (Deklaration)
  Framework();        

  //Destruktor (Deklaration)
  virtual ~Framework();

  //Klassenmethoden (Deklaration)

  /********************************************************************
  * Methodenname: runApplication
  * Parameter: -
  * R�ckgabe:  -
  * Diese Funktion f�hrt das Hauptprogramm in einer Schleife aus, in der
  * die drei Grundfunktionen (handleEvents, update und render)
  * aufgerufen werden.
  ********************************************************************/
  void runApplication();

private:
  //Klassenmethoden (Deklaration)
  //Grundfunktionen

  /********************************************************************
  * Methodenname: handleEvents
  * Parameter: -
  * R�ckgabe:  -
  * Diese Funktion verwaltet Events wie Tasteneingaben etc. und ruft
  * die darauf agierenden Funktionen auf.
  ********************************************************************/
  void handleEvents();

  /********************************************************************
  * Methodenname: update
  * Parameter: -
  * R�ckgabe:  -
  * Diese Funktion aktualisiert Methoden und Objekte zur Laufzeit und
  * passt Ver�nderungen an.
  ********************************************************************/
  void update();

  /********************************************************************
  * Methodenname: render
  * Parameter: -
  * R�ckgabe:  -
  * Diese Funktion zeichnet die Objekte.
  ********************************************************************/
  void render();

  //Spezifische Funktionen

  /********************************************************************
  * Methodenname: calculateFrametime
  * Parameter: -
  * R�ckgabe:  -
  * Diese Funktion berechnet die Frametime.
  ********************************************************************/
  void calculateFrametime();

  //Klassenattribute
  sf::RenderWindow *mpMainWindow;
  sf::Event        *mpMainEvent;
  sf::Clock        *mpMainClock;

  StateManager     *mpMainStateManager;
  
  float mFrametime;
};
#endif //FRAMEWORK_H