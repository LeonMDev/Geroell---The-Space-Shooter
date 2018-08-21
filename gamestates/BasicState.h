#ifndef _BASICSTATE_H_
#define _BASICSTATE_H_

#include <SFML\Graphics.hpp>
#include <string>

class BasicState{
public:
    //Globale Klassenvariablen
    sf::RenderWindow *gpBasicStateWindow;
    sf::Event        *gpBasicStateEvent;

    std::string gNextState;

    //Konstruktor (Deklaration)
    BasicState();

    //Destruktor (Deklaration)
    virtual ~BasicState();

    //Klassenmethoden (Deklaration)
    //Grundfunktionen
    virtual void handleEvents();
    virtual void update(float fFrametime);
    virtual void render();

    //Setter 
    void setNextState(std::string sNextStateID);

    //Getter
    std::string getNextState();

    //Spezifische Funktionen

    /********************************************************************
    * Methodenname: enterState
    * Parameter: -
    * Rückgabe:  -
    * Diese Funktion verwaltet die Funktionsabläufe, die beim Betreten
    * eines Zustandes initiiert werden sollen.
    ********************************************************************/
    virtual void enterState();

    /********************************************************************
    * Methodenname: leaveState
    * Parameter: -
    * Rückgabe:  -
    * Diese Funktion verwaltet die Funktionsabläufe, die beim Verlassen
    * eines Zustandes initiiert werden sollen.
    ********************************************************************/
    virtual void leaveState();
};

#endif //BASICSTATE_H