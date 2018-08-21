#ifndef _SHOT_H_
#define _SHOT_H_

#include <SFML\Graphics.hpp>

class Shot{
public:
  //Konstruktor (Deklaration)
  Shot();

  /********************************************************************
  * Konstruktorname: Shot
  * Parameter: Vector2f vecShotDirection, Vector2f vecShotPosition, 
  *            Texture *pShotTexture
  * Rückgabe:  -
  * Dieser Konstruktor erstellt ein Objekt der Klasse Shot mit der
  * Richtungsangabe, der Startposition und der Textur.
  ********************************************************************/
  Shot(sf::Vector2f vecShotDirection, sf::Vector2f vecShotPosition, 
      sf::Texture *pShotTexture);

  //Destruktor (Deklaration)
  virtual ~Shot();

  //Klassenmethoden (Deklaration)
  //Grundfunktionen zum Darstellen des Objektes
  void update(float fFrametime);
  void render(sf::RenderWindow *pRenderWindow);
  void handleEvents();

  //Setter
  void setShotIsActive(bool bIsActive);

  //Getter
  const bool getShotIsActive();
  const sf::Sprite &getShotSprite();

private:
  //Klassenattribute
  sf::Sprite *mpShotSprite;
  sf::Clock  *mpShotClock;

  sf::Vector2f mShotDirection;
  bool         mShotIsActive;
  float        mShotSpeed;
};
#endif //SHOT_H