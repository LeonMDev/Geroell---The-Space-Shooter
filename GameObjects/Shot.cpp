/***************************************************************************
* Klassenname Shot
* Date
* Autor(en) Hein, Köhler, Meister
*
* Diese Klasse verwaltet die Objekte vom Typ Shot. Es werden die Schüsse
* verwaltet, wie z.B. ob ein Schuss gezeichnet wird und in welcher Richtung.
**************************************************************************/
#include "Shot.h"

Shot::Shot(){

}

Shot::Shot(sf::Vector2f vecShotDirection, sf::Vector2f vecShotPosition, 
    sf::Texture *pShotTexture): mShotDirection(vecShotDirection),
    mShotIsActive(true),mShotSpeed(650){
  mpShotClock  = new sf::Clock;
  mpShotClock->restart();

  mpShotSprite = new sf::Sprite;

  mpShotSprite->setTexture(*pShotTexture);
  mpShotSprite->setOrigin(pShotTexture->getSize().x / 2.f, pShotTexture->getSize().y / 2.f);
  mpShotSprite->setPosition(vecShotPosition);
  mpShotSprite->setRotation(atan2(mShotDirection.y, mShotDirection.x) / 3.1415926f * 180.f);
}

Shot::~Shot(){
  delete mpShotClock;
  delete mpShotSprite;

  mpShotClock  = nullptr;
  mpShotSprite = nullptr;
}

//Klassenmethoden (Definition)
//Grundfunktionen
void Shot::update(float fFrametime){
  mpShotSprite->move(mShotDirection*(mShotSpeed * fFrametime));

  if (mpShotClock->getElapsedTime().asSeconds() > 3.f){
    setShotIsActive(false);
  }
}

void Shot::render(sf::RenderWindow *pRenderWindow){
  pRenderWindow->draw(*mpShotSprite);
}

void Shot::handleEvents(){

}

//Setter
void Shot::setShotIsActive(bool bIsActive){
  mShotIsActive = bIsActive;
}

//Getter
const bool Shot::getShotIsActive(){ 
  return mShotIsActive; 
}

const sf::Sprite &Shot::getShotSprite(){ 
  return *mpShotSprite;
}