/***************************************************************************
* Klassenname AsteroidManager
* Date
* Autor(en) Hein, Köhler, Meister
*
* Diese Klasse verwaltet die Objekte vom Typ Asteroid in einer Liste. In 
* einem bestimmten Zeitintervall werden neue Asteroiden gespawnt, zudem
* variieren die Asteroiden in Größe und Geschwindigkeit.
**************************************************************************/
#include "AsteroidManager.h"

//Konstruktor (Definition)
AsteroidManager::AsteroidManager(){
  mpClock = new sf::Clock();
  mpClock->restart();

  loadMainSettings();

  mpBufferDestroyedAsteroid = new sf::SoundBuffer;
  mpSoundDestroyedAsteroid  = new sf::Sound;
  
  if (!mpBufferDestroyedAsteroid->loadFromFile("Data/Sounds/SoundEffects/destroyAsteroid.ogg")){
    std::string error("Could not load Texture for mpBufferDestroyedAsteroid from: ");
    error.append("Data/Sounds/SoundEffects/destroyAsteroid.ogg");
    error.append("\n");
    error.append("Check data path. Remember, that only wav, flac, ogg, mp3 are supported!");
    throw std::exception(error.c_str());
  }
  mpSoundDestroyedAsteroid->setBuffer(*mpBufferDestroyedAsteroid);
  mpSoundDestroyedAsteroid->setVolume(mpMainSettings->getSoundEffVolume());
}

//Destruktor (Definition)
AsteroidManager::~AsteroidManager(){
  delete mpClock;
  delete mpBufferDestroyedAsteroid;
  delete mpSoundDestroyedAsteroid;
  delete mpMainSettings;

  mpClock                   = nullptr;
  mpBufferDestroyedAsteroid = nullptr;
  mpSoundDestroyedAsteroid  = nullptr;
  mpMainSettings            = nullptr;

  for (auto it : mAsteroidList){
    delete it;
    it = nullptr;
  }

  mAsteroidList.clear();
}

//Klassenmethoden (Definition)
//Grundfunktionen
void AsteroidManager::handleEvents(){
  for (auto it : mAsteroidList){
    it->handleEvents();
  }
}

void AsteroidManager::update(float fFrametime){
  if(mSpawnLevel == 1){
    spawnAsteroids(0.8f); //Erstellung/ Spawn der Asteroiden in einem 0.8 Sekunden Intervall
  }
  else if (mSpawnLevel == 2){
    spawnAsteroids(0.5f); //Erstellung/ Spawn der Asteroiden in einem 0.5 Sekunden Intervall
  }
  else if (mSpawnLevel == 3){
    spawnAsteroids(0.3f); //Erstellung/ Spawn der Asteroiden in einem 0.3 Sekunden Intervall
  }
  checkPositionAsteroid(); //Zur Laufzeit überprüfen, ob Asteroiden im gültigen Bereich sind

  for (auto it : mAsteroidList){
    it->update(fFrametime);
  }
}

void AsteroidManager::render(sf::RenderWindow *pRenderWindow){
  for (auto it : mAsteroidList){
    it->render(pRenderWindow);
  }
}

//Setter
void AsteroidManager::setSpawnLevel(int iLevel){
  mSpawnLevel = iLevel;
}

//Getter
std::list<Asteroid*> *AsteroidManager::getAsteroidsList(){
  return &mAsteroidList;
}

//Spezifische Funktionen
void AsteroidManager::insert(Asteroid *pAsteroid){
  mAsteroidList.push_back(pAsteroid);
}

