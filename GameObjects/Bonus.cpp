/***************************************************************************
* Klassenname Bonus
* Date
* Autor(en) Hein, Köhler, Meister
*
* Diese Klasse verwaltet die Objekte vom Typ Bonus. Es werden Boni erstellt
* udd gezeichnet.
**************************************************************************/
#include "Bonus.h"

//Konstruktoren (Definition)
Bonus::Bonus(){

}

Bonus::Bonus(std::string sBonusTexturePath, sf::Vector2f vecBonusPosition,
  sf::Vector2f vecBonusScaleFactor, float fBonusSpeed) :mBonusSpeed(fBonusSpeed),
  mBonusIsAlive(true), mBonusValue(20){
  mpBonusTexture = new sf::Texture;
  mpBonusSprite = new sf::Sprite;

  if (!mpBonusTexture->loadFromFile(sBonusTexturePath)){
    std::string error("Could not load Texture for mpBonusTexture from: ");
    error.append(sBonusTexturePath);
    error.append("\n");
    error.append("Check data path and image file formats!");
    throw std::exception(error.c_str());
  }
  mpBonusSprite->setTexture(*mpBonusTexture);
  mpBonusSprite->setPosition(vecBonusPosition);
  mpBonusSprite->setScale(0.3f, 0.3f);
}

//Destruktor (Definition)
Bonus::~Bonus(){

  delete mpBonusTexture;
  delete mpBonusSprite;

  mpBonusTexture = nullptr;
  mpBonusSprite = nullptr;
}

//Klassenmethoden (Definition)
//Grundfunktionen
void Bonus::handleEvents(){

}

void Bonus::update(float fFrametime){
  mpBonusSprite->move(0, mBonusSpeed * fFrametime);
  mpBonusSprite->setTexture(*mpBonusTexture);
}

void Bonus::render(sf::RenderWindow *pRenderWindow){
  pRenderWindow->draw(*mpBonusSprite);
}

//Setter
void Bonus::setBonusIsAlive(bool bIsAlive){
  mBonusIsAlive = bIsAlive;
}

void Bonus::setBonusValue(float fValue){
  mBonusValue = fValue;
}

//Getter
const sf::Sprite &Bonus::getBonusSprite(){
  return *mpBonusSprite;
}

const bool &Bonus::getBonusIsAlive(){
  return mBonusIsAlive;
}

const float &Bonus::getBonusValue(){
  return mBonusValue;
}