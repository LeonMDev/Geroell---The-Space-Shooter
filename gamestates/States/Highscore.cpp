/***************************************************************************
* Klassenname Highscore
* Date
* Autor(en) Hein, Köhler, Meister
*
* Diese Klasse ist eine Unterklasse des BasicState und ist die graphische
* Ausgabe der Highscore-Liste.
**************************************************************************/
#include "Highscore.h"
#include <iostream>

//Konstruktoren (Definition)
Highscore::Highscore(){

}

Highscore::Highscore(sf::RenderWindow *pRenderWindow, sf::Event *pStateEvent,
    GUIManager *pGUI):mpStateGUIManager(pGUI){
  gpBasicStateWindow = pRenderWindow;
  gpBasicStateEvent  = pStateEvent;

  //Initialisierung Text
  if (!mHighscoreFont.loadFromFile("Data/Font/04B_30__.ttf")){
    std::string error("Could not load Font for mHighscoreFont from: ");
    error.append("Data/Font/04B_30__.ttf");
    error.append("\n");
    error.append("Check data path and image file formats!");
    throw std::exception(error.c_str());
  }

  //Text PreGame Settings
  mHighscoreText[0].setFont(mHighscoreFont);
  mHighscoreText[0].setCharacterSize(50);
  mHighscoreText[0].setStyle(sf::Text::Bold | sf::Text::Underlined);
  mHighscoreText[0].setPosition(20, 40);

  mTitleText.setFont(mHighscoreFont);
  mTitleText.setPosition(20, 40);

  for (int i = 1; i <= 15; i++){
    mHighscoreText[i].setFont(mHighscoreFont);
    mHighscoreText[i].setCharacterSize(24);
    mTitleText.setStyle(sf::Text::Bold | sf::Text::Underlined);
  }

}

//Destruktor (Definition)
Highscore::~Highscore(){

  mpStateGUIManager->deleteGUIObjects();
  pBackButton = nullptr;

  delete mpMainSettings;
  delete mpMusicHighscore;

  mpMainSettings = nullptr;
  mpMusicHighscore = nullptr;


}

//Klassenmethoden (Definition)
//Grundfunktionen
void Highscore::handleEvents(){
  if (mpStateGUIManager->getGUIObject("Highscore/BackToMenu")->getIsClickedGUIObject() == true){
    setNextState("State/Menu");
  }
}

void Highscore::update(float fFrametime){

}

void Highscore::render(){
  gpBasicStateWindow->draw(mHighscoreText[0]);
  int iItMax = mHighscoreVector.size() * 3;
  for (int i = 1; i <= iItMax && i<= 15; i++){
    if (i <= iItMax) {
      gpBasicStateWindow->draw(mHighscoreText[i]);
    }
  }
}

