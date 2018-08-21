#ifndef _BONUS_H_
#define _BONUS_H_

#include <SFML\Graphics.hpp>

class Bonus{
public:
  //Konstruktoren (Definition)
  Bonus();
  
  /********************************************************************
  * Konstruktorname: Bonus
  * Parameter: string sBonusTexturePath, Vector2f vecBonusPosition,
  *            Vector2f vecBonusScaleFactor, float fBonusSpeed
  * Rückgabe:  -
  * Dieser Konstruktor erstellt ein Objekt der Klasse Bonus
  * mit der Angabe des Texturpfades des Bonus, der Position,
  * dem Skalierungsfaktor und der Geschwindigkeit.
  ********************************************************************/
  Bonus(std::string sBonusTexturePath, sf::Vector2f vecBonusPosition,
      sf::Vector2f vecBonusScaleFactor, float fBonusSpeed);

  //Destruktor (Deklaration)
  virtual ~Bonus();

  //Klassenmethoden (Deklaration)
  //Grundfunktionen zum Darstellen des Objektes
  void handleEvents();
  void update(float fFrametime);
  void render(sf::RenderWindow *pRenderWindow);

  //Setter
  void setBonusIsAlive(bool bIsAlive);
  void setBonusValue(float fValue);

  //Getter
  const sf::Sprite &getBonusSprite();
  const bool &getBonusIsAlive();
  const float &getBonusValue();

private:
  //Klassenattribute
  sf::Texture *mpBonusTexture;
  sf::Sprite  *mpBonusSprite;

  float mBonusSpeed;
  bool  mBonusIsAlive;
  float mBonusValue;
};

#endif //BONUS_H