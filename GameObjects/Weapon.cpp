/***************************************************************************
* Klassenname Weapon
* Date
* Autor(en) Hein, Köhler, Meister
*
* Diese Klasse verwaltet die Objekte vom Typ Weapon. Es werden Weapon
* mit Hilfe der Schussklasse als Liste erstellt und gezeichnet, 
* Dauer der Schusspausen und Schussrichtungen verwaltet.
**************************************************************************/
#include "Weapon.h"

//Konstruktoren (Definition)
Weapon::Weapon(){

}

Weapon::Weapon(float fDamage, std::string sWeaponTexturePath):
    mWeaponCooldown(0.2f),mWeaponIsLocked(true),mWeaponDamage(fDamage)
    {
      
  mpWeaponTexture = new sf::Texture;
  if (!mpWeaponTexture->loadFromFile("Data/Textures/GameObjects/Shot/shot.png")){
    std::string error("Could not load Texture for mpWeaponTexture from: ");
    error.append("Data/Textures/GameObjects/Shot/shot.png");
    error.append("\n");
    error.append("Check data path and image file formats!");
    throw std::exception(error.c_str());
  }

  mpWeaponTexture1 = new sf::Texture;
  if (!mpWeaponTexture1->loadFromFile("Data/Textures/GameObjects/Shot/shot1.png")){
    std::string error("Could not load Texture for mpWeaponTexture1 from: ");
    error.append("Data/Textures/GameObjects/Shot/shot1.png");
    error.append("\n");
    error.append("Check data path and image file formats!");
    throw std::exception(error.c_str());
  }

  mpWeaponTexture2 = new sf::Texture;
  if (!mpWeaponTexture2->loadFromFile("Data/Textures/GameObjects/Shot/shot2.png")){
    std::string error("Could not load Texture for mpWeaponTexture2 from: ");
    error.append("Data/Textures/GameObjects/Shot/shot2.png");
    error.append("\n");
    error.append("Check data path and image file formats!");
    throw std::exception(error.c_str());
  }
  mpWeaponTexture2->loadFromFile("Data/Textures/GameObjects/Shot/shot2.png");
  
  mpWeaponClock = new sf::Clock;
  mpWeaponClock->restart();

  loadMainSettings();

  mPlayerPosition = sf::Vector2f(0, 0);

  mpFireWeaponBuffer  = new sf::SoundBuffer;
  mpFireWeaponBuffer1 = new sf::SoundBuffer;
  mpFireWeaponBuffer2 = new sf::SoundBuffer;
  mpFireWeaponSound   = new sf::Sound;
  mpFireWeaponSound1  = new sf::Sound;
  mpFireWeaponSound2  = new sf::Sound;
  

  //Soundeffekt "normale" Waffe
  if (!mpFireWeaponBuffer->loadFromFile("Data/Sounds/SoundEffects/fireWeapon.ogg")){
    std::string error("Could not load Sound for mpFireWeaponBuffer from: ");
    error.append("'Data/Sounds/SoundEffects/fireWeapon.ogg'");
    error.append("\n");
    error.append("Check data path. Remember, that only wav, flac, ogg, mp3 are supported!");
    throw std::exception(error.c_str());
  }
  mpFireWeaponSound->setBuffer(*mpFireWeaponBuffer);
  mpFireWeaponSound->setVolume(mpMainSettings->getSoundEffVolume());

  //Soundeffekt Waffenupgrade 1
  if (!mpFireWeaponBuffer1->loadFromFile("Data/Sounds/SoundEffects/fireWeapon1.ogg")){
    std::string error("Could not load Sound for mpFireWeaponBuffer1 from: ");
    error.append("'Data/Sounds/SoundEffects/fireWeapon1.ogg'");
    error.append("\n");
    error.append("Check data path. Remember, that only wav, flac, ogg, mp3 are supported!");
    throw std::exception(error.c_str());
  }
  mpFireWeaponSound1->setBuffer(*mpFireWeaponBuffer1);
  mpFireWeaponSound1->setVolume(mpMainSettings->getSoundEffVolume());

  //Soundeffekt Waffenupgrade 2
  if (!mpFireWeaponBuffer2->loadFromFile("Data/Sounds/SoundEffects/fireWeapon2.ogg")){
    std::string error("Could not load Sound for mpFireWeaponBuffer2 from: ");
    error.append("'Data/Sounds/SoundEffects/fireWeapon2.ogg'");
    error.append("\n");
    error.append("Check data path. Remember, that only wav, flac, ogg, mp3 are supported!");
    throw std::exception(error.c_str());
  }
  mpFireWeaponSound2->setBuffer(*mpFireWeaponBuffer2);
  mpFireWeaponSound2->setVolume(mpMainSettings->getSoundEffVolume());
}