void AsteroidManager::spawnAsteroids(float fSpawnTimeInterval){
  if (mpClock->getElapsedTime().asSeconds() > fSpawnTimeInterval){
    if (mSpawnLevel == 1){
      //Eigenschaften für die Asteroiden festlegen
      //Skalierung/Größe
      float fScaleAsteroids = ((rand() % 6 + 0.5f) / 10.f);

      //Score-Wert
      int iScoreAsteroids = 20;
      iScoreAsteroids = iScoreAsteroids * static_cast<int>(fScaleAsteroids* 10);

      //Lebenszeit
      int iLifeAsteroids = 100;
      iLifeAsteroids = iLifeAsteroids * static_cast<int>(fScaleAsteroids * 10);

      //Geschwindigkeit
      int iSpeedAsteroids = rand() % 120 + 20;
      int iRotationAsteroids = rand() % 100 + 10;

      //Position
      int iXPosAsteroids = rand() % 1260 + 20;
      int iYPosAsteroids = rand() % 200 - 200;

      //Neue Asteroiden erstellen bzw. spawnen
      Asteroid *pAsteroid = new Asteroid(std::string("Data/Textures/GameObjects/Asteroids/asteroid.png"),
        sf::Vector2f(float(iXPosAsteroids),float(iYPosAsteroids)), sf::Vector2f(fScaleAsteroids, fScaleAsteroids),
        float(iSpeedAsteroids), float(iRotationAsteroids), float(iLifeAsteroids));
      pAsteroid->setPoints(float(iScoreAsteroids));

      mAsteroidList.push_back(pAsteroid);

      mpClock->restart();
    }
    else if (mSpawnLevel == 2){
      //Eigenschaften für die Asteroiden festlegen
      //Skalierung/Größe
      float fScaleAsteroids = ((rand() % 6 + 0.4f) / 10.f);

      //Score-Wert
      int iScoreAsteroids = 25;
      iScoreAsteroids = iScoreAsteroids * static_cast<int>(fScaleAsteroids * 10);

      //Lebenszeit
      int iLifeAsteroids = 100;
      iLifeAsteroids = iLifeAsteroids * static_cast<int>(fScaleAsteroids * 10);

      //Geschwindigkeit
      int iSpeedAsteroids = rand() % 140 + 60;
      int iRotationAsteroids = rand() % 110 + 10;

      //Position
      int iXPosAsteroids = rand() % 1260 + 20;
      int iYPosAsteroids = rand() % 200 - 200;

      //Neue Asteroiden erstellen bzw. spawnen
      Asteroid *pAsteroid = new Asteroid(std::string("Data/Textures/GameObjects/Asteroids/asteroid.png"),
        sf::Vector2f(float(iXPosAsteroids), float(iYPosAsteroids)), sf::Vector2f(fScaleAsteroids, fScaleAsteroids),
        float(iSpeedAsteroids), float(iRotationAsteroids), float(iLifeAsteroids));
      pAsteroid->setPoints(float(iScoreAsteroids));

      mAsteroidList.push_back(pAsteroid);

      mpClock->restart();
    }
    else if (mSpawnLevel == 3){
      //Eigenschaften für die Asteroiden festlegen
      //Skalierung/Größe
      float fScaleAsteroids = ((rand() % 6 + 0.3f) / 10.f);

      //Score-Wert
      int iScoreAsteroids = 30;
      iScoreAsteroids = iScoreAsteroids * static_cast<int>(fScaleAsteroids * 10);

      //Lebenszeit
      int iLifeAsteroids = 100;
      iLifeAsteroids = iLifeAsteroids * static_cast<int>(fScaleAsteroids * 10);

      //Geschwindigkeit
      int iSpeedAsteroids = rand() % 180 + 80;
      int iRotationAsteroids = rand() % 120 + 10;

      //Position
      int iXPosAsteroids = rand() % 1260 + 20;
      int iYPosAsteroids = rand() % 200 - 200;

      //Neue Asteroiden erstellen bzw. spawnen
      Asteroid *pAsteroid = new Asteroid(std::string("Data/Textures/GameObjects/Asteroids/asteroid.png"),
        sf::Vector2f(float(iXPosAsteroids),float(iYPosAsteroids)), sf::Vector2f(fScaleAsteroids, fScaleAsteroids),
        float(iSpeedAsteroids), float(iRotationAsteroids), float(iLifeAsteroids));
      pAsteroid->setPoints(float(iScoreAsteroids));

      mAsteroidList.push_back(pAsteroid);

      mpClock->restart();
    }
  }
}

void AsteroidManager::checkPositionAsteroid(){
  for (auto it = mAsteroidList.begin(); it != mAsteroidList.end();){
    if ((*it)->getAsteroidSprite().getPosition().y > 800){
      delete (*it);
      (*it) = nullptr;

      it = mAsteroidList.erase(it);
    }
    else if ((*it)->getAsteroidIsAlive() == false) {
      if (mpMainSettings->getIsSoundEffEnabled() == true){
        mpSoundDestroyedAsteroid->play();
      }

      delete(*it);
      (*it) = nullptr;
      
      it = mAsteroidList.erase(it);
    }
    else{
      it++;
    }
  }
}

void AsteroidManager::loadMainSettings(){
  mpMainSettings = new MainSettings();
  *mpMainSettings = BinaryData::readBinaryFile<MainSettings>("Data/Bin/Settings/mainsettings.bin");
}