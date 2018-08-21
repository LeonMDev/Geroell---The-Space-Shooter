/***************************************************************************
* Klassenname WeaponUpgrade
* Date
* Autor(en) Hein, Köhler, Meister
*
* Diese Klasse verwaltet die Objekte vom Typ WeaponUpgrade. Es werden "neue"
* Waffen gezeichnet.
**************************************************************************/
#include "WeaponUpgrade.h"

//Konstruktoren (Definition)
WeaponUpgrade::WeaponUpgrade(){

}

WeaponUpgrade::WeaponUpgrade(std::string sNewTexturePath, sf::Vector2f vecPosition,
    sf::Vector2f vecScaleFactor, float fNewSpeed) :mWeaponUpgradeSpeed(fNewSpeed),
    mWeaponUpgradeIsAlive(true), mWeaponUpgradeValue(20){
  mpWeaponUpgradeTexture = new sf::Texture;
  mpWeaponUpgradeSprite  = new sf::Sprite;

  if (!mpWeaponUpgradeTexture->loadFromFile(sNewTexturePath)){
    std::string error("Could not load Texture for mpWeaponUpgradeTexture from: ");
    error.append(sNewTexturePath);
    error.append("\n");
    error.append("Check data path and image file formats!");
    throw std::exception(error.c_str());
  }
  mpWeaponUpgradeSprite->setTexture(*mpWeaponUpgradeTexture);
  mpWeaponUpgradeSprite->setPosition(vecPosition);
  mpWeaponUpgradeSprite->setScale(0.3f, 0.3f);
}

//Destruktor (Definition)
WeaponUpgrade::~WeaponUpgrade(){

  delete mpWeaponUpgradeTexture;
  delete mpWeaponUpgradeSprite;

  mpWeaponUpgradeTexture = nullptr;
  mpWeaponUpgradeSprite  = nullptr;
}

//Klassenmethoden (Definition)
//Grundfunktionen
void WeaponUpgrade::handleEvents(){

}

void WeaponUpgrade::update(float fFrametime){
  mpWeaponUpgradeSprite->move(0, mWeaponUpgradeSpeed * fFrametime);
  mpWeaponUpgradeSprite->setTexture(*mpWeaponUpgradeTexture);
}

void WeaponUpgrade::render(sf::RenderWindow *pRenderWindow){
  pRenderWindow->draw(*mpWeaponUpgradeSprite);
}

//Setter
void WeaponUpgrade::setWeaponUpgradeIsAlive(bool bIsAlive){
  mWeaponUpgradeIsAlive = bIsAlive;
}

void WeaponUpgrade::setWeaponUpgradeValue(int iValue){
  mWeaponUpgradeValue = iValue;
}

//Getter
const sf::Sprite &WeaponUpgrade::getWeaponUpgradeSprite(){
  return *mpWeaponUpgradeSprite;
}

const bool WeaponUpgrade::getWeaponUpgradeIsAlive(){
  return mWeaponUpgradeIsAlive;
}

const int WeaponUpgrade::getWeaponUpgradeValue(){
  return mWeaponUpgradeValue;
}