/***************************************************************************
* Klassenname BasicState
* Date
* Autor(en) Hein, Köhler, Meister
*
* Diese Klasse verwaltet die Objekte vom Typ BasicState. Sie ist die
* Basis-Klasse der verschiedenen Zustände des Programms.
**************************************************************************/

#include "BasicState.h"

//Konstruktor (Definition)
BasicState::BasicState(){

}

//Destruktor (Definition)
BasicState::~BasicState(){
}

//Klassenmethoden (Definition)
//Grundfunktionen
void BasicState::handleEvents(){

}

void BasicState::update(float fFrametime){

}

void BasicState::render(){

}

//Setter
void BasicState::setNextState(std::string sNextStateID){
  gNextState = sNextStateID;
}

//Getter
std::string BasicState::getNextState(){
  return gNextState;
}

//Spezifische Funktionen
void BasicState::enterState(){

}

void BasicState::leaveState(){

}