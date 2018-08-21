#ifndef _WEAPON_H_
#define _WEAPON_H_

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <list>

#include "Shot.h"
#include "../Core/MainSettings.h"
#include "../../Tools/BinaryData.h"

class Weapon{
public:
  //Konstruktoren (Deklaration)
  Weapon();

  /********************************************************************
  * Konstruktorname: Weapon
  * Parameter: float fDamage, string WeaponTexturePath
  * R�ckgabe:  -
  * Dieser Konstruktor erstellt ein Objekt der Klasse Weapon, mit der
  * �bergabe des Schadens und des Texturpfades.
  ********************************************************************/
  Weapon(float fDamage, std::string WeaponTexturePath);

  //Destruktor (Deklaration)
  virtual ~Weapon();

  //Klassenmethoden (Deklaration)
  //Grundfunktionen zum Darstellen des Objektes
  void handleEvents();
  void update(sf::Vector2f vecTargetPosition, sf::Vector2f vecPlayerPosition,
      float fFrametime);
  void render(sf::RenderWindow *pRenderWindow);

  //Setter
  void setDamage(float fDamage);
  void setTexturePath(std::string sWeaponTexturePath);

  //Getter
  const float getDamage();

  /********************************************************************
  * Methodenname: getShotList
  * Parameter: -
  * R�ckgabe:  list<Shot*>
  * Diese Funktion erm�glicht den Zugriff auf die Liste der Sch�sse
  ********************************************************************/
  virtual std::list<Shot*> *getShotList();

  //Spezifische Funktionen

  /********************************************************************
  * Methodenname: fireWeapon
  * Parameter: -
  * R�ckgabe: -
  * Diese Funktion erstellt die Liste der Sch�sse.
  ********************************************************************/
  void fireWeapon();

  /********************************************************************
  * Methodenname: loadMainSettings
  * Parameter: -
  * R�ckgabe: -
  * Diese Funktion l�dt die Options-Einstellungen.
  ********************************************************************/
  void loadMainSettings();

private:
  //Klassenattribute
  sf::Clock       *mpWeaponClock;
  sf::Texture     *mpWeaponTexture;
  sf::Texture     *mpWeaponTexture1;
  sf::Texture     *mpWeaponTexture2;
  sf::SoundBuffer *mpFireWeaponBuffer;
  sf::SoundBuffer *mpFireWeaponBuffer1;
  sf::SoundBuffer *mpFireWeaponBuffer2;
  sf::Sound       *mpFireWeaponSound;
  sf::Sound       *mpFireWeaponSound1;
  sf::Sound       *mpFireWeaponSound2;
  MainSettings    *mpMainSettings;

  std::list<Shot*> mShotList;
  sf::Vector2f     mTargetDirection;
  sf::Vector2f     mPlayerPosition;
  bool             mWeaponIsLocked;
  float            mWeaponCooldown;
  float            mWeaponDamage;
  std::string      mWeaponTexturePath;
};
#endif //WEAPON_H