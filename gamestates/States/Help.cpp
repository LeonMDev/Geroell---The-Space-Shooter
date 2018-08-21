/***************************************************************************
* Klassenname Help
* Date
* Autor(en) Hein, Köhler, Meister
*
* Diese Klasse ist eine Unterklasse des BasicState. In dieser Klasse
* wird eine kurze Hilfestellung zur Spielmechanik vermittelt.
* Dazu gehören Benennung der Default- bzw. Standardtastenbelegung
* der Spielsteuerung, Angabe der Boni bzw. welche Effekte bei Kollision
* übergeben werden, Tastenbenennung um ins Pausenmenü zu gelangen und
* Zweck/Ziel des Spiels.
**************************************************************************/

#include "Help.h"

//Konstruktor (Definition)
Help::Help(){

}

Help::Help(sf::RenderWindow *pRenderWindow, sf::Event *pStateEvent,
  GUIManager *pGUI) : mpStateGUIManager(pGUI){
  gpBasicStateWindow = pRenderWindow;
  gpBasicStateEvent = pStateEvent;

  //Initialisierung Text
  if (!mHelpFont.loadFromFile("Data/Font/04B_30__.ttf")){
    std::string error("Could not load Font for mHelpFont from: ");
    error.append("Data/Font/04B_30__.ttf");
    error.append("\n");
    error.append("Check data path and image file formats!");
    throw std::exception(error.c_str());
  }

  //Text Help
  mHelpText[0].setFont(mHelpFont);
  mHelpText[0].setCharacterSize(50);
  mHelpText[0].setStyle(sf::Text::Bold | sf::Text::Underlined);
  mHelpText[0].setPosition(20, 40);

  mHelpText[1].setFont(mHelpFont);
  mHelpText[1].setCharacterSize(24);
  mHelpText[1].setPosition(20, 110);

  mHelpText[2].setFont(mHelpFont);
  mHelpText[2].setCharacterSize(50);
  mHelpText[2].setStyle(sf::Text::Bold | sf::Text::Underlined);
  mHelpText[2].setPosition(20, 330);

  mHelpText[3].setFont(mHelpFont);
  mHelpText[3].setCharacterSize(24);
  mHelpText[3].setPosition(20, 400);

  mHelpText[4].setFont(mHelpFont);
  mHelpText[4].setCharacterSize(30);
  mHelpText[4].setPosition(20, 220);

  mHelpText[5].setFont(mHelpFont);
  mHelpText[5].setCharacterSize(24);
  mHelpText[5].setPosition(20, 250);

}

//Destruktor (Definition)
Help::~Help(){

  mpStateGUIManager->deleteGUIObjects();
  pBackButton = nullptr;

  delete mpMainSettings;
  delete mpPanelTexture;
  delete mpPanelSprite;
  delete mpHealthBonusTexture;
  delete mpHealthBonusSprite;
  delete mpLowUpgradeTexture;
  delete mpLowUpgradeSprite;
  delete mpHighUpgradeTexture;
  delete mpHighUpgradeSprite;

  mpMainSettings        = nullptr;
  mpPanelTexture        = nullptr;
  mpPanelSprite         = nullptr;
  mpHealthBonusTexture  = nullptr;
  mpHealthBonusSprite   = nullptr;
  mpLowUpgradeTexture   = nullptr;
  mpLowUpgradeSprite    = nullptr;
  mpHighUpgradeTexture  = nullptr;
  mpHighUpgradeSprite   = nullptr;

  delete mpMusicMenu;
  mpMusicMenu = nullptr;

}

//Klassenmethoden (Definition)
//Grundfunktionen
void Help::handleEvents(){
  if (mpStateGUIManager->getGUIObject("Help/BackToMenu")->getIsClickedGUIObject() == true){
    setNextState("State/Menu");
  }
}

void Help::update(float fFrametime){

}

