/***************************************************************************
* Klassenname ControlSettings
* Date
* Autor(en) Hein, Köhler, Meister
*
* Diese Klasse ist eine Unterklasse des BasicState und verwaltet die 
* Steuerungsstrukturen bzw. Tastenbelegung zur Bewegung der Spielerfigur.
**************************************************************************/
#include "ControlSettings.h"
#include <iostream>

//Konstruktoren (Definition)
ControlSettings::ControlSettings(){

}

ControlSettings::ControlSettings(sf::RenderWindow *pRenderWindow, sf::Event *pEvent,
    GUIManager *pGUI) :mpStateGUIManager(pGUI){
  gpBasicStateWindow = pRenderWindow;
  gpBasicStateEvent = pEvent;

  //Initialisierung Text
  if (!mControlSettingsFont.loadFromFile("Data/Font/04B_30__.ttf")){
    std::string error("Could not load Font for mControlSettingsFont from: ");
    error.append("Data/Font/04B_30__.ttf");
    error.append("\n");
    error.append("Check data path and image file formats!");
    throw std::exception(error.c_str());
  }

  //Text ControlSettings
  mControlSettingsText[0].setFont(mControlSettingsFont);

  mControlSettingsText[0].setCharacterSize(50);
  mControlSettingsText[0].setStyle(sf::Text::Bold | sf::Text::Underlined);
  mControlSettingsText[0].setPosition(20,40);

  mControlSettingsText[1].setFont(mControlSettingsFont);
  mControlSettingsText[1].setCharacterSize(24);
  mControlSettingsText[1].setPosition(10,185);

  mControlSettingsText[2].setFont(mControlSettingsFont);
  mControlSettingsText[2].setCharacterSize(24);
  mControlSettingsText[2].setPosition(10, 260);

  mControlSettingsText[3].setFont(mControlSettingsFont);
  mControlSettingsText[3].setCharacterSize(24);
  mControlSettingsText[3].setPosition(10, 335);

}

//Destruktor (Definition)
ControlSettings::~ControlSettings(){
  
  mpStateGUIManager->deleteGUIObjects();
  pBackButton       = nullptr;
  pSaveApplyButton  = nullptr;
  pMoveLeft         = nullptr;
  pMoveRight        = nullptr;
  pFireWeapon       = nullptr;

  delete mpPlaySettings;
  delete mpMusicMenu;
  delete mpMainSettings;

  mpPlaySettings = nullptr;
  mpMusicMenu = nullptr;
  mpMainSettings = nullptr;
}

