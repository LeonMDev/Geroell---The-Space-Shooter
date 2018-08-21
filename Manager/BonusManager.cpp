/***************************************************************************
* Klassenname BonusManager
* Date
* Autor(en) Hein, Köhler, Meister
*
* Diese Klasse verwaltet die Objekte vom Typ Bonus und WeaponUpgrade in 
* einer Liste. In einem bestimmten Zeitintervall werden neue 
* Boni und Waffen gespawnt.
**************************************************************************/
#include "BonusManager.h"

//Konstruktor (Definition)
BonusManager::BonusManager(){
  mpClockBonus        = new sf::Clock();
  mpClockWeaponUpdate = new sf::Clock();

  mpClockBonus->restart();
  mpClockWeaponUpdate->restart();

  loadMainSettings();
}

//Destruktor (Definition)
BonusManager::~BonusManager(){
  delete mpClockBonus;
  delete mpClockWeaponUpdate;

  delete mpBonusBuffer;
  delete mpBonusSound;
  delete mpWeaponUpgradeBuffer;
  delete mpWeaponUpgradeSound;
  delete mpMainSettings;

  mpBonusBuffer         = nullptr;
  mpBonusSound          = nullptr;
  mpWeaponUpgradeBuffer = nullptr;
  mpWeaponUpgradeSound  = nullptr;
  mpMainSettings        = nullptr;

  mpClockBonus              = nullptr;
  mpClockWeaponUpdate       = nullptr;

  for (auto itBonus : mBonusList){
    delete itBonus;
    itBonus = nullptr;
  }

  for (auto itWeapon : mWeaponUpgradeList){
    delete itWeapon;
    itWeapon = nullptr;
  }

  mBonusList.clear();
  mWeaponUpgradeList.clear();
}

//Klassenmethoden (Definition)
//Grundfunktionen
void BonusManager::handleEvents(){
  for (auto itBonus : mBonusList){
    itBonus->handleEvents();
  }

  for (auto itWeapon : mWeaponUpgradeList){
    itWeapon->handleEvents();
  }
}

void BonusManager::update(float fFrametime){
  if (mSpawnLevel == 1){
    spawnBonus(5.0f);         //Erstellung/ Spawn der Boni in einem ... Sekunden Intervall
    spawnWeaponUpgrade(5.0f); //Erstellung/ Spawn der Waffenupgrades in einem ... Sekunden Intervall
  }
  else if (mSpawnLevel == 2){
    spawnBonus(6.0f);         //Erstellung/ Spawn der Boni in einem ... Sekunden Intervall
    spawnWeaponUpgrade(6.0f); //Erstellung/ Spawn der Waffenupgrades in einem ... Sekunden Intervall
  }
  else if (mSpawnLevel == 3){
    spawnBonus(7.0f);          //Erstellung/ Spawn der Boni in einem ... Sekunden Intervall
    spawnWeaponUpgrade(7.0f); //Erstellung/ Spawn der Waffenupgrades in einem ... Sekunden Intervall
  }

  checkPositionBonus(); //Zur Laufzeit überprüfen, ob Boni im gültigen Bereich sind
  checkPositionWeaponUpgrade(); //Zur Laufzeit überprüfen, ob Waffenupgrade im gültigen Bereich sind

  for (auto itBonus : mBonusList){
    itBonus->update(fFrametime);
  }

  for (auto itWeapon : mWeaponUpgradeList){
    itWeapon->update(fFrametime);
  }
}

void BonusManager::render(sf::RenderWindow *pRenderWindow){
  for (auto itBonus : mBonusList){
    itBonus->render(pRenderWindow);
  }

  for (auto itWeapon : mWeaponUpgradeList){
    itWeapon->render(pRenderWindow);
  }
}

//Setter
void BonusManager::setSpawnLevel(int iLevel){
  mSpawnLevel = iLevel;
}

//Getter
std::list<Bonus*> *BonusManager::getBonusList(){
  return &mBonusList;
}

std::list<WeaponUpgrade*> *BonusManager::getWeaponUpgradeList(){
  return &mWeaponUpgradeList;
}

//Spezifische Funktionen
void BonusManager::insertBonus(Bonus *pBonus){
  mBonusList.push_back(pBonus);
}

void BonusManager::insertWeaponUpgrade(WeaponUpgrade *pWeaponUpgrade){
  mWeaponUpgradeList.push_back(pWeaponUpgrade);
}

