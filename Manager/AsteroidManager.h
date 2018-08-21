#ifndef _MANAGER_H_
#define _MANAGER_H_

#include <list>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include "../GameObjects/Asteroid.h"
#include "../Core/MainSettings.h"
#include "../../Tools/BinaryData.h"

class AsteroidManager{
public:
  //Konstruktor (Deklaration)
  AsteroidManager();

  //Destruktor (Deklaration)
  virtual ~AsteroidManager();

  //Klassenmethoden (Deklaration)
  //Grundfunktionen zum Darstellen des Objektes
  void handleEvents();
  void update(float fFrametime);
  void render(sf::RenderWindow *pRenderWindow);

  //Setter
  void setSpawnLevel(int iLevel);

  //Getter
  std::list<Asteroid*> *getAsteroidsList();

  //Spezifische Funktionen

  /********************************************************************
  * Methodenname: insert
  * Parameter: Asteroid *pAsteroid
  * Rückgabe:  -
  * Diese Funktion fügt Objekte der Klasse Asteroid in eine Liste ein.
  ********************************************************************/
  void insert(Asteroid *pAsteroid);

  /********************************************************************
  * Methodenname: spawnAsteroids
  * Parameter: float fSpawnTimeInterval
  * Rückgabe:  -
  * Diese Funktion erstellt und spawnt Objekte der Klasse Asteroid in
  * einem spezifischen Zeitintervall.
  ********************************************************************/
  void spawnAsteroids(float fSpawnTimeInterval);

  /********************************************************************
  * Methodenname: checkPositionAsteroid
  * Parameter: -
  * Rückgabe:  -
  * Diese Funktion überprüft, ob sich die Objekte der Klasse Asteroid
  * noch im gültigen Darstellungsbereich befinden und löscht die 
  * entsprechenden Asteroiden aus der Liste.
  ********************************************************************/
  void checkPositionAsteroid();

  /********************************************************************
  * Methodenname: loadMainSettings
  * Parameter: -
  * Rückgabe:  -
  * Diese Funktion lädt die Options-Einstellungen.
  ********************************************************************/
  void loadMainSettings();

private:
  //Klassenattribute
  sf::Clock       *mpClock;
  sf::SoundBuffer *mpBufferDestroyedAsteroid;
  sf::Sound       *mpSoundDestroyedAsteroid;
  MainSettings    *mpMainSettings;

  std::list<Asteroid*> mAsteroidList;
  int                  mSpawnLevel;
};

#endif //MANAGER_H