//Klassenmethoden (Definition)
//Grundfunktionen
void ControlSettings::handleEvents(){

  //GUIObject Funktionen des ControlSettings States
  //"Click"->Back To Menu
  if (mpStateGUIManager->getGUIObject("ControlSettings/BackToPreGame")->getIsClickedGUIObject() == true){
    setNextState("State/PreGame");
  }

  //"Click"-> Save and Apply (Control- bzw. PlaySettings)
  if (mpStateGUIManager->getGUIObject("ControlSettings/SaveApply")->getIsClickedGUIObject() == true){

    //Neue Settings speichern bzw. alte Binär-Datei überschreiben
    //1. Schritt: Neue Einstellung abfragen
    mpPlaySettings->setKeyPlayerMoveLeft(getKeyMoveLeft());
    mpPlaySettings->setKeyPlayerMoveRight(getKeyMoveRight());
    mpPlaySettings->setKeyPlayerFireWeapon(getKeyFireWeapon());

    //2. Schritt: Binär-Datei überschreiben
    BinaryData::writeBinaryFile<PlaySettings>("Data/Bin/Settings/playsettings.bin",
      *mpPlaySettings);

    //3. Schritt: Binär-Datei lesen
    *mpPlaySettings = BinaryData::readBinaryFile<PlaySettings>("Data/Bin/Settings/playsettings.bin");

    /*Erzeugung eines Schriftzuges, der als Prüfanzeige dient, sobald die Steuerungseinstellungen
      gespeichert wurden.*/
    mControlSettingsText[4].setFont(mControlSettingsFont);
    if (mLanguageOptions == 1){
      mControlSettingsText[4].setString("Gespeichert!");
      mControlSettingsText[4].setPosition(75.f + mpStateGUIManager->
        getGUIObject("ControlSettings/SaveApply")->getSpriteGUIObject().getTextureRect().
        width / 2.f, 300.f + mpStateGUIManager->getGUIObject("ControlSettings/SaveApply")
        ->getSpriteGUIObject().getTextureRect().height + 50.f);
    }
    else if (mLanguageOptions == 2){
      mControlSettingsText[4].setString("Saved!");
      mControlSettingsText[4].setPosition(150.f + mpStateGUIManager->
        getGUIObject("ControlSettings/SaveApply")->getSpriteGUIObject().getTextureRect().
        width / 2.f, 300.f + mpStateGUIManager->getGUIObject("ControlSettings/SaveApply")
        ->getSpriteGUIObject().getTextureRect().height + 50.f);
    }
    else if (mLanguageOptions == 3){
      mControlSettingsText[4].setString("Enregistre!");
      mControlSettingsText[4].setPosition(100.f + mpStateGUIManager->
        getGUIObject("ControlSettings/SaveApply")->getSpriteGUIObject().getTextureRect().
        width / 2.f, 300.f + mpStateGUIManager->getGUIObject("ControlSettings/SaveApply")
        ->getSpriteGUIObject().getTextureRect().height + 50.f);
    }
    mControlSettingsText[4].setCharacterSize(36);
  }
  
  //"Click"->Textbox (MoveLeft/MoveRight/FireWeapon)
  /*Sobald eine Textbox für eine Änderung der Steurungseinstellungen erneut aktiviert wird
    soll die Prüfanzeige wieder auf Null gesetzt werden.*/
  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true
      || mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true
      || mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    mControlSettingsText[4].setString("");
  }


  //CONTROL SETTINGS
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  //*****************************************MOVE LEFT**********************************************//
  ////////////////////////////////////////////////////////////////////////////////////////////////////

  #pragma region MoveLeft_ALPHABET
  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
          setString("A");
      mKeySetMoveLeft = sf::Keyboard::A;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("B");
      mKeySetMoveLeft = sf::Keyboard::B;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("C");
      mKeySetMoveLeft = sf::Keyboard::C;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("D");
      mKeySetMoveLeft = sf::Keyboard::D;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("E");
      mKeySetMoveLeft = sf::Keyboard::E;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("F");
      mKeySetMoveLeft = sf::Keyboard::F;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("G");
      mKeySetMoveLeft = sf::Keyboard::G;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("H");
      mKeySetMoveLeft = sf::Keyboard::H;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("I");
      mKeySetMoveLeft = sf::Keyboard::I;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("J");
      mKeySetMoveLeft = sf::Keyboard::J;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("K");
      mKeySetMoveLeft = sf::Keyboard::K;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("L");
      mKeySetMoveLeft = sf::Keyboard::L;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("M");
      mKeySetMoveLeft = sf::Keyboard::M;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("N");
      mKeySetMoveLeft = sf::Keyboard::N;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("O");
      mKeySetMoveLeft = sf::Keyboard::O;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("P");
      mKeySetMoveLeft = sf::Keyboard::P;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Q");
      mKeySetMoveLeft = sf::Keyboard::Q;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("R");
      mKeySetMoveLeft = sf::Keyboard::R;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("S");
      mKeySetMoveLeft = sf::Keyboard::S;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("T");
      mKeySetMoveLeft = sf::Keyboard::T;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("U");
      mKeySetMoveLeft = sf::Keyboard::U;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("V");
      mKeySetMoveLeft = sf::Keyboard::V;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("W");
      mKeySetMoveLeft = sf::Keyboard::W;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("X");
      mKeySetMoveLeft = sf::Keyboard::X;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Y");
      mKeySetMoveLeft = sf::Keyboard::Y;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Z");
      mKeySetMoveLeft = sf::Keyboard::Z;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }
  #pragma endregion MoveLeft_ALPHABET

  #pragma region MoveLeft_NUMBLOCK
  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Num0");
      mKeySetMoveLeft = sf::Keyboard::Num0;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Num1");
      mKeySetMoveLeft = sf::Keyboard::Num1;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Num2");
      mKeySetMoveLeft = sf::Keyboard::Num2;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Num3");
      mKeySetMoveLeft = sf::Keyboard::Num3;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Num4");
      mKeySetMoveLeft = sf::Keyboard::Num4;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Num5");
      mKeySetMoveLeft = sf::Keyboard::Num5;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Num6");
      mKeySetMoveLeft = sf::Keyboard::Num6;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Num7");
      mKeySetMoveLeft = sf::Keyboard::Num7;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Num8");
      mKeySetMoveLeft = sf::Keyboard::Num8;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Num9");
      mKeySetMoveLeft = sf::Keyboard::Num9;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }
