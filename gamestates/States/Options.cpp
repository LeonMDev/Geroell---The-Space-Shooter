/***************************************************************************
* Klassenname Options
* Date
* Autor(en) Hein, Köhler, Meister
*
* Diese Klasse ist eine Unterklasse des BasicState. In dieser Klasse
* werden die Optionen verwaltet.
**************************************************************************/
#include "Options.h"

//Konstruktoren (Definition)
Options::Options(){
}

Options::Options(sf::RenderWindow *pRenderWindow, sf::Event *pStateEvent, 
    GUIManager *pGUI): mpStateGUIManager(pGUI){
  gpBasicStateWindow = pRenderWindow;
  gpBasicStateEvent  = pStateEvent;

  //Initialisierung Text
  if (!mOptionsFont.loadFromFile("Data/Font/04B_30__.ttf")){
    std::string error("Could not load Font for mOptionsFont from: ");
    error.append("Data/Font/04B_30__.ttf");
    error.append("\n");
    error.append("Check data path and image file formats!");
    throw std::exception(error.c_str());
  }

  //Text Options
  mOptionsText[0].setFont(mOptionsFont);
  mOptionsText[0].setCharacterSize(50);
  mOptionsText[0].setStyle(sf::Text::Bold | sf::Text::Underlined);
  mOptionsText[0].setPosition(20,40);

  //Text Toggle Music
  mOptionsText[1].setFont(mOptionsFont);
  mOptionsText[1].setCharacterSize(24);
  mOptionsText[1].setPosition(20, 150);

  //Text Music Volume
  mOptionsText[2].setFont(mOptionsFont);
  mOptionsText[2].setCharacterSize(24);
  mOptionsText[2].setPosition(20, 200);

  //Text Toggle Sound Effects
  mOptionsText[3].setFont(mOptionsFont);
  mOptionsText[3].setCharacterSize(24);
  mOptionsText[3].setPosition(20, 250);

  //Text Sound Effects Volume
  mOptionsText[4].setFont(mOptionsFont);
  mOptionsText[4].setCharacterSize(24);
  mOptionsText[4].setPosition(20, 300);

  //Text Language
  mOptionsText[5].setFont(mOptionsFont);
  mOptionsText[5].setCharacterSize(24);
}

//Destruktor (Definition)
Options::~Options(){

  mpStateGUIManager->deleteGUIObjects();
  mpMusicToggle = nullptr;
  mpSoundEffToggle = nullptr;
  pEnglishButton = nullptr;
  pGermanButton = nullptr;
  pFrenchButton = nullptr;
  pMusicVolumeTextbox = nullptr;
  pSoundEffVolumeTextbox = nullptr;
  mpBackButton = nullptr;
  mpSaveApplyButton = nullptr;

  delete mpOptionsSettings;
  mpOptionsSettings = nullptr;

  delete mpMusicMenu;
  mpMusicMenu = nullptr;
}

