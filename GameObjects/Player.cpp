/***************************************************************************
* Klassenname Player
* Date
* Autor(en) Hein, Köhler, Meister
*
* Diese Klasse verwaltet die Objekte vom Typ Player. Es werden Player 
* erstellt und gezeichnet, Lebens- und Spielpunkte verwaltet
**************************************************************************/
#include <sstream>

#include "Player.h"

//Konstruktor (Definition)
Player::Player(){

}

Player::Player(std::string sPlayerTexturePath, sf::Vector2f vecPlayerPosition):
    mPlayerScore(0.f),mPlayerLife(100),mPlayerIsAlive(true){

  mpPlayerClock = new sf::Clock;
  mpPlayerClock->restart();

  //Erstellen der Player-Figur
  mpPlayerSprite  = new sf::Sprite;
  mpPlayerTexture = new sf::Texture;

  sf::Image subImage;  //subImage, falls Texturehintergrund einfarbig und nicht transparent
  if (!subImage.loadFromFile(sPlayerTexturePath)){
    std::string error("Could not load Image for subImage from: ");
    error.append(sPlayerTexturePath);
    error.append("\n");
    error.append("Check data path and image file formats!");
    throw std::exception(error.c_str());
  }
  subImage.createMaskFromColor(sf::Color::Black);  //Hintergrundfarbe hier Schwarz
  
  mpPlayerTexture->loadFromImage(subImage);
  mpPlayerSprite->setTexture(*mpPlayerTexture);

  mpPlayerSprite->setScale(0.2f,0.2f);  //Player-Sprite skalieren
  mpPlayerSprite->setOrigin(mpPlayerTexture->getSize().x / 2.f, 
      mpPlayerTexture->getSize().y / 2.f); //Player-Figur mittig platzieren
  mpPlayerSprite->setPosition(vecPlayerPosition);

  //Erstellen des Lebensbalken
  mpPlayerLifeSprite  = new sf::Sprite;
  mpPlayerLifeSpriteBackground = new sf::Sprite;
  mpPlayerLifeTexture = new sf::Texture;
  mpPlayerLifeTextureBackground = new sf::Texture;

  if (!mpPlayerLifeTextureBackground->loadFromFile("Data/Textures/healthbackground.png")){
    std::string error("Could not load Texture for mpPlayerLifeTextureBackground from: ");
    error.append("Data/Textures/healthbackground.png");
    error.append("\n");
    error.append("Check data path and image file formats!");
    throw std::exception(error.c_str());
  }
  mpPlayerLifeSpriteBackground->setTexture(*mpPlayerLifeTextureBackground);
  mpPlayerLifeSpriteBackground->setPosition(sf::Vector2f(300, 12));

  if (!mpPlayerLifeTexture->loadFromFile("Data/Textures/health.png")){
    std::string error("Could not load Texture for mpPlayerLifeTexture from: ");
    error.append("Data/Textures/health.png");
    error.append("\n");
    error.append("Check data path and image file formats!");
    throw std::exception(error.c_str());
  }
  mpPlayerLifeSprite->setTexture(*mpPlayerLifeTexture);
  mpPlayerLifeSprite->setPosition(sf::Vector2f(300, 12));

  mPlayerLifeSteps = int(mpPlayerLifeTexture->getSize().x / mPlayerLife);

  //Erstellen des Game-Scores
  mpPlayerScoreFont = new sf::Font;
  if (!mpPlayerScoreFont->loadFromFile("Data/Font/04B_30__.ttf")){
    std::string error("Could not load Font for mpPlayerScoreFont from: ");
    error.append("Data/Font/04B_30__.ttf");
    error.append("\n");
    error.append("Check data path and image file formats!");
    throw std::exception(error.c_str());
  }
  mPlayerScoreText.setFont(*mpPlayerScoreFont);
  mPlayerScoreText.setCharacterSize(24);
  mPlayerScoreText.setPosition(sf::Vector2f(20, 20));

  //Waffen
  mpWeapon = new Weapon(40, "Data/Textures/GameObjects/Shot/shot.png");
  enterStandardWeapon();
  mShotPosition = sf::Vector2f(0, -800);

  //PlaySettings laden
  mpPlaySettings = new PlaySettings();
  *mpPlaySettings = BinaryData::readBinaryFile<PlaySettings>
      ("Data/Bin/Settings/playsettings.bin");

  //MainSettings initiieren
  mpMainSettings = new MainSettings();
}

//Destruktor (Definition)
Player::~Player(){

  delete mpPlayerSprite;
  delete mpPlayerTexture;
  delete mpPlayerLifeSprite;
  delete mpPlayerLifeSpriteBackground;
  delete mpPlayerLifeTexture;
  delete mpPlayerLifeTextureBackground;
  delete mpPlayerScoreFont;
  delete mpWeapon;
  delete mpPlaySettings;
  delete mpMainSettings;
  delete mpPlayerClock;

  mpPlayerSprite                = nullptr;
  mpPlayerTexture               = nullptr;
  mpPlayerLifeSprite            = nullptr;
  mpPlayerLifeSpriteBackground  = nullptr;
  mpPlayerLifeTexture           = nullptr;
  mpPlayerLifeTextureBackground = nullptr;
  mpPlayerScoreFont             = nullptr;
  mpWeapon                      = nullptr;
  mpPlaySettings                = nullptr;
  mpMainSettings                = nullptr;
  mpPlayerClock                 = nullptr;
}