#pragma endregion MoveLeft_NUMBLOCK

  #pragma region MoveLeft_CONTROLKEYS
  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Key reserved!");
      mKeySetMoveLeft = sf::Keyboard::Left;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("LControl");
      mKeySetMoveLeft = sf::Keyboard::LControl;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("LSift");
      mKeySetMoveLeft = sf::Keyboard::LShift;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("LAlt");
      mKeySetMoveLeft = sf::Keyboard::LAlt;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LSystem)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("LSystem");
      mKeySetMoveLeft = sf::Keyboard::LSystem;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("RControl");
      mKeySetMoveLeft = sf::Keyboard::RControl;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("RShift");
      mKeySetMoveLeft = sf::Keyboard::RShift;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("RAlt");
      mKeySetMoveLeft = sf::Keyboard::RAlt;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::RSystem)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("RSystem");
      mKeySetMoveLeft = sf::Keyboard::RSystem;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Menu)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Menu");
      mKeySetMoveLeft = sf::Keyboard::Menu;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Space");
      mKeySetMoveLeft = sf::Keyboard::Space;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Return");
      mKeySetMoveLeft = sf::Keyboard::Return;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("BackSpace");
      mKeySetMoveLeft = sf::Keyboard::BackSpace;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Tab");
      mKeySetMoveLeft = sf::Keyboard::Tab;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("PageUp");
      mKeySetMoveLeft = sf::Keyboard::PageUp;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("PageDown");
      mKeySetMoveLeft = sf::Keyboard::PageDown;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::End)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("End");
      mKeySetMoveLeft = sf::Keyboard::End;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Home)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Home");
      mKeySetMoveLeft = sf::Keyboard::Home;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Insert)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Insert");
      mKeySetMoveLeft = sf::Keyboard::Insert;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Delete");
      mKeySetMoveLeft = sf::Keyboard::Delete;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Pause)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Pause");
      mKeySetMoveLeft = sf::Keyboard::Pause;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Add");
      mKeySetMoveLeft = sf::Keyboard::Add;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Substract");
      mKeySetMoveLeft = sf::Keyboard::Subtract;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Multiply)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Multiply");
      mKeySetMoveLeft = sf::Keyboard::Multiply;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Divide)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Divide");
      mKeySetMoveLeft = sf::Keyboard::Divide;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Left");
      mKeySetMoveLeft = sf::Keyboard::Left;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Right");
      mKeySetMoveLeft = sf::Keyboard::Right;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Up");
      mKeySetMoveLeft = sf::Keyboard::Up;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Down");
      mKeySetMoveLeft = sf::Keyboard::Down;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }
  #pragma endregion MoveLeft_CONTROLKEYS

  #pragma region MoveLeft_SIGNS
  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LBracket)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("LBracket");
      mKeySetMoveLeft = sf::Keyboard::LBracket;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::RBracket)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("RBracket");
      mKeySetMoveLeft = sf::Keyboard::RBracket;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::SemiColon)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("SemiColon");
      mKeySetMoveLeft = sf::Keyboard::SemiColon;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Comma)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Comma");
      mKeySetMoveLeft = sf::Keyboard::Comma;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Period)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Period");
      mKeySetMoveLeft = sf::Keyboard::Period;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Quote)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Quote");
      mKeySetMoveLeft = sf::Keyboard::Quote;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Slash)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Slash");
      mKeySetMoveLeft = sf::Keyboard::Slash;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSlash)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("BackSlash");
      mKeySetMoveLeft = sf::Keyboard::BackSlash;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Tilde");
      mKeySetMoveLeft = sf::Keyboard::Tilde;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Equal");
      mKeySetMoveLeft = sf::Keyboard::Equal;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Dash");
      mKeySetMoveLeft = sf::Keyboard::Dash;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }
  #pragma endregion MoveLeft_SIGNS

  #pragma region MoveLeft_NUMPAD
  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Numpad0");
      mKeySetMoveLeft = sf::Keyboard::Numpad0;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Numpad1");
      mKeySetMoveLeft = sf::Keyboard::Numpad1;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Numpad2");
      mKeySetMoveLeft = sf::Keyboard::Numpad2;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Numpad3");
      mKeySetMoveLeft = sf::Keyboard::Numpad3;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Numpad4");
      mKeySetMoveLeft = sf::Keyboard::Numpad4;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Numpad5");
      mKeySetMoveLeft = sf::Keyboard::Numpad5;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Numpad6");
      mKeySetMoveLeft = sf::Keyboard::Numpad6;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Numpad7");
      mKeySetMoveLeft = sf::Keyboard::Numpad7;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Numpad8");
      mKeySetMoveLeft = sf::Keyboard::Numpad8;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("Numpad");
      mKeySetMoveLeft = sf::Keyboard::Numpad9;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }
  #pragma endregion MoveLeft_NUMPAD

  #pragma region MoveLeft_FKEYS
  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("F1");
      mKeySetMoveLeft = sf::Keyboard::F1;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("F2");
      mKeySetMoveLeft = sf::Keyboard::F2;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("F3");
      mKeySetMoveLeft = sf::Keyboard::F3;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F4)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("F4");
      mKeySetMoveLeft = sf::Keyboard::F4;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("F5");
      mKeySetMoveLeft = sf::Keyboard::F5;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F6)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("F6");
      mKeySetMoveLeft = sf::Keyboard::F6;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F7)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("F7");
      mKeySetMoveLeft = sf::Keyboard::F7;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F8)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("F8");
      mKeySetMoveLeft = sf::Keyboard::F8;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F9)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("F9");
      mKeySetMoveLeft = sf::Keyboard::F9;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F10)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("F10");
      mKeySetMoveLeft = sf::Keyboard::F10;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("F11");
      mKeySetMoveLeft = sf::Keyboard::F11;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F12)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("F12");
      mKeySetMoveLeft = sf::Keyboard::F12;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F13)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("F13");
      mKeySetMoveLeft = sf::Keyboard::F13;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F14)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("F14");
      mKeySetMoveLeft = sf::Keyboard::F14;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F15)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->getTextGUIObject().
        setString("F15");
      mKeySetMoveLeft = sf::Keyboard::F15;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveLeft")->setIsActiveGUIObject(false);
    }
  }
  #pragma endregion MoveLeft_FKEYS

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  //***************************************END MOVE LEFT********************************************//
  ////////////////////////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  //*****************************************MOVE RIGHT*********************************************//
  ////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma region MoveRight_ALPHABET
  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("A");
      mKeySetMoveRight = sf::Keyboard::A;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("B");
      mKeySetMoveRight = sf::Keyboard::B;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("C");
      mKeySetMoveRight = sf::Keyboard::C;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("D");
      mKeySetMoveRight = sf::Keyboard::D;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("E");
      mKeySetMoveRight = sf::Keyboard::E;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("F");
      mKeySetMoveRight = sf::Keyboard::F;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("G");
      mKeySetMoveRight = sf::Keyboard::G;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("H");
      mKeySetMoveRight = sf::Keyboard::H;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("I");
      mKeySetMoveRight = sf::Keyboard::I;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("J");
      mKeySetMoveRight = sf::Keyboard::J;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("K");
      mKeySetMoveRight = sf::Keyboard::K;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("L");
      mKeySetMoveRight = sf::Keyboard::L;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("M");
      mKeySetMoveRight = sf::Keyboard::M;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("N");
      mKeySetMoveRight = sf::Keyboard::N;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("O");
      mKeySetMoveRight = sf::Keyboard::O;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("P");
      mKeySetMoveRight = sf::Keyboard::P;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Q");
      mKeySetMoveRight = sf::Keyboard::Q;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("R");
      mKeySetMoveRight = sf::Keyboard::R;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("S");
      mKeySetMoveRight = sf::Keyboard::S;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("T");
      mKeySetMoveRight = sf::Keyboard::T;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("U");
      mKeySetMoveRight = sf::Keyboard::U;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("V");
      mKeySetMoveRight = sf::Keyboard::V;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("W");
      mKeySetMoveRight = sf::Keyboard::W;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("X");
      mKeySetMoveRight = sf::Keyboard::X;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Y");
      mKeySetMoveRight = sf::Keyboard::Y;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Z");
      mKeySetMoveRight = sf::Keyboard::Z;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }
