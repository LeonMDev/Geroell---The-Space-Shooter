/***************************************************************************
* Klassenname PlaySettings
* Date
* Autor(en) Hein, Köhler, Meister
*
* Diese Klasse verwaltet die Spieleinstellungen (die im PrePlayState
* erfolgte Tastenbelegung zur Steuerung der Player-Figur.
**************************************************************************/
#include "PlaySettings.h"

//Konstruktor (Definition)
PlaySettings::PlaySettings() :mKeyPlayerMoveLeft(sf::Keyboard::Left),
    mKeyPlayerMoveRight(sf::Keyboard::Right),
    mKeyPlayerFireWeapon(sf::Keyboard::Space){

}

PlaySettings::PlaySettings(sf::Keyboard::Key keyMoveLeft, sf::Keyboard::Key keyMoveRight,
    sf::Keyboard::Key keyFireWeapon) : mKeyPlayerMoveLeft(keyMoveLeft),
    mKeyPlayerMoveRight(keyMoveRight), mKeyPlayerFireWeapon(keyFireWeapon){

}

//Destruktor (Definition)
PlaySettings::~PlaySettings(){
}

//Klassenmethoden (Definition)
//Setter
void PlaySettings::setKeyPlayerMoveLeft(sf::Keyboard::Key keyMoveLeft){
  mKeyPlayerMoveLeft = keyMoveLeft;
}

void PlaySettings::setKeyPlayerMoveRight(sf::Keyboard::Key keyMoveRight){
  mKeyPlayerMoveRight = keyMoveRight;
}

void PlaySettings::setKeyPlayerFireWeapon(sf::Keyboard::Key keyFireWeapon){
  mKeyPlayerFireWeapon = keyFireWeapon;
}

//Getter
const sf::Keyboard::Key PlaySettings::getKeyPlayerMoveLeft(){
  return mKeyPlayerMoveLeft;
}

const sf::Keyboard::Key PlaySettings::getKeyPlayerMoveRight(){
  return mKeyPlayerMoveRight;
}

const sf::Keyboard::Key PlaySettings::getKeyPlayerFireWeapon(){
  return mKeyPlayerFireWeapon;
}