void Help::render(){
  gpBasicStateWindow->draw(mQuads);
  gpBasicStateWindow->draw(mLines);
  gpBasicStateWindow->draw(mHelpText[0]);
  gpBasicStateWindow->draw(mHelpText[1]);
  gpBasicStateWindow->draw(mHelpText[2]);
  gpBasicStateWindow->draw(mHelpText[3]);
  gpBasicStateWindow->draw(mHelpText[4]);
  gpBasicStateWindow->draw(mHelpText[5]);

  gpBasicStateWindow->draw(*mpHealthBonusSprite);
  gpBasicStateWindow->draw(*mpLowUpgradeSprite);
  gpBasicStateWindow->draw(*mpHighUpgradeSprite);


}



//Spezifische Funktionen

void Help::createPanelGraphic(){

  //Initiieren von zwei PrimitiveTypes
  mQuads = sf::VertexArray(sf::Quads, 4);
  mLines = sf::VertexArray(sf::LinesStrip, 5);

  //Quadrat
  //Definition der (Eck-)Punkte des Quadrates
  mQuads[0].position = sf::Vector2f(5.f, 30.f);
  mQuads[1].position = sf::Vector2f(1200.f, 30.f);
  mQuads[2].position = sf::Vector2f(1200.f, 700.f);
  mQuads[3].position = sf::Vector2f(5.f, 700.f);

  //Definition der Farbe des Quadrats
  mQuads[0].color = sf::Color(0, 0, 0, 255);
  mQuads[1].color = sf::Color(0, 0, 0, 225);
  mQuads[2].color = sf::Color(0, 0, 0, 200);
  mQuads[3].color = sf::Color(0, 0, 0, 225);


  //Linien
  //Definition der Position der Linien
  mLines[0].position = sf::Vector2f(5.f, 30.f);
  mLines[1].position = sf::Vector2f(1200.f, 30.f);
  mLines[2].position = sf::Vector2f(1200.f, 700.f);
  mLines[3].position = sf::Vector2f(5.f, 700.f);
  mLines[4].position = sf::Vector2f(5.f, 30.f);

  //Definition der Farbe der Linien
  mLines[0].color = sf::Color(200, 200, 200, 255);
  mLines[1].color = sf::Color(200, 200, 200, 255);
  mLines[2].color = sf::Color(200, 200, 200, 255);
  mLines[3].color = sf::Color(200, 200, 200, 255);
  mLines[4].color = sf::Color(200, 200, 200, 255);

}