#pragma endregion MoveRight_ALPHABET

#pragma region MoveRight_NUMBLOCK
  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Num0");
      mKeySetMoveRight = sf::Keyboard::Num0;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Num1");
      mKeySetMoveRight = sf::Keyboard::Num1;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Num2");
      mKeySetMoveRight = sf::Keyboard::Num2;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Num3");
      mKeySetMoveRight = sf::Keyboard::Num3;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Num4");
      mKeySetMoveRight = sf::Keyboard::Num4;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Num5");
      mKeySetMoveRight = sf::Keyboard::Num5;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Num6");
      mKeySetMoveRight = sf::Keyboard::Num6;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Num7");
      mKeySetMoveRight = sf::Keyboard::Num7;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Num8");
      mKeySetMoveRight = sf::Keyboard::Num8;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Num9");
      mKeySetMoveRight = sf::Keyboard::Num9;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }
#pragma endregion MoveRight_NUMBLOCK

#pragma region MoveRight_CONTROLKEYS
  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Key reserved!");
      mKeySetMoveRight = sf::Keyboard::Right;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("LControl");
      mKeySetMoveRight = sf::Keyboard::LControl;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("LSift");
      mKeySetMoveRight = sf::Keyboard::LShift;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("LAlt");
      mKeySetMoveRight = sf::Keyboard::LAlt;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LSystem)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("LSystem");
      mKeySetMoveRight = sf::Keyboard::LSystem;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("RControl");
      mKeySetMoveRight = sf::Keyboard::RControl;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("RShift");
      mKeySetMoveRight = sf::Keyboard::RShift;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("RAlt");
      mKeySetMoveRight = sf::Keyboard::RAlt;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::RSystem)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("RSystem");
      mKeySetMoveRight = sf::Keyboard::RSystem;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Menu)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Menu");
      mKeySetMoveRight = sf::Keyboard::Menu;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Space");
      mKeySetMoveRight = sf::Keyboard::Space;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Return");
      mKeySetMoveRight = sf::Keyboard::Return;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("BackSpace");
      mKeySetMoveRight = sf::Keyboard::BackSpace;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Tab");
      mKeySetMoveRight = sf::Keyboard::Tab;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("PageUp");
      mKeySetMoveRight = sf::Keyboard::PageUp;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("PageDown");
      mKeySetMoveRight = sf::Keyboard::PageDown;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::End)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("End");
      mKeySetMoveRight = sf::Keyboard::End;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Home)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Home");
      mKeySetMoveRight = sf::Keyboard::Home;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Insert)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Insert");
      mKeySetMoveRight = sf::Keyboard::Insert;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Delete");
      mKeySetMoveRight = sf::Keyboard::Delete;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Pause)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Pause");
      mKeySetMoveRight = sf::Keyboard::Pause;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Add");
      mKeySetMoveRight = sf::Keyboard::Add;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Substract");
      mKeySetMoveRight = sf::Keyboard::Subtract;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Multiply)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Multiply");
      mKeySetMoveRight = sf::Keyboard::Multiply;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Divide)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Divide");
      mKeySetMoveRight = sf::Keyboard::Divide;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Left");
      mKeySetMoveRight = sf::Keyboard::Left;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Right");
      mKeySetMoveRight = sf::Keyboard::Right;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Up");
      mKeySetMoveRight = sf::Keyboard::Up;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Down");
      mKeySetMoveRight = sf::Keyboard::Down;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }
#pragma endregion MoveRight_CONTROLKEYS

