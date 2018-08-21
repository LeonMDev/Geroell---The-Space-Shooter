#ifndef _COLLISIONSYSTEM_H_
#define _COLLISIONSYSTEM_H_

#include <list>
#include <SFML\Graphics.hpp>

#include "../GameObjects/Asteroid.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/Bonus.h"
#include "../GameObjects/WeaponUpgrade.h"

class CollisionSystem{
public:
  //Konstruktoren (Deklaration)  
  CollisionSystem();
    
  /********************************************************************
  * Konstruktorname: CollisionSystem
  * Parameter: Player *pPlayer, std::list<Asteroid*> *pList
  * Rückgabe:  -
  * Dieser Konstruktor erstellt ein Objekt der Klasse CollisionSystem,
  * die selbst Objekte der Klassen Player und Asteroid enthält
  ********************************************************************/
  CollisionSystem(Player *pPlayer, std::list<Asteroid*> *pList,
      std::list<Bonus*> *pBonus, std::list<WeaponUpgrade*> *pWeaponUpgradeList);

  //Destruktor (Deklaration)
  virtual ~CollisionSystem();

  //Klassenmethoden
  //Grundfunktionen zum Darstellen des Objektes
  void update(float fFrametime);
  void render(sf::RenderWindow *pRenderWindow);
  void handleEvents();

private:
  //Klassenattribute
  Player                    *mpPlayer;
  std::list<Asteroid*>      *mpAsteroidList;
  std::list<Bonus*>         *mpBonusList;
  std::list<WeaponUpgrade*> *mpWeaponUpgradeList;
};
#endif