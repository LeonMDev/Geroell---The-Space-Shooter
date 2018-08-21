#ifndef _BONUSMANAGER_H_
#define _BONUSMANAGER_H_

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <list>

#include "../GameObjects/Bonus.h"
#include "../GameObjects/WeaponUpgrade.h"
#include "../Core/MainSettings.h"
#include "../../Tools/BinaryData.h"

class BonusManager{
public:
  //Konstruktor (Deklaration)
  BonusManager();

  //Destruktor (Deklaration)
  virtual ~BonusManager();

  //Klassenmethoden (Deklaration)
  //Grundfunktionen zum Darstellen des Objektes
  void handleEvents();
  void update(float fFrametime);
  void render(sf::RenderWindow *pRenderWindow);

  //Setter
  void setSpawnLevel(int iLevel);

  //Getter
  std::list<Bonus*>         *getBonusList();
  std::list<WeaponUpgrade*> *getWeaponUpgradeList();

  //Spezifische Funktionen

  /********************************************************************
  * Methodenname: insertBonus
  * Parameter: Bonus *pBonus
  * R�ckgabe:  -
  * Diese Funktion f�gt Objekte der Klasse Bonus in eine Liste ein.
  ********************************************************************/
  void insertBonus(Bonus *pBonus);

  /********************************************************************
  * Methodenname: insertWeaponUpgrade
  * Parameter: WeaponUpgrade *pWeaponUpgrade
  * R�ckgabe:  -
  * Diese Funktion f�gt Objekte der Klasse WeaponUpgrade in eine Liste ein.
  ********************************************************************/
  void insertWeaponUpgrade(WeaponUpgrade *pWeaponUpgrade);

  /********************************************************************
  * Methodenname: spawnBonus
  * Parameter: float fBonusSpawnTimeInterval
  * R�ckgabe:  -
  * Diese Funktion erstellt und spawnt Objekte der Klasse Bonus in
  * einem spezifischen Zeitintervall.
  ********************************************************************/
  void spawnBonus(float fBonusSpawnTimeInterval);

  /********************************************************************
  * Methodenname: spawnWeaponUpgrade
  * Parameter: float fWeaponUpgradeSpawnTimeInterval
  * R�ckgabe:  -
  * Diese Funktion erstellt und spawnt Objekte der Klasse WeaponUpgrade 
  * in einem spezifischen Zeitintervall.
  ********************************************************************/
  void spawnWeaponUpgrade(float fWeaponUpgradeSpawnTimeInterval);

  /********************************************************************
  * Methodenname: checkBonus
  * Parameter: -
  * R�ckgabe:  -
  * Diese Funktion �berpr�ft, ob sich die Objekte der Klasse Bonus
  * noch im g�ltigen Darstellungsbereich befinden und l�scht den
  * entsprechenden Bonus aus der Liste.
  ********************************************************************/
  void checkPositionBonus();

  /********************************************************************
  * Methodenname: checkWeaponUpgrade
  * Parameter: -
  * R�ckgabe:  -
  * Diese Funktion �berpr�ft, ob sich die Objekte der Klasse WeaponUpgrade
  * noch im g�ltigen Darstellungsbereich befinden und l�scht die
  * Waffe aus der Liste.
  ********************************************************************/
  void checkPositionWeaponUpgrade();

  /********************************************************************
  * Methodenname: loadMainSettings
  * Parameter: -
  * R�ckgabe:  -
  * Diese Funktion l�dt die Options-Einstellungen.
  ********************************************************************/
  void loadMainSettings();

private:
  //Klassenattribute
  sf::Clock       *mpClockBonus;
  sf::Clock       *mpClockWeaponUpdate;
  sf::SoundBuffer *mpBonusBuffer;
  sf::Sound       *mpBonusSound;
  sf::SoundBuffer *mpWeaponUpgradeBuffer;
  sf::Sound       *mpWeaponUpgradeSound;
  MainSettings    *mpMainSettings;

  std::list<Bonus*>         mBonusList;
  std::list<WeaponUpgrade*> mWeaponUpgradeList;
  int                       mSpawnLevel;
};
#endif //BONUSMANAGER_H