#pragma region MoveRight_SIGNS
  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LBracket)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("LBracket");
      mKeySetMoveRight = sf::Keyboard::LBracket;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::RBracket)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("RBracket");
      mKeySetMoveRight = sf::Keyboard::RBracket;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::SemiColon)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("SemiColon");
      mKeySetMoveRight = sf::Keyboard::SemiColon;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Comma)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Comma");
      mKeySetMoveRight = sf::Keyboard::Comma;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Period)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Period");
      mKeySetMoveRight = sf::Keyboard::Period;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Quote)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Quote");
      mKeySetMoveRight = sf::Keyboard::Quote;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Slash)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Slash");
      mKeySetMoveRight = sf::Keyboard::Slash;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSlash)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("BackSlash");
      mKeySetMoveRight = sf::Keyboard::BackSlash;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Tilde");
      mKeySetMoveRight = sf::Keyboard::Tilde;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Equal");
      mKeySetMoveRight = sf::Keyboard::Equal;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Dash");
      mKeySetMoveRight = sf::Keyboard::Dash;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }
#pragma endregion MoveRight_SIGNS

#pragma region MoveRight_NUMPAD
  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Numpad0");
      mKeySetMoveRight = sf::Keyboard::Numpad0;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Numpad1");
      mKeySetMoveRight = sf::Keyboard::Numpad1;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Numpad2");
      mKeySetMoveRight = sf::Keyboard::Numpad2;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Numpad3");
      mKeySetMoveRight = sf::Keyboard::Numpad3;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Numpad4");
      mKeySetMoveRight = sf::Keyboard::Numpad4;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Numpad5");
      mKeySetMoveRight = sf::Keyboard::Numpad5;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Numpad6");
      mKeySetMoveRight = sf::Keyboard::Numpad6;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Numpad7");
      mKeySetMoveRight = sf::Keyboard::Numpad7;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Numpad8");
      mKeySetMoveRight = sf::Keyboard::Numpad8;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("Numpad");
      mKeySetMoveRight = sf::Keyboard::Numpad9;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }
#pragma endregion MoveRight_NUMPAD

#pragma region MoveRight_FKEYS
  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("F1");
      mKeySetMoveRight = sf::Keyboard::F1;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("F2");
      mKeySetMoveRight = sf::Keyboard::F2;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("F3");
      mKeySetMoveRight = sf::Keyboard::F3;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F4)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("F4");
      mKeySetMoveRight = sf::Keyboard::F4;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("F5");
      mKeySetMoveRight = sf::Keyboard::F5;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F6)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("F6");
      mKeySetMoveRight = sf::Keyboard::F6;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F7)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("F7");
      mKeySetMoveRight = sf::Keyboard::F7;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F8)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("F8");
      mKeySetMoveRight = sf::Keyboard::F8;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F9)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("F9");
      mKeySetMoveRight = sf::Keyboard::F9;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F10)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("F10");
      mKeySetMoveRight = sf::Keyboard::F10;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("F11");
      mKeySetMoveRight = sf::Keyboard::F11;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F12)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("F12");
      mKeySetMoveRight = sf::Keyboard::F12;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F13)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("F13");
      mKeySetMoveRight = sf::Keyboard::F13;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F14)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("F14");
      mKeySetMoveRight = sf::Keyboard::F14;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F15)){
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->getTextGUIObject().
        setString("F15");
      mKeySetMoveRight = sf::Keyboard::F15;
      mpStateGUIManager->getGUIObject("ControlSettings/MoveRight")->setIsActiveGUIObject(false);
    }
  }
#pragma endregion MoveRight_FKEYS

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  //***************************************END MOVE RIGHT*******************************************//
  ////////////////////////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  //*****************************************FIRE WEAPON********************************************//
  ////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma region FireWeapon_ALPHABET
  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("A");
      mKeySetFireWeapon = sf::Keyboard::A;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("B");
      mKeySetFireWeapon = sf::Keyboard::B;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("C");
      mKeySetFireWeapon = sf::Keyboard::C;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("D");
      mKeySetFireWeapon = sf::Keyboard::D;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("E");
      mKeySetFireWeapon = sf::Keyboard::E;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("F");
      mKeySetFireWeapon = sf::Keyboard::F;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("G");
      mKeySetFireWeapon = sf::Keyboard::G;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("H");
      mKeySetFireWeapon = sf::Keyboard::H;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("I");
      mKeySetFireWeapon = sf::Keyboard::I;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("J");
      mKeySetFireWeapon = sf::Keyboard::J;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("K");
      mKeySetFireWeapon = sf::Keyboard::K;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("L");
      mKeySetFireWeapon = sf::Keyboard::L;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("M");
      mKeySetFireWeapon = sf::Keyboard::M;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("N");
      mKeySetFireWeapon = sf::Keyboard::N;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("O");
      mKeySetFireWeapon = sf::Keyboard::O;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("P");
      mKeySetFireWeapon = sf::Keyboard::P;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Q");
      mKeySetFireWeapon = sf::Keyboard::Q;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("R");
      mKeySetFireWeapon = sf::Keyboard::R;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("S");
      mKeySetFireWeapon = sf::Keyboard::S;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("T");
      mKeySetFireWeapon = sf::Keyboard::T;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("U");
      mKeySetFireWeapon = sf::Keyboard::U;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("V");
      mKeySetFireWeapon = sf::Keyboard::V;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("W");
      mKeySetFireWeapon = sf::Keyboard::W;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("X");
      mKeySetFireWeapon = sf::Keyboard::X;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Y");
      mKeySetFireWeapon = sf::Keyboard::Y;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Z");
      mKeySetFireWeapon = sf::Keyboard::Z;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }
