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
  * Rückgabe:  -
  * Diese Funktion fügt Objekte der Klasse Bonus in eine Liste ein.
  ********************************************************************/
  void insertBonus(Bonus *pBonus);

  /********************************************************************
  * Methodenname: insertWeaponUpgrade
  * Parameter: WeaponUpgrade *pWeaponUpgrade
  * Rückgabe:  -
  * Diese Funktion fügt Objekte der Klasse WeaponUpgrade in eine Liste ein.
  ********************************************************************/
  void insertWeaponUpgrade(WeaponUpgrade *pWeaponUpgrade);

  /********************************************************************
  * Methodenname: spawnBonus
  * Parameter: float fBonusSpawnTimeInterval
  * Rückgabe:  -
  * Diese Funktion erstellt und spawnt Objekte der Klasse Bonus in
  * einem spezifischen Zeitintervall.
  ********************************************************************/
  void spawnBonus(float fBonusSpawnTimeInterval);

  /********************************************************************
  * Methodenname: spawnWeaponUpgrade
  * Parameter: float fWeaponUpgradeSpawnTimeInterval
  * Rückgabe:  -
  * Diese Funktion erstellt und spawnt Objekte der Klasse WeaponUpgrade 
  * in einem spezifischen Zeitintervall.
  ********************************************************************/
  void spawnWeaponUpgrade(float fWeaponUpgradeSpawnTimeInterval);

  /********************************************************************
  * Methodenname: checkBonus
  * Parameter: -
  * Rückgabe:  -
  * Diese Funktion überprüft, ob sich die Objekte der Klasse Bonus
  * noch im gültigen Darstellungsbereich befinden und löscht den
  * entsprechenden Bonus aus der Liste.
  ********************************************************************/
  void checkPositionBonus();

  /********************************************************************
  * Methodenname: checkWeaponUpgrade
  * Parameter: -
  * Rückgabe:  -
  * Diese Funktion überprüft, ob sich die Objekte der Klasse WeaponUpgrade
  * noch im gültigen Darstellungsbereich befinden und löscht die
  * Waffe aus der Liste.
  ********************************************************************/
  void checkPositionWeaponUpgrade();

  /********************************************************************
  * Methodenname: loadMainSettings
  * Parameter: -
  * Rückgabe:  -
  * Diese Funktion lädt die Options-Einstellungen.
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