void BonusManager::spawnBonus(float fBonusSpawnTimeInterval){
  if (mpClockBonus->getElapsedTime().asSeconds() > fBonusSpawnTimeInterval){
    if (mSpawnLevel == 1){
      //Eigenschaften für die Boni in Level 1 festlegen

      //"Heilungs"-Wert
      int iHealthBonusValue = rand() % 25 + 9;

      //Geschwindigkeit
      int iSpeedBonus = rand() % 120 + 20;

      //Position
      int iXPosBonus = rand() % 1260 + 20;
      int iYPosBonus = rand() % 200 - 200;

      //Neue Bonus erstellen bzw. spawnen
      Bonus *pBonus = new Bonus(std::string("Data/Textures/GameObjects/Bonus/healthbonus.png"),
        sf::Vector2f(float(iXPosBonus), float(iYPosBonus)), sf::Vector2f(0.3f,0.3f), float(iSpeedBonus));
      pBonus->setBonusValue(float(iHealthBonusValue));

      mBonusList.push_back(pBonus);

      mpClockBonus->restart();
    }
    else if (mSpawnLevel == 2){
      //Eigenschaften für die Boni in Level 2 festlegen

      //"Heilungs"-Wert
      int iHealthBonusValue = rand() % 26 + 8;

      //Geschwindigkeit
      int iSpeedBonus = rand() % 140 + 60;

      //Position
      int iXPosBonus = rand() % 1260 + 20;
      int iYPosBonus = rand() % 200 - 200;

      //Neue Bonus erstellen bzw. spawnen
      Bonus *pBonus = new Bonus(std::string("Data/Textures/GameObjects/Bonus/healthbonus.png"),
        sf::Vector2f(float(iXPosBonus),float(iYPosBonus)), sf::Vector2f(0.3f, 0.3f), float(iSpeedBonus));
      pBonus->setBonusValue(float(iHealthBonusValue));

      mBonusList.push_back(pBonus);

      mpClockBonus->restart();
    }
    else if (mSpawnLevel == 3){
      //Eigenschaften für die Boni in Level 3 festlegen

      //"Heilungs"-Wert
      int iHealthBonusValue = rand() % 25 + 9;

      //Geschwindigkeit
      int iSpeedBonus = rand() % 180 + 80;

      //Position
      int iXPosBonus = rand() % 1260 + 20;
      int iYPosBonus = rand() % 200 - 200;

      //Neue Bonus erstellen bzw. spawnen
      Bonus *pBonus = new Bonus(std::string("Data/Textures/GameObjects/Bonus/healthbonus.png"),
        sf::Vector2f(float(iXPosBonus),float(iYPosBonus)), sf::Vector2f(0.3f, 0.3f),float(iSpeedBonus));
      pBonus->setBonusValue(float(iHealthBonusValue));

      mBonusList.push_back(pBonus);

      mpClockBonus->restart();
    }
  }
}

