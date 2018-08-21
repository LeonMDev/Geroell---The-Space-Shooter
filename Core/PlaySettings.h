#ifndef _PLAYSETTINGS_H_
#define _PLAYSETTINGS_H_

#include <SFML\Graphics.hpp>

#include "../../Tools/BinaryData.h"

class PlaySettings{
public:
  //Konstruktor (Deklaration)
  PlaySettings();

  /********************************************************************
  * Konstruktor: PlaySettings
  * Parameter: Key keyMoveLeft, Key keyMoveRight, Key keyFireWeapon
  * Rückgabe:  -
  * Dieser Konstruktor erstellt ein Objekt der Klasse PlaySettings,
  * indem die Werte für die Playersteuerung übergeben werden.
  ********************************************************************/
  PlaySettings(sf::Keyboard::Key keyMoveLeft, sf::Keyboard::Key keyMoveRight,
      sf::Keyboard::Key keyFireWeapon);

  //Destruktor (Deklaration)
  virtual ~PlaySettings();

  //Klassenmethoden (Deklaration)
  //Setter
  void setKeyPlayerMoveLeft(sf::Keyboard::Key keyMoveLeft);
  void setKeyPlayerMoveRight(sf::Keyboard::Key keyMoveRight);
  void setKeyPlayerFireWeapon(sf::Keyboard::Key keyFireWeapon);

  //Getter
  const sf::Keyboard::Key getKeyPlayerMoveLeft();
  const sf::Keyboard::Key getKeyPlayerMoveRight();
  const sf::Keyboard::Key getKeyPlayerFireWeapon();

private:
  //Klassenattribute
  sf::Keyboard::Key mKeyPlayerMoveLeft;
  sf::Keyboard::Key mKeyPlayerMoveRight;
  sf::Keyboard::Key mKeyPlayerFireWeapon;
};
#endif //PLAYSETTINGS_H