//Destruktor (Definition)
Weapon::~Weapon(){

  delete mpWeaponTexture;
  delete mpWeaponTexture1;
  delete mpWeaponTexture2;
  delete mpWeaponClock;
  delete mpFireWeaponBuffer;
  delete mpFireWeaponBuffer1;
  delete mpFireWeaponBuffer2;
  delete mpFireWeaponSound;
  delete mpFireWeaponSound1;
  delete mpFireWeaponSound2;
  delete mpMainSettings;

  mpWeaponTexture     = nullptr;
  mpWeaponTexture1    = nullptr;
  mpWeaponTexture2    = nullptr;
  mpWeaponClock       = nullptr;
  mpFireWeaponBuffer  = nullptr;
  mpFireWeaponBuffer1 = nullptr;
  mpFireWeaponBuffer2 = nullptr;
  mpFireWeaponSound   = nullptr;
  mpFireWeaponSound1  = nullptr;
  mpFireWeaponSound2  = nullptr;
  mpMainSettings      = nullptr;
}


//Klassenmethoden (Definition)
//Grundfunktionen

void Weapon::handleEvents(){

}

void Weapon::update(sf::Vector2f vecTargetPosition, sf::Vector2f vecPlayerPosition, 
    float fFrametime){
  mPlayerPosition = vecPlayerPosition;

  if (mWeaponIsLocked == false){
    if (mpWeaponClock->getElapsedTime().asSeconds() > mWeaponCooldown){
      mWeaponIsLocked = true;
    }
  }

  //Schussrichtung berechnen
  mTargetDirection = vecTargetPosition;
  const float confLength = sqrt(pow(mTargetDirection.x, 2) + pow(mTargetDirection.y, 2));
  mTargetDirection = (mTargetDirection /= confLength); //Richtungsvektor

  //Schussliste aktualisieren
  for (auto it = mShotList.begin(); it != mShotList.end();){
    if ((*it)->getShotIsActive() == false){
      delete (*it);
      (*it) = nullptr;
      it = mShotList.erase(it);
    }
    else{
      (*it)->update(fFrametime);
      it++;
    }
  }
}

void Weapon::render(sf::RenderWindow *pRenderWindow){
  for (auto it : mShotList){
    pRenderWindow->draw(it->getShotSprite());
  }
}

//Setter
void Weapon::setDamage(float fDamage){
  mWeaponDamage = fDamage;
}

void Weapon::setTexturePath(std::string sWeaponTexturePath){
  mWeaponTexturePath = sWeaponTexturePath;
}

//Getter
const float Weapon::getDamage(){
  return mWeaponDamage;
}

//Spezifische Funktionen
void Weapon::fireWeapon(){
  if (mWeaponIsLocked == true){

    //"normale" Waffe
    if (getDamage() == 40){
      Shot *pShot = new Shot(mTargetDirection, mPlayerPosition, mpWeaponTexture);
      mShotList.push_back(pShot);

      if (mpMainSettings->getIsSoundEffEnabled() == true){
        mpFireWeaponSound->play();
      }

      mpWeaponClock->restart();
      mWeaponIsLocked = false;
    }
    //Waffenupgrade 1
    else if (getDamage() == 70){
      Shot *pShot = new Shot(mTargetDirection, mPlayerPosition, mpWeaponTexture1);
      mShotList.push_back(pShot);

      if (mpMainSettings->getIsSoundEffEnabled() == true){
        mpFireWeaponSound1->play();
      }

      mpWeaponClock->restart();
      mWeaponIsLocked = false;
    }
    //Waffenupgrade 2
    else if (getDamage() == 100){
      Shot *pShot = new Shot(mTargetDirection, mPlayerPosition, mpWeaponTexture2);
      mShotList.push_back(pShot);

      if (mpMainSettings->getIsSoundEffEnabled() == true){
        mpFireWeaponSound2->play();
      }

      mpWeaponClock->restart();
      mWeaponIsLocked = false;
    }
  }
}

void Weapon::loadMainSettings(){
  mpMainSettings = new MainSettings();
  *mpMainSettings = BinaryData::readBinaryFile<MainSettings>("Data/Bin/Settings/mainsettings.bin");
}

//Getter
std::list<Shot*> *Weapon::getShotList(){
  return &mShotList;
}