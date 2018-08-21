#ifndef _WEAPONUPGRADE_H_
#define _WEAPONUPGRADE_H_

#include <SFML\Graphics.hpp>

class WeaponUpgrade{
public:
  //Konstruktoren (Deklaration)
  WeaponUpgrade();

  /********************************************************************
  * Konstruktorname: WeaponUpgrade
  * Parameter: string sNewTexturePath, Vector2f vecPosition,
  *            Vector2f vecScaleFactor, float fNewSpeed
  * Rückgabe:  -
  * Dieser Konstruktor erstellt ein Objekt der Klasse WeaponUpgrade
  * mit der Angabe des Texturpfades der neuen Waffe, der Position,
  * dem Skalierungsfaktor und der neuen Geschwindigkeit.
  ********************************************************************/
  WeaponUpgrade(std::string sNewTexturPath, sf::Vector2f vecPosition,
      sf::Vector2f vecScaleFactor, float fNewSpeed);

  //Destruktor (Deklaration)
  virtual ~WeaponUpgrade();

  //Klassenmethoden (Deklaration)
  //Grundfunktionen zum Darstellen des Objektes
  void handleEvents();
  void update(float fFrametime);
  void render(sf::RenderWindow *pRenderWindow);

  //Setter
  void setWeaponUpgradeIsAlive(bool bIsAlive);
  void setWeaponUpgradeValue(int iValue);

  //Getter
  const sf::Sprite &getWeaponUpgradeSprite();
  const bool getWeaponUpgradeIsAlive();
  const int getWeaponUpgradeValue();

private:
  //Klassenattribute
  sf::Texture *mpWeaponUpgradeTexture;
  sf::Sprite  *mpWeaponUpgradeSprite;

  float mWeaponUpgradeSpeed;
  bool  mWeaponUpgradeIsAlive;
  int   mWeaponUpgradeValue;
};
#endif //WEAPONUPGRADE_H