#pragma endregion FireWeapon_ALPHABET

#pragma region FireWeapon_NUMBLOCK
  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Num0");
      mKeySetFireWeapon = sf::Keyboard::Num0;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Num1");
      mKeySetFireWeapon = sf::Keyboard::Num1;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Num2");
      mKeySetFireWeapon = sf::Keyboard::Num2;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Num3");
      mKeySetFireWeapon = sf::Keyboard::Num3;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Num4");
      mKeySetFireWeapon = sf::Keyboard::Num4;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Num5");
      mKeySetFireWeapon = sf::Keyboard::Num5;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Num6");
      mKeySetFireWeapon = sf::Keyboard::Num6;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Num7");
      mKeySetFireWeapon = sf::Keyboard::Num7;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Num8");
      mKeySetFireWeapon = sf::Keyboard::Num8;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Num9");
      mKeySetFireWeapon = sf::Keyboard::Num9;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }
#pragma endregion FireWeapon_NUMBLOCK

#pragma region FireWeapon_CONTROLKEYS
  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Key reserved!");
      mKeySetFireWeapon = sf::Keyboard::Space;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("LControl");
      mKeySetFireWeapon = sf::Keyboard::LControl;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("LSift");
      mKeySetFireWeapon = sf::Keyboard::LShift;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("LAlt");
      mKeySetFireWeapon = sf::Keyboard::LAlt;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LSystem)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("LSystem");
      mKeySetFireWeapon = sf::Keyboard::LSystem;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("RControl");
      mKeySetFireWeapon = sf::Keyboard::RControl;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("RShift");
      mKeySetFireWeapon = sf::Keyboard::RShift;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("RAlt");
      mKeySetFireWeapon = sf::Keyboard::RAlt;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::RSystem)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("RSystem");
      mKeySetFireWeapon = sf::Keyboard::RSystem;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Menu)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Menu");
      mKeySetFireWeapon = sf::Keyboard::Menu;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Space");
      mKeySetFireWeapon = sf::Keyboard::Space;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Return");
      mKeySetFireWeapon = sf::Keyboard::Return;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("BackSpace");
      mKeySetFireWeapon = sf::Keyboard::BackSpace;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Tab");
      mKeySetFireWeapon = sf::Keyboard::Tab;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("PageUp");
      mKeySetFireWeapon = sf::Keyboard::PageUp;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("PageDown");
      mKeySetFireWeapon = sf::Keyboard::PageDown;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::End)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("End");
      mKeySetFireWeapon = sf::Keyboard::End;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Home)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Home");
      mKeySetFireWeapon = sf::Keyboard::Home;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Insert)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Insert");
      mKeySetFireWeapon = sf::Keyboard::Insert;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Delete");
      mKeySetFireWeapon = sf::Keyboard::Delete;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Pause)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Pause");
      mKeySetFireWeapon = sf::Keyboard::Pause;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Add");
      mKeySetFireWeapon = sf::Keyboard::Add;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Substract");
      mKeySetFireWeapon = sf::Keyboard::Subtract;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Multiply)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Multiply");
      mKeySetFireWeapon = sf::Keyboard::Multiply;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Divide)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Divide");
      mKeySetFireWeapon = sf::Keyboard::Divide;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Left");
      mKeySetFireWeapon = sf::Keyboard::Left;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Right");
      mKeySetFireWeapon = sf::Keyboard::Right;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Up");
      mKeySetFireWeapon = sf::Keyboard::Up;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Down");
      mKeySetFireWeapon = sf::Keyboard::Down;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }
#pragma endregion FireWeapon_CONTROLKEYS

#pragma region FireWeapon_SIGNS
  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LBracket)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("LBracket");
      mKeySetFireWeapon = sf::Keyboard::LBracket;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::RBracket)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("RBracket");
      mKeySetFireWeapon = sf::Keyboard::RBracket;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::SemiColon)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("SemiColon");
      mKeySetFireWeapon = sf::Keyboard::SemiColon;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Comma)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Comma");
      mKeySetFireWeapon = sf::Keyboard::Comma;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Period)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Period");
      mKeySetFireWeapon = sf::Keyboard::Period;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Quote)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Quote");
      mKeySetFireWeapon = sf::Keyboard::Quote;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Slash)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Slash");
      mKeySetFireWeapon = sf::Keyboard::Slash;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSlash)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("BackSlash");
      mKeySetFireWeapon = sf::Keyboard::BackSlash;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Tilde");
      mKeySetFireWeapon = sf::Keyboard::Tilde;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Equal");
      mKeySetFireWeapon = sf::Keyboard::Equal;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Dash");
      mKeySetFireWeapon = sf::Keyboard::Dash;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }
#pragma endregion FireWeapon_SIGNS

