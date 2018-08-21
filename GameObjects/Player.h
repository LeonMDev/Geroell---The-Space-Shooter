#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SFML\Graphics.hpp>

#include "Weapon.h"
#include "../Core/PlaySettings.h"
#include "../Core/MainSettings.h"
#include "Shot.h"
#include "../../Tools/BinaryData.h"

class Player{
public:
  //Konstruktoren (Deklaration)
  Player();

  /********************************************************************
  * Konstruktorname: Player
  * Parameter: string sPlayerTexturePath, Vector2f vecPlayerPosition
  * R�ckgabe:  -
  * Dieser Konstruktor erstellt ein Objekt der Klasse Player mit der
  * Angabe des Texturpfades und der Startposition
  ********************************************************************/
  Player(std::string sPlayerTexturePath, sf::Vector2f vecPlayerPosition);

  //Destruktor (Deklaration)
  virtual ~Player();

  //Klassenmethoden (Deklaration)
  //Grundfunktionen zum Darstellen des Objektes
  void handleEvents();
  void update(float fFrametime);
  void render(sf::RenderWindow *pRenderWindow);

  //Setter
  void setPlayerLife(float fLife);
  void setPlayerIsAlive(bool bIsAlive);
  void setPlayerScore(float fScore);

  //Getter
  const float getPlayerScore();
  const float getPlayerLife();
  const bool getPlayerIsAlive();
  const float getPlayerDamage();

  /********************************************************************
  * Methodenname: getSprite
  * Parameter: -
  * R�ckgabe:  Sprite
  * Diese Funktion erm�glicht den Zugriff auf die Sprites "privater"
  * Instanzen.
  ********************************************************************/
  const sf::Sprite &getPlayerSprite();

  /********************************************************************
  * Methodenname: getShotList
  * Parameter: -
  * R�ckgabe:  list<Shot*>
  * Diese Funktion erm�glicht den Zugriff auf die Liste der Sch�sse.
  ********************************************************************/
  virtual std::list<Shot*> *getShotList();

  /********************************************************************
  * Methodenname: enterStandardWeapon
  * Parameter: -
  * R�ckgabe: -
  * Diese Funktion setzt die Standard Waffe. Der Schaden der Waffe
  * liegt bei 40.
  ********************************************************************/
  void enterStandardWeapon();

  /********************************************************************
  * Methodenname: enterWeapon1
  * Parameter: -
  * R�ckgabe: -
  * Diese Funktion setzt den Waffenbonus 1. Der Schaden der Waffe
  * liegt bei 70.
  ********************************************************************/
  void enterWeapon1();

  /********************************************************************
  * Methodenname: enterWeapon2
  * Parameter: -
  * R�ckgabe: -
  * Diese Funktion setzt den Waffenbonus 1. Der Schaden der Waffe
  * liegt bei 100, mit einem Schuss kann der Asteroid zerst�rt werden.
  ********************************************************************/
  void enterWeapon2();

private:
  //Klassenattribute
  sf::Sprite  *mpPlayerSprite;
  sf::Texture *mpPlayerTexture;
  sf::Sprite  *mpPlayerLifeSprite;
  sf::Sprite  *mpPlayerLifeSpriteBackground;
  sf::Texture *mpPlayerLifeTexture;
  sf::Texture *mpPlayerLifeTextureBackground;
  sf::Font    *mpPlayerScoreFont;
  sf::Clock   *mpPlayerClock;

  Weapon       *mpWeapon;
  PlaySettings *mpPlaySettings;
  MainSettings *mpMainSettings;

  sf::Vector2f mShotPosition;
  sf::Text     mPlayerScoreText;
  float        mPlayerScore;
  float        mPlayerLife;
  float        mPlayerDamage;
  bool         mPlayerIsAlive;
  int          mPlayerLifeSteps;
  int          mLanguageOptions;
};

#endif //PLAYER_H