//Spezifische Funktionen
void Highscore::enterState(){
  
  //MainSettings laden (bei Programmstart mit Defaultwerten, sonst bereits gespeicherte
  mpMainSettings = new MainSettings();
  *mpMainSettings = BinaryData::readBinaryFile<MainSettings>("Data/Bin/Settings/mainsettings.bin");

  //Musik-Instanz initiieren
  mpMusicHighscore = new sf::Music;
  if (!mpMusicHighscore->openFromFile("Data/Sounds/Music/backgroundHighscore.ogg")){
    std::string error("Could not load Music for mpMusicHighscore from: ");
    error.append("Data/Sounds/Music/backgroundHighscore.ogg");
    error.append("\n");
    error.append("Check data path. Remember, that only wav, flac, ogg, mp3 are supported!");
    throw std::exception(error.c_str());
  }

  //Hintergrund-Musik
  //Lautstärke je nach geladenen MainSettings setzen
  mpMusicHighscore->setVolume(mpMainSettings->getMusicVolume());
  mpMusicHighscore->setLoop(true);

  sf::SoundSource::Status musicStatus = mpMusicHighscore->getStatus();

  //*mpMainSettings = BinaryData::readBinaryFile<MainSettings>("Data/Bin/Settings/mainsettings.bin");

  if (musicStatus == sf::SoundSource::Status::Paused &&
    mpMainSettings->getIsMusicEnabled() == true){
    mpMusicHighscore->play();
  }
  else if (musicStatus == sf::SoundSource::Status::Playing &&
    mpMainSettings->getIsMusicEnabled() == false){
    mpMusicHighscore->stop();
  }
  else if (musicStatus == sf::SoundSource::Status::Stopped
    && mpMainSettings->getIsMusicEnabled() == true){
    mpMusicHighscore->play();
  }

  //Spracheinstellungen
  mLanguageOptions = mpMainSettings->getLanguage();
  std::string sBackButtonString = "";

  if (mLanguageOptions == 1){
    mHighscoreText[0].setString("HIGHSCORE");
    sBackButtonString = "Hauptmenue";
  }
  else if (mLanguageOptions == 2){
    mHighscoreText[0].setString("HIGHSCORE");
    sBackButtonString = "Main Menu";
  }
  else if (mLanguageOptions == 3){
    mHighscoreText[0].setString("SCORE ELEVE");
    sBackButtonString = "Menu Principal";
  }

  //GUI (Button) initialisieren
  pBackButton = new Button("Highscore/BackToMenu", sf::Vector2f(100, 100),
      sf::Vector2f(1, 1), "Data/Textures/GUI/Button/ButtonTexture.png", sBackButtonString);

  //Button ausrichten
  pBackButton->setPositionGUIObject(sf::Vector2f(222.f
    - pBackButton->getSpriteGUIObject().getTextureRect().width / 2.f, 530.f));

  //Objekte registrieren
  mpStateGUIManager->registerGUIObject(pBackButton);

  //Vector erstellen
  
  //std::vector<std::string> vecHighscore;
  std::string sLine = "";
  std::ifstream ifstrReadHighscore("Data/Highscore/highscore.txt");
  //Vector fuellen durch Einlesen der highscore.txt
  if (ifstrReadHighscore.is_open()){
    while (getline(ifstrReadHighscore, sLine)) {
      mHighscoreVector.push_back(sLine);
    }
    ifstrReadHighscore.close();
  }

  int iFound = 0;
  unsigned int iItmax = 5;
  if (mHighscoreVector.size() < iItmax) {
    iItmax = mHighscoreVector.size();
  }

  for (unsigned int i = 0; i < iItmax; i++){
    std::string sCurrentString = mHighscoreVector[i];
    iFound = sCurrentString.find("_");

    if (iFound != std::string::npos){
      std::string strName = sCurrentString.substr(iFound + 1);
      std::string strPunkte = sCurrentString.substr(0, iFound);
      std::string strPlace = std::to_string(i+1);
      if (i == 0){
        mHighscoreText[1].setPosition(sf::Vector2f(20, 120));
        mHighscoreText[1].setString(strPlace);

        mHighscoreText[2].setPosition(sf::Vector2f(120, 120));
        mHighscoreText[2].setString(strName);

        mHighscoreText[3].setPosition(sf::Vector2f(420, 120));
        mHighscoreText[3].setString(strPunkte);
      }
      else if (i == 1){
        mHighscoreText[4].setPosition(sf::Vector2f(20, 170));
        mHighscoreText[4].setString(strPlace);

        mHighscoreText[5].setPosition(sf::Vector2f(120, 170));
        mHighscoreText[5].setString(strName);

        mHighscoreText[6].setPosition(sf::Vector2f(420, 170));
        mHighscoreText[6].setString(strPunkte);
      }
      else if (i == 2){
        mHighscoreText[7].setPosition(sf::Vector2f(20, 220));
        mHighscoreText[7].setString(strPlace);

        mHighscoreText[8].setPosition(sf::Vector2f(120, 220));
        mHighscoreText[8].setString(strName);

        mHighscoreText[9].setPosition(sf::Vector2f(420, 220));
        mHighscoreText[9].setString(strPunkte);
      }
      else if (i == 3){
        mHighscoreText[10].setPosition(sf::Vector2f(20, 270));
        mHighscoreText[10].setString(strPlace);

        mHighscoreText[11].setPosition(sf::Vector2f(120, 270));
        mHighscoreText[11].setString(strName);

        mHighscoreText[12].setPosition(sf::Vector2f(420, 270));
        mHighscoreText[12].setString(strPunkte);
      }
      else if (i == 4){
        mHighscoreText[13].setPosition(sf::Vector2f(20, 320));
        mHighscoreText[13].setString(strPlace);

        mHighscoreText[14].setPosition(sf::Vector2f(120, 320));
        mHighscoreText[14].setString(strName);

        mHighscoreText[15].setPosition(sf::Vector2f(420, 320));
        mHighscoreText[15].setString(strPunkte);
      }
    }
  }
}

void Highscore::leaveState(){
  mpStateGUIManager->deleteGUIObjects();
  pBackButton = nullptr;

  setNextState("");

  delete mpMainSettings;
  mpMainSettings = nullptr;

  mHighscoreVector.clear();

  mpMusicHighscore->stop();
  delete mpMusicHighscore;
  mpMusicHighscore = nullptr;
}