//Klassenmethoden (Definition)
//Grundfunktionen
void Options::handleEvents(){

  //GUIObject Funktionen des Options States
  //"Click"->Back To Menu
  if (mpStateGUIManager->getGUIObject("Options/BackToMenu")->getIsClickedGUIObject() == true){
    setNextState("State/Menu");
  }

  //"Click"->German Flag
  if (mpStateGUIManager->getGUIObject("Options/German")->getIsClickedGUIObject() == true){
    mLanguageOptions = 1;
  }

  //"Click"->UK Flag
  if (mpStateGUIManager->getGUIObject("Options/English")->getIsClickedGUIObject() == true){
    mLanguageOptions = 2;
  }

  //"Click"->French Flag
  if (mpStateGUIManager->getGUIObject("Options/French")->getIsClickedGUIObject() == true){
    mLanguageOptions = 3;
  }

  //"Click"-> Save and Apply (MainSettings)
  if (mpStateGUIManager->getGUIObject("Options/SaveApply")->getIsClickedGUIObject() == true){

    //Neue Settings speichern bzw. alte Binär-Datei überschreiben
    //1. Schritt: Neue Einstellung abfragen
    mpOptionsSettings->setMusicEnabled(mpMusicToggle->getIsActiveGUIObject());
    mpOptionsSettings->getIsSoundEffEnabled() = mpSoundEffToggle->getIsActiveGUIObject();
    mpOptionsSettings->setLanguage(mLanguageOptions);

    /*Konvertierung String into Integer für Volume Eingabe in Textbox umgewandelt auf
      Lautstärkeregelung der Musik*/
    std::string sMusicVolume(mpStateGUIManager->getGUIObject("Options/MusicVolume")
        ->getTextGUIObject().getString());
    std::stringstream sstrMusicVolume;
    sstrMusicVolume << sMusicVolume;
    int iMusicVolume;
    sstrMusicVolume >> iMusicVolume;

    //Beschränkung der Lautstärkeregulierung auf Werte zwischen 0-100
    if (iMusicVolume <= 100 && iMusicVolume >= 0){
      mpOptionsSettings->getMusicVolume() = float(iMusicVolume);
    }
    else{
      if (mLanguageOptions == 1){
        mpStateGUIManager->getGUIObject("Options/MusicVolume")->getTextGUIObject().
            setString("Ungueltig");
      }
      else if (mLanguageOptions == 2){
        mpStateGUIManager->getGUIObject("Options/MusicVolume")->getTextGUIObject().
            setString("Invalid");
      }
      else if (mLanguageOptions == 3){
        mpStateGUIManager->getGUIObject("Options/MusicVolume")->getTextGUIObject().
          setString("Caduque");
      }
    }

    /*Konvertierung String into Integer für Volume Eingabe in Textbox umgewandelt auf
      Lautstärkeregelung der Sound Effekte*/
    std::string sSoundEffVolume(mpStateGUIManager->getGUIObject("Options/SoundEffectsVolume")
        ->getTextGUIObject().getString());
    std::stringstream sstrSoundEffVolume;
    sstrSoundEffVolume << sSoundEffVolume;
    int iSoundEffVolume;
    sstrSoundEffVolume >> iSoundEffVolume;

    //Beschränkung der Lautstärkeregulierung
    if (iSoundEffVolume <= 100 && iSoundEffVolume >= 0){
      mpOptionsSettings->getSoundEffVolume() = float(iSoundEffVolume);
    }
    else{
      if (mLanguageOptions == 1){
        mpStateGUIManager->getGUIObject("Options/SoundEffectsVolume")->getTextGUIObject().
          setString("Ungueltig");
      }
      else if (mLanguageOptions == 2){
        mpStateGUIManager->getGUIObject("Options/SoundEffectsVolume")->getTextGUIObject().
          setString("Invalid");
      }
      else if (mLanguageOptions == 3){
        mpStateGUIManager->getGUIObject("Options/SoundEffectsVolume")->getTextGUIObject().
          setString("Caduque");
      }
    }

    //2. Schritt: Binär-Datei überschreiben
    BinaryData::writeBinaryFile<MainSettings>("Data/Bin/Settings/mainsettings.bin", 
        *mpOptionsSettings);

    //3. Schritt: Binär-Datei lesen
    *mpOptionsSettings = BinaryData::readBinaryFile<MainSettings>("Data/Bin/Settings/mainsettings.bin");

    /*Erzeugung eines Schriftzuges, der als Prüfanzeige dient, sobald die Einstellungen gespeichert
      wurden*/
    mOptionsText[6].setFont(mOptionsFont);
    mOptionsText[6].setCharacterSize(30);
    mOptionsText[6].setPosition(1280 / 4.f + mpStateGUIManager->getGUIObject("Options/SaveApply")
      ->getSpriteGUIObject().getTextureRect().width / 2, 720 / 4.f + mpStateGUIManager->
      getGUIObject("Options/SaveApply")->getSpriteGUIObject().getTextureRect().height + 375);
    if (mLanguageOptions == 1){
      mOptionsText[6].setString("Gespeichert!");
    }
    else if (mLanguageOptions == 2){
      mOptionsText[6].setString("Saved!");
    }
    else if (mLanguageOptions == 3){
      mOptionsText[6].setString("Enregistre!");
    }
  }

  //"Click"->Textbox
  /*Sobald ein primäres GUIObject, dass zur Regulierung der MainSettings dient, 
    erneut aktiviert wird (für eine erneute Änderung), soll die Prüfanzeige wieder auf "Null" 
    gesetzt werden, damit bei erneuter Speicherung ersichtlich wird, dass gespeichert wurde.*/
  if (mpStateGUIManager->getGUIObject("Options/MusicVolume")->getIsActiveGUIObject() == true
      || mpStateGUIManager->getGUIObject("Options/SoundEffectsVolume")->getIsActiveGUIObject()
      == true){
    mOptionsText[6].setString("");
  }
  if (mpStateGUIManager->getGUIObject("Options/MusicCheck")->getIsClickedGUIObject() == true){
    mOptionsText[6].setString("");
  }
  if (mpStateGUIManager->getGUIObject("Options/SoundEffectCheck")->getIsClickedGUIObject() == true){
    mOptionsText[6].setString("");
  }
  if (mpStateGUIManager->getGUIObject("Options/German")->getIsClickedGUIObject() == true
    || mpStateGUIManager->getGUIObject("Options/English")->getIsClickedGUIObject() == true
    || mpStateGUIManager->getGUIObject("Options/French")->getIsClickedGUIObject() == true){
    mOptionsText[6].setString("");
  }

  /*Methode/If-Block hinzufügen, um zu gewährleisten, dass nur eine Textbox aktiv ist
    und entsprechend nur einzeln und nicht bei beiden gleichzeitig Werte gesetzt werden können.*/
  if (mpStateGUIManager->getGUIObject("Options/MusicVolume")->getIsActiveGUIObject() == true){
    mpStateGUIManager->getGUIObject("Options/SoundEffectsVolume")->setIsBlockedGUIObject(true);
  }
  if (mpStateGUIManager->getGUIObject("Options/MusicVolume")->getIsActiveGUIObject() == false){
    mpStateGUIManager->getGUIObject("Options/SoundEffectsVolume")->setIsBlockedGUIObject(false);
  }
  if (mpStateGUIManager->getGUIObject("Options/SoundEffectsVolume")->getIsActiveGUIObject() == true){
    mpStateGUIManager->getGUIObject("Options/MusicVolume")->setIsBlockedGUIObject(true);
  }
  if (mpStateGUIManager->getGUIObject("Options/SoundEffectsVolume")->getIsActiveGUIObject() == false){
    mpStateGUIManager->getGUIObject("Options/MusicVolume")->setIsBlockedGUIObject(false);
  }
}

