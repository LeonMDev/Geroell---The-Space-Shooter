/***************************************************************************
* Klassenname MainSettings
* Date
* Autor(en) Hein, Köhler, Meister
*
* Diese Klasse verwaltet die Haupteinstellungen des Spiels, wie 
* Musiklautstärke, Soundeffektlautstärke etc.
**************************************************************************/
#include "MainSettings.h"

//Konstruktor (Definition)
MainSettings::MainSettings():mMusicVolume(50.f), mMusicEnabled(true),
    mSoundEffVolume(50.f), mSoundEffEnabled(true),mLanguage(1){

}

MainSettings::MainSettings(float fMusicVolume, bool bMusicEnabled,
    float fSoundEffVolume, bool bSoundEffEnabled, int iLanguage):
    mMusicVolume(fMusicVolume), mMusicEnabled(bMusicEnabled), 
    mSoundEffVolume(fSoundEffVolume),mSoundEffEnabled(bSoundEffEnabled),
    mLanguage(iLanguage){

}

//Destruktor (Definition)
MainSettings::~MainSettings(){
}

//Klassenmethoden (Definition)
//Setter
void MainSettings::setMusicVolume(float iMusicVolume){ 
  mMusicVolume = iMusicVolume; 
}

void MainSettings::setSoundEffVolume(float iSoundEffVolume){ 
  mSoundEffVolume = iSoundEffVolume; 
}

void MainSettings::setMusicEnabled(bool bMusicEnabled){ 
  mMusicEnabled = bMusicEnabled; 
}

void MainSettings::setSoundEffEnabled(bool bSoundEffEnabled){ 
  mSoundEffEnabled = bSoundEffEnabled; 
}

void MainSettings::setLanguage(int iLanguage){
  mLanguage = iLanguage;
}

//Getter
float  &MainSettings::getMusicVolume(){ 
  return mMusicVolume; 
}

float  &MainSettings::getSoundEffVolume(){ 
  return mSoundEffVolume; 
}

bool &MainSettings::getIsMusicEnabled(){ 
  return mMusicEnabled; 
}

bool &MainSettings::getIsSoundEffEnabled(){ 
  return mSoundEffEnabled; 
}

int &MainSettings::getLanguage(){
  return mLanguage;
}