void Help::enterState(){

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

  //Hintergrundpanel
  createPanelGraphic();

  //Spracheinstellungen
  mLanguageOptions = mpMainSettings->getLanguage();
  std::string sBackButtonString = "";

  if (mLanguageOptions == 1){
    sBackButtonString = "Zurueck";
  }
  else if (mLanguageOptions == 2){
    sBackButtonString = "Back";
  }
  else if (mLanguageOptions == 3){
    sBackButtonString = "Retour";
  }

  std::string sDescriptionControlSettings = "";

  if (mLanguageOptions == 1){
    mHelpText[0].setString("Steuerung:");
    sDescriptionControlSettings.append("Standard Tastenbelegung: \n");
    sDescriptionControlSettings.append
      ("   ");
    sDescriptionControlSettings.append
      ("Bewegung nach links - Taste: links\n");
    sDescriptionControlSettings.append
      ("   ");
    sDescriptionControlSettings.append
      ("Bewegung nach rechts - Taste: rechts\n");
    sDescriptionControlSettings.append
      ("   ");
    sDescriptionControlSettings.append
      ("Feuern - Taste: Leertaste\n");
    mHelpText[1].setString(sDescriptionControlSettings);

    sBackButtonString = "Hauptmenue";

  }
  else if (mLanguageOptions == 2){
    mHelpText[0].setString("Control:");
    sDescriptionControlSettings.append("Default Control Settings:\n");
    sDescriptionControlSettings.append
      ("   ");
    sDescriptionControlSettings.append
      ("Move Left - Key: Left\n");
    sDescriptionControlSettings.append
      ("   ");
    sDescriptionControlSettings.append
      ("Move Right - Key: Right\n");
    sDescriptionControlSettings.append
      ("   ");
    sDescriptionControlSettings.append
      ("Fire Weapon - Key: Space\n");
    mHelpText[1].setString(sDescriptionControlSettings);

    sBackButtonString = "MainMenu";

  }
  else if (mLanguageOptions == 3){
    mHelpText[0].setString("Parametres De Controle:");
    sDescriptionControlSettings.append("Touche Standard De Controle:\n");
    sDescriptionControlSettings.append
      ("   ");
    sDescriptionControlSettings.append
      ("Tournez a Gauche - Touche: de Gauche\n");
    sDescriptionControlSettings.append
      ("   ");
    sDescriptionControlSettings.append
      ("Tournez a Gauche - Touche: de Droite\n");
    sDescriptionControlSettings.append
      ("   ");
    sDescriptionControlSettings.append
      ("Arme a Feu - Touche: barre d'espacement\n");
    mHelpText[1].setString(sDescriptionControlSettings);

    sBackButtonString = "Menu Principal";
    
  }

  std::string sKeyPauseMenu = "";

  if (mLanguageOptions == 1){
    mHelpText[4].setString("Pausenmenue:");
    sKeyPauseMenu.append("   ");
    sKeyPauseMenu.append("Taste: Escape\n");
    mHelpText[5].setString(sKeyPauseMenu);

    sBackButtonString = "Hauptmenue";

  }
  else if (mLanguageOptions == 2){
    mHelpText[4].setString("PauseMenu:");
    sKeyPauseMenu.append("   ");
    sKeyPauseMenu.append("Key: Escape \n");
    mHelpText[5].setString(sKeyPauseMenu);

    sBackButtonString = "MainMenu";

  }
  else if (mLanguageOptions == 3){
    mHelpText[4].setString("menu pause:");
    sKeyPauseMenu.append("   ");
    sKeyPauseMenu.append("Touche: d'echappement \n");
    mHelpText[5].setString(sKeyPauseMenu);

    sBackButtonString = "Menu Principal";
  }

  std::string sDescriptionBonusSystem = "";

  if (mLanguageOptions == 1){
    mHelpText[2].setString("Erklaerung Bonussystem:");
    sDescriptionBonusSystem.append("Versuche folgende Boni einzusammeln: \n");
    sDescriptionBonusSystem.append
      ("\n    ");
    sDescriptionBonusSystem.append
      ("Du bekommst eine staerkere Waffe.\n");
    sDescriptionBonusSystem.append
      ("\n    ");
    sDescriptionBonusSystem.append
      ("Du bekommst eine sehr viel staerkere Waffe.\n");
    sDescriptionBonusSystem.append
      ("\n    ");
    sDescriptionBonusSystem.append
      ("Du regenerierst Lebenspunkte.\n");
    mHelpText[3].setString(sDescriptionBonusSystem);

    sBackButtonString = "Hauptmenue";

  }
  else if (mLanguageOptions == 2){
    mHelpText[2].setString("Description Benefit Scheme:");
    sDescriptionBonusSystem.append("Try to collect the following Bonuses:\n");
    sDescriptionBonusSystem.append
      ("\n    ");
    sDescriptionBonusSystem.append
      ("You will get a stronger Weapon.\n");
    sDescriptionBonusSystem.append
      ("\n    ");
    sDescriptionBonusSystem.append
      ("You will get a much stronger Weapon.\n");
    sDescriptionBonusSystem.append
      ("\n    ");
    sDescriptionBonusSystem.append
      ("You will regenerate Health.\n");
    mHelpText[3].setString(sDescriptionBonusSystem);

    sBackButtonString = "MainMenu";

  }
  else if (mLanguageOptions == 3){
    mHelpText[2].setString("Declaration du bonussysteme:");
    sDescriptionBonusSystem.append("Essayez de collecter les bonus: \n");
    sDescriptionBonusSystem.append
      ("\n    ");
    sDescriptionBonusSystem.append
      ("Vous obtiendrez une arme plus forte.\n");
    sDescriptionBonusSystem.append
      ("\n    ");
    sDescriptionBonusSystem.append
      ("Vous obtiendrez une arme beaucoup plus forte.\n");
    sDescriptionBonusSystem.append
      ("\n    ");
    sDescriptionBonusSystem.append
      ("Vous regenererez les points essentiels.\n");
    mHelpText[3].setString(sDescriptionBonusSystem);

    sBackButtonString = "Menu Principal";

  }

  //Bonusgraphiken initialisieren
  mpHealthBonusTexture = new sf::Texture;
  mpHealthBonusSprite = new sf::Sprite;

  if (!mpHealthBonusTexture->loadFromFile("Data/Textures/GameObjects/Bonus/healthbonus.png")){
    std::string error("Could not load Texture for mpHealthBonusTexture from: ");
    error.append("Data/Textures/GameObjects/Bonus/healthbonus.png");
    error.append("\n");
    error.append("Check data path and image file formats!");
    throw std::exception(error.c_str());
  }
  mpHealthBonusSprite->setTexture(*mpHealthBonusTexture);
  mpHealthBonusSprite->setPosition(mHelpText[3].getPosition().x + 14.f, 
    mHelpText[3].getPosition().y + 144.f);
  mpHealthBonusSprite->setScale(0.2f, 0.2f);

  mpLowUpgradeTexture = new sf::Texture;
  mpLowUpgradeSprite = new sf::Sprite;

  if (!mpLowUpgradeTexture->loadFromFile("Data/Textures/GameObjects/Bonus/weaponupgrade1.png")){
    std::string error("Could not load Texture for mpLowUpgradeTexture from: ");
    error.append("Data/Textures/GameObjects/Bonus/weaponupgrade1.png");
    error.append("\n");
    error.append("Check data path and image file formats!");
    throw std::exception(error.c_str());
  }
  mpLowUpgradeSprite->setTexture(*mpLowUpgradeTexture);
  mpLowUpgradeSprite->setPosition(mHelpText[3].getPosition().x + 10.f,
    mHelpText[3].getPosition().y + 42.f);
  mpLowUpgradeSprite->setScale(0.2f, 0.2f);

  mpHighUpgradeTexture = new sf::Texture;
  mpHighUpgradeSprite = new sf::Sprite;

  if (!mpHighUpgradeTexture->loadFromFile("Data/Textures/GameObjects/Bonus/weaponupgrade2.png")){
    std::string error("Could not load Texture for mpHighUpgradeTexture from: ");
    error.append("Data/Textures/GameObjects/Bonus/weaponupgrade2.png");
    error.append("\n");
    error.append("Check data path and image file formats!");
    throw std::exception(error.c_str());
  }
  mpHighUpgradeSprite->setTexture(*mpHighUpgradeTexture);
  mpHighUpgradeSprite->setPosition(mHelpText[3].getPosition().x + 10.f,
    mHelpText[3].getPosition().y + 90.f);
  mpHighUpgradeSprite->setScale(0.2f, 0.2f);


  //GUI (Button) initialisieren
  pBackButton = new Button("Help/BackToMenu", sf::Vector2f(100, 100),
    sf::Vector2f(1, 1), "Data/Textures/GUI/Button/ButtonTexture.png", sBackButtonString);

  //Ausrichten
  pBackButton->setPositionGUIObject(sf::Vector2f(300.f
    - pBackButton->getSpriteGUIObject().getTextureRect().width / 2.f, 600.f));

  //Objekte registrieren
  mpStateGUIManager->registerGUIObject(pBackButton);
}

void Help::leaveState(){
  mpStateGUIManager->deleteGUIObjects();
  pBackButton = nullptr;

  setNextState("");

  delete mpMainSettings;
  delete mpPanelTexture;
  delete mpPanelSprite;
  delete mpHealthBonusTexture;
  delete mpHealthBonusSprite;
  delete mpLowUpgradeTexture;
  delete mpLowUpgradeSprite;
  delete mpHighUpgradeTexture;
  delete mpHighUpgradeSprite;

  mpMainSettings = nullptr;
  mpPanelTexture = nullptr;
  mpPanelSprite = nullptr;
  mpHealthBonusTexture = nullptr;
  mpHealthBonusSprite = nullptr;
  mpLowUpgradeTexture = nullptr;
  mpLowUpgradeSprite = nullptr;
  mpHighUpgradeTexture = nullptr;
  mpHighUpgradeSprite = nullptr;

  mpMusicMenu->stop();
  delete mpMusicMenu;
  mpMusicMenu = nullptr;
}