void Options::update(float fFrametime){
  if (mLanguageOptions == 1){
    mOptionsText[0].setString("Optionen");
    mOptionsText[1].setString("Musik An/Aus");
    mOptionsText[2].setString("Musiklautstaerke");
    mOptionsText[3].setString("Soundeffekte An/Aus");
    mOptionsText[4].setString("Soundeffekte Lautstaerke");
    mOptionsText[5].setPosition(259, 383);
    mOptionsText[5].setString("Waehle eine Sprache");

    mpBackButton->setButtonText("Zurueck");
    mpSaveApplyButton->setButtonText("Speichern");
  }
  else if (mLanguageOptions == 2){
    mOptionsText[0].setString("Options");
    mOptionsText[1].setString("Music On/Off");
    mOptionsText[2].setString("Music Volume");
    mOptionsText[3].setString("Soundeffects On/Off");
    mOptionsText[4].setString("Sound Effects Volume");
    mOptionsText[5].setPosition(294, 383);
    mOptionsText[5].setString("Choose Language");

    mpBackButton->setButtonText("Back");
    mpSaveApplyButton->setButtonText("Save");
  }
  else if (mLanguageOptions == 3){
    mOptionsText[0].setString("Options");
    mOptionsText[1].setString("Alterne la musique");
    mOptionsText[2].setString("Musique volume");
    mOptionsText[3].setString("Alterne l'effet acoustique");
    mOptionsText[4].setString("Effect acoustique volume");
    mOptionsText[5].setPosition(279, 383);
    mOptionsText[5].setString("Choisis une langue");

    mpBackButton->setButtonText("Retour");
    mpSaveApplyButton->setButtonText("Enregistrer");
  }
}

void Options::render(){
  gpBasicStateWindow->draw(mOptionsText[0]);
  gpBasicStateWindow->draw(mOptionsText[1]);
  gpBasicStateWindow->draw(mOptionsText[2]);
  gpBasicStateWindow->draw(mOptionsText[3]);
  gpBasicStateWindow->draw(mOptionsText[4]);
  gpBasicStateWindow->draw(mOptionsText[5]);
  gpBasicStateWindow->draw(mOptionsText[6]);
}