void BonusManager::spawnWeaponUpgrade(float fWeaponUpgradeSpawnTimeInterval){
  if (mpClockWeaponUpdate->getElapsedTime().asSeconds() > 
      fWeaponUpgradeSpawnTimeInterval){
    if (mSpawnLevel == 1){
      //Eigenschaften für die Waffenupgrades in Level 1 festlegen

      //"Waffenart"-Wert
      int iWeaponValue = rand() % 2 + 1;

      //Geschwindigkeit
      int iSpeedBonus = rand() % 120 + 20;

      //Position
      int iXPosBonus = rand() % 1260 + 20;
      int iYPosBonus = rand() % 200 - 200;

      if (iWeaponValue == 1){

        //Waffenbonus mit Texture 1 erstellen bzw. spawnen
        WeaponUpgrade *pWeaponUpgrade = new WeaponUpgrade(std::string
            ("Data/Textures/GameObjects/Bonus/weaponupgrade1.png"),
            sf::Vector2f(float(iXPosBonus),float(iYPosBonus)), sf::Vector2f(0.3f, 0.3f), float(iSpeedBonus));
        pWeaponUpgrade->setWeaponUpgradeValue(iWeaponValue);
        mWeaponUpgradeList.push_back(pWeaponUpgrade);
      }
      else{
        //Waffenbonus mit Texture 2 erstellen bzw. spawnen
        WeaponUpgrade *pWeaponUpgrade = new WeaponUpgrade(std::string
            ("Data/Textures/GameObjects/Bonus/weaponupgrade2.png"),
            sf::Vector2f(float(iXPosBonus),float(iYPosBonus)), sf::Vector2f(0.3f, 0.3f), float(iSpeedBonus));
        pWeaponUpgrade->setWeaponUpgradeValue(iWeaponValue);
        mWeaponUpgradeList.push_back(pWeaponUpgrade);
      }
      mpClockWeaponUpdate->restart();
    }
    else if (mSpawnLevel == 2){
      //Eigenschaften für die Waffenupgrades in Level 2 festlegen

      //"Waffenart"-Wert
      int iWeaponValue = rand() % 2 + 1;

      //Geschwindigkeit
      int iSpeedBonus = rand() % 140 + 60;

      //Position
      int iXPosBonus = rand() % 1260 + 20;
      int iYPosBonus = rand() % 200 - 200;

      if (iWeaponValue == 1){

        //Waffenbonus mit Texture 1 erstellen bzw. spawnen
        WeaponUpgrade *pWeaponUpgrade = new WeaponUpgrade(std::string
            ("Data/Textures/GameObjects/Bonus/weaponupgrade1.png"),
            sf::Vector2f(float(iXPosBonus),float(iYPosBonus)), sf::Vector2f(0.3f, 0.3f), float(iSpeedBonus));
        pWeaponUpgrade->setWeaponUpgradeValue(iWeaponValue);
        mWeaponUpgradeList.push_back(pWeaponUpgrade);
      }
      else{
        //Waffenbonus mit Texture 2 erstellen bzw. spawnen
        WeaponUpgrade *pWeaponUpgrade = new WeaponUpgrade(std::string
            ("Data/Textures/GameObjects/Bonus/weaponupgrade2.png"),
            sf::Vector2f(float(iXPosBonus), float(iYPosBonus)), sf::Vector2f(0.3f, 0.3f), float(iSpeedBonus));
        pWeaponUpgrade->setWeaponUpgradeValue(iWeaponValue);
        mWeaponUpgradeList.push_back(pWeaponUpgrade);
      }
      mpClockWeaponUpdate->restart();
    }
    else if (mSpawnLevel == 3){
      //Eigenschaften für die Waffenupgrades in Level 3 festlegen

      //"Waffenart"-Wert
      int iWeaponValue = rand() % 2 + 1;

      //Geschwindigkeit
      int iSpeedBonus = rand() % 180 + 80;

      //Position
      int iXPosBonus = rand() % 1260 + 20;
      int iYPosBonus = rand() % 200 - 200;

      if (iWeaponValue == 1){

        //Waffenbonus mit Texture 1 erstellen bzw. spawnen
        WeaponUpgrade *pWeaponUpgrade = new WeaponUpgrade(std::string
            ("Data/Textures/GameObjects/Bonus/weaponupgrade1.png"),
            sf::Vector2f(float(iXPosBonus), float(iYPosBonus)), sf::Vector2f(0.3f, 0.3f),float(iSpeedBonus));
        pWeaponUpgrade->setWeaponUpgradeValue(iWeaponValue);
        mWeaponUpgradeList.push_back(pWeaponUpgrade);
      }
      else{
        //Neue Waffe mit Texture 2 erstellen bzw. spawnen
        WeaponUpgrade *pWeaponUpgrade = new WeaponUpgrade(std::string
            ("Data/Textures/GameObjects/Bonus/weaponupgrade2.png"),
            sf::Vector2f(float(iXPosBonus), float(iYPosBonus)), sf::Vector2f(0.3f, 0.3f), float(iSpeedBonus));
        pWeaponUpgrade->setWeaponUpgradeValue(iWeaponValue);
        mWeaponUpgradeList.push_back(pWeaponUpgrade);
      }
      mpClockWeaponUpdate->restart();
    }
  }
}

void BonusManager::checkPositionBonus(){
  for (auto it = mBonusList.begin(); it != mBonusList.end();){
    if ((*it)->getBonusSprite().getPosition().y > 800){
      delete (*it);
      (*it) = nullptr;

      it = mBonusList.erase(it);
    }
    else if ((*it)->getBonusIsAlive() == false){
      if (mpMainSettings->getIsSoundEffEnabled() == true){
      }

      delete(*it);
      (*it) = nullptr;

      it = mBonusList.erase(it);
    }
    else{
      it++;
    }
  }
}

void BonusManager::checkPositionWeaponUpgrade(){
  for (auto it = mWeaponUpgradeList.begin(); it != mWeaponUpgradeList.end();){
    if ((*it)->getWeaponUpgradeSprite().getPosition().y > 800){
      delete (*it);
      (*it) = nullptr;

      it = mWeaponUpgradeList.erase(it);
    }
    else if ((*it)->getWeaponUpgradeIsAlive() == false){
      if (mpMainSettings->getIsSoundEffEnabled() == true){
      }

      delete(*it);
      (*it) = nullptr;

      it = mWeaponUpgradeList.erase(it);
    }
    else{
      it++;
    }
  }
}

void BonusManager::loadMainSettings(){
  mpMainSettings = new MainSettings();
  *mpMainSettings = BinaryData::readBinaryFile<MainSettings>("Data/Bin/Settings/mainsettings.bin");
}