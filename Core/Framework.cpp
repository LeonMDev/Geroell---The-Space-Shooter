/***************************************************************************
* Klassenname Framework
* Date
* Autor(en) Hein, Köhler, Meister
*
* Diese Klasse stellt das Hauptprogramm dar. Hier wird die Hauptschleife
* des Projektes aufgerufen, mit der das Spiel gezeichnet und ausgeführt
* wird.
**************************************************************************/
#include "Framework.h"

//Konstruktor (Definition)
Framework::Framework(){

  mpMainWindow = new sf::RenderWindow(sf::VideoMode(1280, 720, 32),
      "Geröll - The Space Game", sf::Style::Default);
  mpMainEvent = new sf::Event;

  mpMainStateManager = new StateManager(mpMainWindow, mpMainEvent);

  mpMainClock = new sf::Clock;
  mpMainClock->restart();
}

//Destruktor (Definition)
Framework::~Framework(){

  delete mpMainWindow;
  delete mpMainEvent;
  delete mpMainStateManager;
  delete mpMainClock;

  mpMainWindow       = nullptr;
  mpMainEvent        = nullptr;
  mpMainStateManager = nullptr;
  mpMainClock        = nullptr;
}

//Klassenmethoden (Definition) /public
void Framework::runApplication(){
  while (mpMainWindow->isOpen()){
    handleEvents();
    update();
    render();
  }
}

//Klassenmethoden (Definition)
//Grundfunktionen
void Framework::handleEvents(){
  while (mpMainWindow->pollEvent(*mpMainEvent)){
    if (mpMainEvent->type == sf::Event::Closed){
      mpMainWindow->close();
    }
    mpMainStateManager->handleEvents();
  }
}

void Framework::update(){
  calculateFrametime();
  mpMainStateManager->update(mFrametime);
}

void Framework::render(){
  mpMainWindow->clear();
  mpMainStateManager->render();
  mpMainWindow->display();
}

//Spezifische Funktionen
void Framework::calculateFrametime(){
  mFrametime = static_cast<float>(mpMainClock->getElapsedTime().asSeconds());
  mpMainClock->restart();
}