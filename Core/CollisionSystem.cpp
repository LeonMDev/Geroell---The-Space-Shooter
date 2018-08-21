/***************************************************************************
* Klassenname CollisionSystem
* Date
* Autor(en) Hein, Köhler, Meister
*
* Diese Klasse dient als Schnittstelle, um die Kollision zwischen dem Player
* und den Asteroiden zu managen
**************************************************************************/

#include "CollisionSystem.h"
#include "../../Tools/Collision.h"

//Konstruktoren (Definition)
CollisionSystem::CollisionSystem(){

}

CollisionSystem::CollisionSystem(Player *pPlayer, std::list<Asteroid*> *pAsteroidList,
    std::list<Bonus*> *pBonusList, std::list<WeaponUpgrade*> *pWeaponUpgrade):
    mpPlayer(pPlayer),mpAsteroidList(pAsteroidList),mpBonusList(pBonusList),
    mpWeaponUpgradeList(pWeaponUpgrade){
    
}

CollisionSystem::~CollisionSystem(){
}

void CollisionSystem::handleEvents(){

}

void CollisionSystem::update(float fFrametime){
  for (auto it : *mpAsteroidList){

    /*Überprüfen, ob eine "Kollision" zwischen dem Schuss des Spieler 
      und dem Asteroiden stattfindet*/
    for (auto itShot : *mpPlayer->getShotList()){
      if (Collision::PixelPerfectTest(itShot->getShotSprite(), it->getAsteroidSprite())){
        itShot->setShotIsActive(false);

        //Abzug von "Lebenspunkten" des Asteroiden
        it->setAsteroidLife(it->getAsteroidLife() - mpPlayer->getPlayerDamage()); 
      }
    }

    if (Collision::PixelPerfectTest(mpPlayer->getPlayerSprite(), it->getAsteroidSprite())){
      it->setAsteroidLife(it->getAsteroidLife() - 50 * fFrametime);
      mpPlayer->setPlayerLife(mpPlayer->getPlayerLife() - 50 * fFrametime);
      if (mpPlayer->getPlayerLife() <= 0){
        mpPlayer->setPlayerLife(0);
      }
    }

    if (it->getAsteroidLife() <= 0){
      it->setAsteroidIsAlive(false);
    }

    if (it->getAsteroidIsAlive() == false){
      mpPlayer->setPlayerScore(mpPlayer->getPlayerScore() + it->getPoints());
    }
  }

  for (auto itBonus : *mpBonusList){
    if (Collision::PixelPerfectTest(mpPlayer->getPlayerSprite(), itBonus->getBonusSprite())){
      itBonus->setBonusIsAlive(false);
      if (mpPlayer->getPlayerLife() + itBonus->getBonusValue() <= 100){
        mpPlayer->setPlayerLife(mpPlayer->getPlayerLife() + itBonus->getBonusValue());
      }
      else{
        mpPlayer->setPlayerLife(100);
      }
    }
  }

  for (auto itWeapon : *mpWeaponUpgradeList){
    if (Collision::PixelPerfectTest(mpPlayer->getPlayerSprite(),
        itWeapon->getWeaponUpgradeSprite())){
      itWeapon->setWeaponUpgradeIsAlive(false);
      if (itWeapon->getWeaponUpgradeValue() == 1){
        mpPlayer->enterWeapon1();
      }
      else if (itWeapon->getWeaponUpgradeValue() == 2){
        mpPlayer->enterWeapon2();
      }
    }
  }
}

void CollisionSystem::render(sf::RenderWindow *pRenderWindow){

}