#pragma region FireWeapon_NUMPAD
  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Numpad0");
      mKeySetFireWeapon = sf::Keyboard::Numpad0;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Numpad1");
      mKeySetFireWeapon = sf::Keyboard::Numpad1;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Numpad2");
      mKeySetFireWeapon = sf::Keyboard::Numpad2;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Numpad3");
      mKeySetFireWeapon = sf::Keyboard::Numpad3;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Numpad4");
      mKeySetFireWeapon = sf::Keyboard::Numpad4;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Numpad5");
      mKeySetFireWeapon = sf::Keyboard::Numpad5;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Numpad6");
      mKeySetFireWeapon = sf::Keyboard::Numpad6;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Numpad7");
      mKeySetFireWeapon = sf::Keyboard::Numpad7;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Numpad8");
      mKeySetFireWeapon = sf::Keyboard::Numpad8;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("Numpad");
      mKeySetFireWeapon = sf::Keyboard::Numpad9;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }
#pragma endregion FireWeapon_NUMPAD

#pragma region FireWeapon_FKEYS
  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("F1");
      mKeySetFireWeapon = sf::Keyboard::F1;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("F2");
      mKeySetFireWeapon = sf::Keyboard::F2;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("F3");
      mKeySetFireWeapon = sf::Keyboard::F3;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F4)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("F4");
      mKeySetFireWeapon = sf::Keyboard::F4;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("F5");
      mKeySetFireWeapon = sf::Keyboard::F5;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F6)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("F6");
      mKeySetFireWeapon = sf::Keyboard::F6;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F7)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("F7");
      mKeySetFireWeapon = sf::Keyboard::F7;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F8)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("F8");
      mKeySetFireWeapon = sf::Keyboard::F8;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F9)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("F9");
      mKeySetFireWeapon = sf::Keyboard::F9;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F10)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("F10");
      mKeySetFireWeapon = sf::Keyboard::F10;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("F11");
      mKeySetFireWeapon = sf::Keyboard::F11;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F12)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("F12");
      mKeySetFireWeapon = sf::Keyboard::F12;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F13)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("F13");
      mKeySetFireWeapon = sf::Keyboard::F13;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F14)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("F14");
      mKeySetFireWeapon = sf::Keyboard::F14;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }

  if (mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getIsActiveGUIObject() == true){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F15)){
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->getTextGUIObject().
        setString("F15");
      mKeySetFireWeapon = sf::Keyboard::F15;
      mpStateGUIManager->getGUIObject("ControlSettings/FireWeapon")->setIsActiveGUIObject(false);
    }
  }
#pragma endregion FireWeapon_FKEYS

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  //***************************************END FIRE WEAPON******************************************//
  ////////////////////////////////////////////////////////////////////////////////////////////////////
}

void ControlSettings::update(float fFrametime){

}

void ControlSettings::render(){
  gpBasicStateWindow->draw(mControlSettingsText[0]);
  gpBasicStateWindow->draw(mControlSettingsText[1]);
  gpBasicStateWindow->draw(mControlSettingsText[2]);
  gpBasicStateWindow->draw(mControlSettingsText[3]);
  gpBasicStateWindow->draw(mControlSettingsText[4]);
}

//Setter
void ControlSettings::setKeyMoveLeft(sf::Keyboard::Key keyMoveLeft){
  mKeySetMoveLeft = keyMoveLeft;
}

void ControlSettings::setKeyMoveRight(sf::Keyboard::Key keyMoveRight){
  mKeySetMoveRight = keyMoveRight;
}

void ControlSettings::setKeyFireWeapon(sf::Keyboard::Key keyFireWeapon){
  mKeySetFireWeapon = keyFireWeapon;
}

//Getter
const sf::Keyboard::Key ControlSettings::getKeyMoveLeft(){
  return mKeySetMoveLeft;
}

const sf::Keyboard::Key ControlSettings::getKeyMoveRight(){
  return mKeySetMoveRight;
}

const sf::Keyboard::Key ControlSettings::getKeyFireWeapon(){
  return mKeySetFireWeapon;
}

