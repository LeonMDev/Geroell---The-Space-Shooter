/***************************************************************************
* Klassenname Asteroid
* Date
* Autor(en) Hein, Köhler, Meister
*
* Diese Klasse verwaltet die Objekte vom Typ Asteroid. Es werden Asteroiden
* erstellt, die dann über den AsteroidManager weiter verwaltet werden
**************************************************************************/
#include "Asteroid.h"

//Konstruktor (Definition)
Asteroid::Asteroid(){

}

Asteroid::Asteroid(std::string sAsteroidImagePath, sf::Vector2f vecAsteroidPosition, 
    sf::Vector2f vecAsteroidScaleFactor, float fSpeed, float fRotation, 
    float fAsteroidLife):mAsteroidRotation(fRotation),mAsteroidSpeed(fSpeed),
    mAsteroidLife(fAsteroidLife),mAsteroidIsAlive(true){
  mpAsteroidSprite  = new sf::Sprite;
  mpAsteroidTexture = new sf::Texture;

  sf::Image subImage;
  if (!subImage.loadFromFile(sAsteroidImagePath)){
    std::string error("Could not load Image for subImage from: ");
    error.append(sAsteroidImagePath);
    error.append("\n");
    error.append("Check data path and image file formats!");
    throw std::exception(error.c_str());
  }
  subImage.createMaskFromColor(sf::Color::Black);

  mpAsteroidTexture->loadFromImage(subImage);
  mpAsteroidSprite->setTexture(*mpAsteroidTexture);
  mpAsteroidSprite->setScale(vecAsteroidScaleFactor);
  mpAsteroidSprite->setPosition(vecAsteroidPosition);
  mpAsteroidSprite->setOrigin(mpAsteroidTexture->getSize().x / 2.f, 
      mpAsteroidTexture->getSize().y / 2.f);
}

//Destruktor (Definition)
Asteroid::~Asteroid(){

  delete mpAsteroidSprite;
  delete mpAsteroidTexture;

  mpAsteroidSprite  = nullptr;
  mpAsteroidTexture = nullptr;
}

//Klassenmethoden (Definition)
//Grundfunktionen
void Asteroid::update(float fFrametime){
  //Bewegungen des Asteroiden koordinieren
  mpAsteroidSprite->rotate(mAsteroidRotation * fFrametime);
  mpAsteroidSprite->move(0, mAsteroidSpeed * fFrametime);
  mpAsteroidSprite->setTexture(*mpAsteroidTexture);
}

void Asteroid::render(sf::RenderWindow *pRenderWindow){
  pRenderWindow->draw(*mpAsteroidSprite);
}

void Asteroid::handleEvents(){

}

//Setter
void Asteroid::setAsteroidLife(float fLife){ 
  mAsteroidLife = fLife; 
}

void Asteroid::setAsteroidIsAlive(bool bIsAlive){ 
  mAsteroidIsAlive = bIsAlive; 
}

void Asteroid::setPoints(float fPoints){ 
  mPoints = fPoints;
}

//Getter
const sf::Sprite &Asteroid::getAsteroidSprite(){
  return *mpAsteroidSprite;
}

const float Asteroid::getAsteroidLife(){ 
  return mAsteroidLife;
}

const bool Asteroid::getAsteroidIsAlive(){ 
  return mAsteroidIsAlive;
}

const float Asteroid::getPoints(){
  return mPoints;
}