//Klassenmethoden (Definition)
//Grundfunktionen

void Player::handleEvents(){

}

void Player::update(float fFrametime){

  //Steuerung der Spieler-Figur -> Bewegung nach Rechts
  if (sf::Keyboard::isKeyPressed(mpPlaySettings->getKeyPlayerMoveRight())){
    if (mpPlayerSprite->getPosition().x + (250 * fFrametime) <= 1280){
      mpPlayerSprite->move(250 * fFrametime, 0);
    }
  }

  //Bewegung nach links
  if (sf::Keyboard::isKeyPressed(mpPlaySettings->getKeyPlayerMoveLeft())){
    if (mpPlayerSprite->getPosition().x + (-250 * fFrametime) >= 0) {
      mpPlayerSprite->move(-250 * fFrametime, 0);
    }
  }

  //Abfeuern der Waffe
  if (sf::Keyboard::isKeyPressed(mpPlaySettings->getKeyPlayerFireWeapon())){
    mpWeapon->fireWeapon();
  }

  //Schuss-Richtung
  mpWeapon->update(sf::Vector2f(0,-800),getPlayerSprite().getPosition(), fFrametime);
 
  //Spieler-Leben überprüfen
  if (mPlayerLife <= 0){
    mPlayerIsAlive = false;
  }

  //Graphische Darstellung Spieler-Lebensbalken
  mpPlayerLifeSprite->setTextureRect(sf::IntRect(0, 0, static_cast<int>(mPlayerLifeSteps*mPlayerLife), 
    static_cast<int>(mpPlayerLifeTexture->getSize().y)));
    
  //Darstellung Gamescore
  //MainSettings laden (bei Programmstart mit Defaultwerten, sonst bereits gespeicherte
  *mpMainSettings = BinaryData::readBinaryFile<MainSettings>("Data/Bin/Settings/mainsettings.bin");

  mLanguageOptions = mpMainSettings->getLanguage();
  std::stringstream strsGameScore;
  strsGameScore << mPlayerScore;
  if (mLanguageOptions == 1){
    mPlayerScoreText.setString("Punkte: " + strsGameScore.str());
  }
  else if (mLanguageOptions == 2 || mLanguageOptions == 3){
    mPlayerScoreText.setString("Score: " + strsGameScore.str());
  }  

  
  //Zeitliche Begrenzung Waffenupgrades
  if (getPlayerDamage() > 40){
    if (mpPlayerClock->getElapsedTime().asSeconds() >= 5){
      enterStandardWeapon();
    }
  }
}

void Player::render(sf::RenderWindow *pRenderWindow){
  if (mPlayerIsAlive == true){
    mpWeapon->render(pRenderWindow);
    pRenderWindow->draw(*mpPlayerSprite);
    pRenderWindow->draw(*mpPlayerLifeSpriteBackground);
    pRenderWindow->draw(*mpPlayerLifeSprite);
    pRenderWindow->draw(mPlayerScoreText);
  }
}

//Setter
void Player::setPlayerLife(float fLife){ 
  mPlayerLife = fLife; 
}

void Player::setPlayerIsAlive(bool bIsAlive){ 
  mPlayerIsAlive = bIsAlive; 
}

void Player::setPlayerScore(float fScore){
  mPlayerScore = fScore; 
}

//Getter
const float Player::getPlayerScore(){ 
  return mPlayerScore; 
}

const float Player::getPlayerLife(){ 
  return mPlayerLife; 
}

const bool Player::getPlayerIsAlive(){ 
  return mPlayerIsAlive; 
}

const float Player::getPlayerDamage(){
  return mPlayerDamage;
}

const sf::Sprite &Player::getPlayerSprite(){
  return *mpPlayerSprite; 
}

std::list<Shot*> *Player::getShotList(){ 
  return mpWeapon->getShotList(); 
}

void Player::enterStandardWeapon(){
  mpWeapon->setDamage(40);
  mpWeapon->setTexturePath("Data/Textures/GameObjects/Shot/shot.png");
  mPlayerDamage = mpWeapon->getDamage();

  mpPlayerClock->restart();
}

void Player::enterWeapon1(){

  //"Waffendowngrade" verhindern
  if (getPlayerDamage() <= 70){
    mpWeapon->setTexturePath("Data/Textures/GameObjects/Shot/shot1.png");
    mpWeapon->setDamage(70);
    mPlayerDamage = mpWeapon->getDamage();
    
    mpPlayerClock->restart();
  }
}

void Player::enterWeapon2(){
  mpWeapon->setTexturePath("Data/Textures/GameObjects/Shot/shot2.png");
  mpWeapon->setDamage(100);
  mPlayerDamage = mpWeapon->getDamage();

  mpPlayerClock->restart();
}