//Spezifische Funktionen
void ControlSettings::enterState(){

  //MainSettings laden (bei Programmstart mit Defaultwerten, sonst bereits gespeicherte
  mpMainSettings = new MainSettings();
  *mpMainSettings = BinaryData::readBinaryFile<MainSettings>("Data/Bin/Settings/mainsettings.bin");

  //Musik-Instanz initiieren
  mpMusicMenu = new sf::Music;
  if (!mpMusicMenu->openFromFile("Data/Sounds/Music/backgroundMenu.ogg")){
    std::string error("Could not load Music for mpMusicMenu from: ");
    error.append("Data/Sounds/Music/backgroundMenu.ogg");
    error.append("\n");
    error.append("Check data path. Remember, that only wav, flac, ogg, mp3 are supported!");
    throw std::exception(error.c_str());
  }

  //Hintergrund-Musik
  //Lautstärke je nach geladenen MainSettings setzen
  mpMusicMenu->setVolume(mpMainSettings->getMusicVolume());
  mpMusicMenu->setLoop(true);

  sf::SoundSource::Status musicStatus = mpMusicMenu->getStatus();
  if (musicStatus == sf::SoundSource::Status::Paused &&
    mpMainSettings->getIsMusicEnabled() == true){
    mpMusicMenu->play();
  }
  else if (musicStatus == sf::SoundSource::Status::Playing &&
    mpMainSettings->getIsMusicEnabled() == false){
    mpMusicMenu->stop();
  }
  else if (musicStatus == sf::SoundSource::Status::Stopped
    && mpMainSettings->getIsMusicEnabled() == true){
    mpMusicMenu->play();
  }

  //Spracheinstellungen
  mLanguageOptions = mpMainSettings->getLanguage();
  std::string sBackButtonString = "";
  std::string sSaveApplyString = "";

  if (mLanguageOptions == 1){
    mControlSettingsText[0].setString("Steuerungseinstellungen");
    mControlSettingsText[1].setString("Taste: Bewegung nach links");
    mControlSettingsText[2].setString("Taste: Bewegung nach rechts");
    mControlSettingsText[3].setString("Taste: Feuern");

    sBackButtonString = "Zurueck";
    sSaveApplyString = "Speichern";
  }
  else if (mLanguageOptions == 2){
    mControlSettingsText[0].setString("Control Settings");
    mControlSettingsText[1].setString("Set Key: Move Left");
    mControlSettingsText[2].setString("Set Key: Move Right");
    mControlSettingsText[3].setString("Set Key: Fire Weapon");

    sBackButtonString = "Back";
    sSaveApplyString = "Save";
  }
  else if (mLanguageOptions == 3){
    mControlSettingsText[0].setString("Parametres De Controle");
    mControlSettingsText[1].setString("Touche Programmee: Tournez a Gauche");
    mControlSettingsText[2].setString("Touche Programmee: Tournez a Droite");
    mControlSettingsText[3].setString("Touche Programmee: Arme a Feu");

    sBackButtonString = "Retour";
    sSaveApplyString = "Enregistrer";
  }

  //PlaySettings laden
  mpPlaySettings = new PlaySettings();
  *mpPlaySettings = BinaryData::readBinaryFile<PlaySettings>("Data/Bin/Settings/playsettings.bin");

  //GUI (Button) initialisieren
  pBackButton = new Button("ControlSettings/BackToPreGame", sf::Vector2f(100, 100),
      sf::Vector2f(1, 1), "Data/Textures/GUI/Button/ButtonTexture.png", sBackButtonString);
  pSaveApplyButton = new Button("ControlSettings/SaveApply", sf::Vector2f(100, 100),
      sf::Vector2f(1, 1), "Data/Textures/GUI/Button/ButtonTexture.png", sSaveApplyString);

  //Button ausrichten
  pBackButton->setPositionGUIObject(sf::Vector2f(222.f - pBackButton->getSpriteGUIObject().
      getTextureRect().width/2.f, 530.f));
  pSaveApplyButton->setPositionGUIObject(sf::Vector2f(350.f + pSaveApplyButton->getSpriteGUIObject().
      getTextureRect().width / 4.f, 530.f));

  //Button registrieren
  mpStateGUIManager->registerGUIObject(pBackButton);
  mpStateGUIManager->registerGUIObject(pSaveApplyButton);

  //GUI (Textbox) initialisieren
  pMoveLeft = new Textbox("ControlSettings/MoveLeft", sf::Vector2f(100, 100),
    sf::Vector2f(300, 50), "");
  pMoveRight = new Textbox("ControlSettings/MoveRight", sf::Vector2f(100, 100),
    sf::Vector2f(300, 50), "");
  pFireWeapon = new Textbox("ControlSettings/FireWeapon", sf::Vector2f(100, 100),
    sf::Vector2f(300, 50), "");

  //Textbox ausrichten
  if (mLanguageOptions == 1 || mLanguageOptions == 2){
    pMoveLeft->setTextboxPosition(sf::Vector2f(550.f - pMoveLeft->getSpriteGUIObject().
      getTextureRect().width, 175.f));
    pMoveRight->setTextboxPosition(sf::Vector2f(550.f - pMoveLeft->getSpriteGUIObject().
      getTextureRect().width / 2.f, 250.f));
    pFireWeapon->setTextboxPosition(sf::Vector2f(550.f - pMoveLeft->getSpriteGUIObject().
      getTextureRect().width / 2.f, 325.f));
  }
  else if (mLanguageOptions == 3){
    pMoveLeft->setTextboxPosition(sf::Vector2f(750.f - pMoveLeft->getSpriteGUIObject().
      getTextureRect().width, 175.f));
    pMoveRight->setTextboxPosition(sf::Vector2f(750.f - pMoveLeft->getSpriteGUIObject().
      getTextureRect().width / 2.f, 250.f));
    pFireWeapon->setTextboxPosition(sf::Vector2f(750.f - pMoveLeft->getSpriteGUIObject().
      getTextureRect().width / 2.f, 325.f));
  }

  //Textbox registrieren
  mpStateGUIManager->registerGUIObject(pMoveLeft);
  mpStateGUIManager->registerGUIObject(pMoveRight);
  mpStateGUIManager->registerGUIObject(pFireWeapon);
}

void ControlSettings::leaveState(){

  mpStateGUIManager->deleteGUIObjects();
  pBackButton      = nullptr;
  pSaveApplyButton = nullptr;
  pMoveLeft        = nullptr;
  pMoveRight       = nullptr;
  pFireWeapon      = nullptr;

  setNextState("");

  delete mpMainSettings;
  delete mpPlaySettings;

  mpPlaySettings = nullptr;
  mpMainSettings = nullptr;

  mControlSettingsText[4].setString("");

  mpMusicMenu->stop();
  delete mpMusicMenu;
  mpMusicMenu = nullptr;

}