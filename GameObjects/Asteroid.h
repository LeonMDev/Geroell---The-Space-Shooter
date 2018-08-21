#ifndef _ASTEROID_H_
#define _ASTEROID_H_

#include <SFML\Graphics.hpp>

class Asteroid{
public:
  //Konstruktor(Deklaration)
  Asteroid();

  /********************************************************************
  * Konstruktorname: Asteroid
  * Parameter: string sAsteroidImagePath, Vector2f vecAsteroidPosition, 
  *            Vector2f vecAsteroidScaleFactor, float fSpeed, 
  *            float fRotation, float fAsteroidLife
  * Rückgabe:  -
  * Dieser Konstruktor erstellt ein Objekt der Klasse Asteroid mit der
  * Angabe des Texturpfades, der Startposition, dem Skalierungsfaktor,
  * der Geschwindigkeit, der Rotation und der Lebenspunkte.
  ********************************************************************/
  Asteroid(std::string sAsteroidImagePath, sf::Vector2f vecAsteroidPosition, 
      sf::Vector2f vecAsteroidScaleFactor, float fSpeed, float fRotation, 
      float fAsteroidLife);

  //Destruktor (Deklaration)
  virtual ~Asteroid();

  //Klassenmethoden (Deklaration)
  //Grundfunktionen zum Darstellen des Objektes
  void update(float fFrametime);
  void render(sf::RenderWindow *pRenderWindow);
  void handleEvents();

  //Setter
  void setAsteroidLife(float fLife);
  void setAsteroidIsAlive(bool bIsAlive);
  void setPoints(float fPoints);

  //Getter
  const sf::Sprite &getAsteroidSprite();
  const float getAsteroidLife();
  const bool getAsteroidIsAlive();
  const float getPoints();

private:
  //Klassenattribute
  sf::Texture *mpAsteroidTexture;
  sf::Sprite  *mpAsteroidSprite;

  float mAsteroidSpeed;
  float mAsteroidRotation;
  float mAsteroidLife;
  bool  mAsteroidIsAlive;
  float mPoints;
};
#endif //ASTEROID_H