void Options::enterState(){
  mpOptionsSettings = new MainSettings();
  *mpOptionsSettings = BinaryData::readBinaryFile<MainSettings>("Data/Bin/Settings/mainsettings.bin");

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
  mpMusicMenu->setVolume(mpOptionsSettings->getMusicVolume());
  mpMusicMenu->setLoop(true);

  sf::SoundSource::Status musicStatus = mpMusicMenu->getStatus();
  if (musicStatus == sf::SoundSource::Status::Paused &&
    mpOptionsSettings->getIsMusicEnabled() == true){
    mpMusicMenu->play();
  }
  else if (musicStatus == sf::SoundSource::Status::Playing &&
    mpOptionsSettings->getIsMusicEnabled() == false){
    mpMusicMenu->stop();
  }
  else if (musicStatus == sf::SoundSource::Status::Stopped
    && mpOptionsSettings->getIsMusicEnabled() == true){
    mpMusicMenu->play();
  }

  //Spracheinstellungen
  mLanguageOptions = mpOptionsSettings->getLanguage();

  //GUI (Button) initialisieren
  mpBackButton = new Button("Options/BackToMenu", sf::Vector2f(100, 100),
      sf::Vector2f(1, 1), "Data/Textures/GUI/Button/ButtonTexture.png", "");
  mpSaveApplyButton = new Button("Options/SaveApply", sf::Vector2f(100, 100),
      sf::Vector2f(1, 1), "Data/Textures/GUI/Button/ButtonTexture.png", "");
  pEnglishButton = new Button("Options/English", sf::Vector2f(32, 20),
      sf::Vector2f(1, 1), "Data/Textures/GUI/Button/UKFlag.png", "");
  pGermanButton = new Button("Options/German", sf::Vector2f(32, 20),
      sf::Vector2f(1, 1), "Data/Textures/GUI/Button/GermanFlag.png", "");
  pFrenchButton = new Button("Options/French", sf::Vector2f(32, 20),
      sf::Vector2f(1, 1), "Data/Textures/GUI/Button/FrenchFlag.png", "");

  //Button ausrichten
  mpBackButton->setPositionGUIObject(sf::Vector2f(222.f - mpBackButton->getSpriteGUIObject().
      getTextureRect().width / 2, 530.f));
  mpSaveApplyButton->setPositionGUIObject(sf::Vector2f(350.f + mpSaveApplyButton
      ->getSpriteGUIObject().getTextureRect().width / 4, 530.f));
  pGermanButton->setPositionGUIObject(sf::Vector2f(246, 435));
  pEnglishButton->setPositionGUIObject(sf::Vector2f(396, 435));
  pFrenchButton->setPositionGUIObject(sf::Vector2f(546, 435));

  //Button registrieren
  mpStateGUIManager->registerGUIObject(mpBackButton);
  mpStateGUIManager->registerGUIObject(mpSaveApplyButton);
  mpStateGUIManager->registerGUIObject(pEnglishButton);
  mpStateGUIManager->registerGUIObject(pGermanButton);
  mpStateGUIManager->registerGUIObject(pFrenchButton);

  //GUI (Checkbox) initialisieren
  mpMusicToggle = new Checkbox("Options/MusicCheck", sf::Vector2f(585.f, 150.f),
      sf::Vector2f(30.f, 30.f));
  mpSoundEffToggle = new Checkbox("Options/SoundEffectCheck", sf::Vector2f(585.f, 250.f),
    sf::Vector2f(30.f, 30.f));

  //Checkbox registrieren
  mpStateGUIManager->registerGUIObject(mpMusicToggle);
  mpStateGUIManager->registerGUIObject(mpSoundEffToggle);

  //Checkboxaktivierung by Default
  mpMusicToggle->setIsActiveGUIObject(mpOptionsSettings->getIsMusicEnabled());
  mpSoundEffToggle->setIsActiveGUIObject(mpOptionsSettings->getIsSoundEffEnabled());

  //GUI (Textbox) initialisieren
  Textbox *pMusicVolumeTextbox = new Textbox("Options/MusicVolume", sf::Vector2f(100, 200),
      sf::Vector2f(60, 30), "");
  Textbox *pSoundEffVolumeTextbox = new Textbox("Options/SoundEffectsVolume", sf::Vector2f(100, 200),
      sf::Vector2f(60, 30), "");

  //Textbox ausrichten
  pMusicVolumeTextbox->setTextboxPosition(sf::Vector2f(570.f, 200.f));
  pSoundEffVolumeTextbox->setTextboxPosition(sf::Vector2f(570.f, 300.f));

  //Konvertieren von integer into String, damit Defaultwerte richtig dargestellt werden
  std::ostringstream osstrMusicVolume;
  std::ostringstream osstrSoundEffVolume;
  osstrMusicVolume << mpOptionsSettings->getMusicVolume();
  osstrSoundEffVolume << mpOptionsSettings->getSoundEffVolume();
  std::string sMusicVolumeTextbox(osstrMusicVolume.str());
  std::string sSoundEffVolumeTextbox(osstrSoundEffVolume.str());

  // Inhalt der Textbox entsprechend den geladenen Einstellungen setzen:
  pMusicVolumeTextbox->getTextGUIObject().setString(sMusicVolumeTextbox);
  pSoundEffVolumeTextbox->getTextGUIObject().setString(sSoundEffVolumeTextbox);

  //Textbox registrieren
  mpStateGUIManager->registerGUIObject(pMusicVolumeTextbox);
  mpStateGUIManager->registerGUIObject(pSoundEffVolumeTextbox);
}

void Options::leaveState(){
  
  mpStateGUIManager->deleteGUIObjects();
  mpMusicToggle          = nullptr;
  mpSoundEffToggle       = nullptr;
  pEnglishButton         = nullptr;
  pGermanButton          = nullptr;
  pFrenchButton          = nullptr;
  pMusicVolumeTextbox    = nullptr;
  pSoundEffVolumeTextbox = nullptr;
  mpBackButton           = nullptr;
  mpSaveApplyButton      = nullptr;

  setNextState("");

  delete mpOptionsSettings;
  mpOptionsSettings = nullptr;

  mOptionsText[6].setString("");

  mpMusicMenu->stop();
  delete mpMusicMenu;
  mpMusicMenu = nullptr;
}