/***************************************************************************
* Klassenname Credits
* Date
* Autor(en) Hein, Köhler, Meister
*
* Diese Klasse ist eine Unterklasse des BasicState. In dieser Klasse
* werden die Credits dargestellt.
**************************************************************************/

#include "Credits.h"

//Konstruktor (Definition)
Credits::Credits(){

}

Credits::Credits(sf::RenderWindow *pRenderWindow, sf::Event *pStateEvent, 
    GUIManager *pGUI): mpStateGUIManager(pGUI){
  gpBasicStateWindow = pRenderWindow;
  gpBasicStateEvent  = pStateEvent;

  //Initialisierung Text
  if (!mCreditsFont.loadFromFile("Data/Font/04B_30__.ttf")){
    std::string error("Could not load Font for mCreditsFont from: ");
    error.append("Data/Font/04B_30__.ttf");
    error.append("\n");
    error.append("Check data path and image file formats!");
    throw std::exception(error.c_str());
  }

  //Text Help
  mCreditsText[0].setFont(mCreditsFont);
  mCreditsText[0].setCharacterSize(20);
  mCreditsText[0].setStyle(sf::Text::Bold | sf::Text::Underlined);
  mCreditsText[0].setPosition(20, 40);

  mCreditsText[1].setFont(mCreditsFont);
  mCreditsText[1].setCharacterSize(14);
  mCreditsText[1].setPosition(20, 80);

  mCreditsText[2].setFont(mCreditsFont);
  mCreditsText[2].setCharacterSize(20);
  mCreditsText[2].setStyle(sf::Text::Bold | sf::Text::Underlined);
  mCreditsText[2].setPosition(20, 200);

  mCreditsText[3].setFont(mCreditsFont);
  mCreditsText[3].setCharacterSize(12);
  mCreditsText[3].setPosition(20, 240);

}

//Destruktor (Definition)
Credits::~Credits(){

  mpStateGUIManager->deleteGUIObjects();
  pBackButton = nullptr;

  delete mpMainSettings;
  mpMainSettings = nullptr;

  delete mpMusicMenu;
  mpMusicMenu = nullptr;
}

//Klassenmethoden (Definition)
//Grundfunktionen
void Credits::handleEvents(){
  if (mpStateGUIManager->getGUIObject("Credits/BackToMenu")->getIsClickedGUIObject() == true){
    setNextState("State/Menu");
  }
}

void Credits::update(float fFrametime){

}

void Credits::render(){
  gpBasicStateWindow->draw(mQuads);
  gpBasicStateWindow->draw(mLines);
  gpBasicStateWindow->draw(mCreditsText[0]);
  gpBasicStateWindow->draw(mCreditsText[1]);
  gpBasicStateWindow->draw(mCreditsText[2]);
  gpBasicStateWindow->draw(mCreditsText[3]);


}

//Spezifische Funktionen

void Credits::createPanelGraphic(){

  //Initiieren von zwei PrimitiveTypes
  mQuads = sf::VertexArray(sf::Quads, 4);
  mLines = sf::VertexArray(sf::LinesStrip, 5);

  //Quadrat
  //Definition der (Eck-)Punkte des Quadrates
  mQuads[0].position = sf::Vector2f(5.f, 30.f);
  mQuads[1].position = sf::Vector2f(1275.f, 30.f);
  mQuads[2].position = sf::Vector2f(1275.f, 700.f);
  mQuads[3].position = sf::Vector2f(5.f, 700.f);

  //Definition der Farbe des Quadrats
  mQuads[0].color = sf::Color(0, 0, 0, 255);
  mQuads[1].color = sf::Color(0, 0, 0, 225);
  mQuads[2].color = sf::Color(0, 0, 0, 200);
  mQuads[3].color = sf::Color(0, 0, 0, 225);


  //Linien
  //Definition der Position der Linien
  mLines[0].position = sf::Vector2f(5.f, 30.f);
  mLines[1].position = sf::Vector2f(1275.f, 30.f);
  mLines[2].position = sf::Vector2f(1275.f, 700.f);
  mLines[3].position = sf::Vector2f(5.f, 700.f);
  mLines[4].position = sf::Vector2f(5.f, 30.f);

  //Definition der Farbe der Linien
  mLines[0].color = sf::Color(200, 200, 200, 255);
  mLines[1].color = sf::Color(200, 200, 200, 255);
  mLines[2].color = sf::Color(200, 200, 200, 255);
  mLines[3].color = sf::Color(200, 200, 200, 255);
  mLines[4].color = sf::Color(200, 200, 200, 255);

}
void Credits::enterState(){

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

  std::string sAuthors = "";

  if (mLanguageOptions == 1){
    mCreditsText[0].setString("Autoren:");
    sAuthors.append("Das Projekt wurde im Rahmen eines Studienprojektes\n");
    sAuthors.append("von folgenden Autoren erstellt:\n");
    sAuthors.append
      ("\n");
    sAuthors.append
      ("   ");
    sAuthors.append
      ("Christoph Hein\n");
    sAuthors.append
      ("   ");
    sAuthors.append
      ("Cora Isabella Koehler\n");
    sAuthors.append
      ("   ");
    sAuthors.append
      ("Leon Meister\n");
    mCreditsText[1].setString(sAuthors);

    sBackButtonString = "Hauptmenue";

  }
  else if (mLanguageOptions == 2){
    mCreditsText[0].setString("Authors:");
    sAuthors.append("This project has been created as a part of an student research project \n");
    sAuthors.append("by the following authors : \n");
    sAuthors.append
      ("\n");
    sAuthors.append
      ("   ");
    sAuthors.append
      ("Christoph Hein\n");
    sAuthors.append
      ("   ");
    sAuthors.append
      ("Cora Isabella Koehler\n");
    sAuthors.append
      ("   ");
    sAuthors.append
      ("Leon Meister\n");
    mCreditsText[1].setString(sAuthors);

    sBackButtonString = "MainMenu";

  }
  else if (mLanguageOptions == 3){
    mCreditsText[0].setString("auteurs:");
    sAuthors.append("Le projet a ete cree dans le cadre d'un projet d'etude \n");
    sAuthors.append("par les auteurs suivants \n");
    sAuthors.append
      ("\n");
    sAuthors.append
      ("   ");
    sAuthors.append
      ("Christoph Hein\n");
    sAuthors.append
      ("   ");
    sAuthors.append
      ("Cora Isabella Koehler\n");
    sAuthors.append
      ("   ");
    sAuthors.append
      ("Leon Meister\n");
    mCreditsText[1].setString(sAuthors);

    sBackButtonString = "Menu Principal";

  }

  std::string sSources = "";

  if (mLanguageOptions == 1){
    mCreditsText[2].setString("Quellen:");
    sSources.append("Fuer das Projekt wurden folgende \n");
    sSources.append("Sounds, Grafiken und Tutorials verwendet: \n");
    sSources.append
      ("\n");
    sSources.append("Texturen und Sounds : \n");
    sSources.append
      ("\n      ");
    sSources.append("Texturen fuer Waffen- und Lebensboni: \n");
    sSources.append("       https://opengameart.org/content/free-ui-asset-pack-1 \n");
    sSources.append("       [Platformer asset Pack #4 by Cam Tatz]\n");
    sSources.append
      ("\n   ");
    sSources.append("Font 04b_30 : \n");
    sSources.append("       http://www.dafont.com/de/04b-30.font \n");
    sSources.append("       [by Yuji Oshimoto  http ://www.04.jp.org] \n");
    sSources.append
      ("\n   ");
    sSources.append("Hintergrundgrafik: \n"); 
    sSources.append("       https://opengameart.org/content/bevouliin-free-space-background \n");
    sSources.append("       [FREE SPACE UNIVERSE BACKGROUND by Bevoullin.com] \n");
    sSources.append
      ("\n   ");
    sSources.append("Texturen für Asteroiden und Raumschiff : \n");
    sSources.append("       https://opengameart.org/content/space-shooter-assets \n");
    sSources.append("       [by Immersivegamer] \n");
    sSources.append
      ("\n   ");
    sSources.append("Soundeffekte und Hintergrundmusik : \n");
    sSources.append("       http://www.purple-planet.com/ \n");
    sSources.append
      ("\n");
    sSources.append
      ("\n");
    sSources.append("Tutorials : \n");
    sSources.append
      ("\n      ");
    sSources.append("Grundspiel-Tutorial und GUI-Tutorial aus diversen Videos des Kanals LittleChamberStudios : \n");
    sSources.append("      https://www.youtube.com/user/InformatikTutorial/playlists \n");
    sSources.append
      ("\n");
    sSources.append
      ("\n");
    sSources.append("Spezielle Tools : \n");
    sSources.append
      ("\n      ");
    sSources.append("Chronometer: sftools by Marco Antognini \n");
    sSources.append
      ("      ");
    sSources.append("Collision: LittleMonkey LTD by Nick Koirala und ahnonay \n");
    mCreditsText[3].setString(sSources);

    sBackButtonString = "Hauptmenue";

  }
  else if (mLanguageOptions == 2){
    mCreditsText[2].setString("Sources:");
    sSources.append("The following Sounds, Graphics and Tutorials have bee used for this project: \n");
    sSources.append
      ("\n");
    sSources.append("Textures and Sounds : \n");
    sSources.append
      ("\n      ");
    sSources.append("Textures for Weapon- and HealthBonus : \n");
    sSources.append("       https://opengameart.org/content/free-ui-asset-pack-1 \n");
    sSources.append("       [Platformer asset Pack #4 by Cam Tatz]\n");
    sSources.append
      ("\n   ");
    sSources.append("Font 04b_30 : \n");
    sSources.append("       http://www.dafont.com/de/04b-30.font \n");
    sSources.append("       [by Yuji Oshimoto  http ://www.04.jp.org] \n");
    sSources.append
      ("\n   ");
    sSources.append("Backgrounds: \n");
    sSources.append("       https://opengameart.org/content/bevouliin-free-space-background \n");
    sSources.append("       [FREE SPACE UNIVERSE BACKGROUND by Bevoullin.com] \n");
    sSources.append
      ("\n   ");
    sSources.append("Textures for Asteroids and Spaceship : \n");
    sSources.append("       https://opengameart.org/content/space-shooter-assets \n");
    sSources.append("       [by Immersivegamer] \n");
    sSources.append
      ("\n   ");
    sSources.append("Soundeffects and Backgroundmusic : \n");
    sSources.append("       http://www.purple-planet.com/ \n");
    sSources.append
      ("\n");
    sSources.append
      ("\n");
    sSources.append("Tutorials : \n");
    sSources.append
      ("\n      ");
    sSources.append("MainGame-Tutorial and GUI-Tutorial from videos provided by the Youtube-Channel LittleChamberStudios : \n");
    sSources.append("      https://www.youtube.com/user/InformatikTutorial/playlists \n");
    sSources.append
      ("\n");
    sSources.append
      ("\n");
    sSources.append("Spezified Tools : \n");
    sSources.append
      ("\n      ");
    sSources.append("Chronometer: sftools by Marco Antognini \n");
    sSources.append
      ("      ");
    sSources.append("Collision: LittleMonkey LTD by Nick Koirala und ahnonay \n");
    mCreditsText[3].setString(sSources);

    sBackButtonString = "MainMenu";

  }
  else if (mLanguageOptions == 3){

  mCreditsText[2].setString("Source:");
  sSources.append("les sources suivantes ont ete utilisees pour la musique et les effets de bruit : \n");
  sSources.append
    ("\n");
  sSources.append("textures et effets de bruit : \n");
  sSources.append
    ("\n      ");
  sSources.append("textures d'armes et de bonus de vie : \n");
  sSources.append("       https://opengameart.org/content/free-ui-asset-pack-1 \n");
  sSources.append("       [Platformer asset Pack #4 by Cam Tatz]\n");
  sSources.append
    ("\n   ");
  sSources.append("Font 04b_30 : \n");
  sSources.append("       http://www.dafont.com/de/04b-30.font \n");
  sSources.append("       [by Yuji Oshimoto  http ://www.04.jp.org] \n");
  sSources.append
    ("\n   ");
  sSources.append("image de fond : \n");
  sSources.append("       https://opengameart.org/content/bevouliin-free-space-background \n");
  sSources.append("       [FREE SPACE UNIVERSE BACKGROUND by Bevoullin.com] \n");
  sSources.append
    ("\n   ");
  sSources.append("textures pour les asteroides et le vaisseau spatial : \n");
  sSources.append("       https://opengameart.org/content/space-shooter-assets \n");
  sSources.append("       [by Immersivegamer] \n");
  sSources.append
    ("\n   ");
  sSources.append("effets de bruit et musique de fond : \n");
  sSources.append("       http://www.purple-planet.com/ \n");
  sSources.append
    ("\n");
  sSources.append
    ("\n");
  sSources.append("tutoriels : \n");
  sSources.append
    ("\n      ");
  sSources.append("Didacticiel de jeu de base et Didacticiel de GUI du canal LittleChamberStudios : \n");
  sSources.append("      https://www.youtube.com/user/InformatikTutorial/playlists \n");
  sSources.append
    ("\n");
  sSources.append
    ("\n");
  sSources.append("outils speciaux : \n");
  sSources.append
    ("\n      ");
  sSources.append("Chronometer: sftools by Marco Antognini \n");
  sSources.append
    ("      ");
  sSources.append("Collision: LittleMonkey LTD by Nick Koirala und ahnonay \n");
  mCreditsText[3].setString(sSources);

  sBackButtonString = "Menu Principal";

  }

  //GUI (Button) initialisieren
  pBackButton = new Button("Credits/BackToMenu", sf::Vector2f(100, 100),
      sf::Vector2f(1, 1), "Data/Textures/GUI/Button/ButtonTexture.png", sBackButtonString);

  //Ausrichten
  pBackButton->setPositionGUIObject(sf::Vector2f(800.f, 50.f));

  //Objekte registrieren
  mpStateGUIManager->registerGUIObject(pBackButton);
}

void Credits::leaveState(){
    mpStateGUIManager->deleteGUIObjects();  
    pBackButton = nullptr;

    setNextState("");

    delete mpMainSettings;
    mpMainSettings = nullptr;

    mpMusicMenu->stop();
    delete mpMusicMenu;
    mpMusicMenu = nullptr;
}