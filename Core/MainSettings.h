#ifndef _MAINSETTINGS_H_
#define _MAINSETTINGS_H_

#include <string>

class MainSettings{
public:
  //Konstruktor (Deklaration)
  MainSettings();
  
  /********************************************************************
  * Konstruktor: MainSettings
  * Parameter: int iMusicVolume, bool bMusicEnabled, int iSoundEffVolume
  *            bool bSoundEffEnabled, int iLanguage
  * Rückgabe:  -
  * Dieser Konstruktor erstellt ein Objekt der Klasse MainSettings,
  * indem die Werte für die Musiklautstärke, ob Musik angeschaltet ist, 
  * Soundeffektlautstärke und, ob die Soundeffekte aktiviert sind sowie
  * die gewählte Sprache (1 = Deutsch, 2 = Englisch, 3 = Französisch)
  * übergeben werden.
  ********************************************************************/
  MainSettings(float fMusicVolume, bool bMusicEnabled, float fSoundEffVolume,
      bool bSoundEffEnabled, int iLanguage);

  //Destruktor (Deklaration)
  virtual ~MainSettings();

  //Klassenmethoden (Deklaration)
  //Setter
  void setMusicVolume(float fMusicVolume);
  void setSoundEffVolume(float fSoundEffVolume);
  void setMusicEnabled(bool bMusicEnabled);
  void setSoundEffEnabled(bool bSoundEffEnabled);
  void setLanguage(int iLanguage);

  //Getter
  float  &getMusicVolume();
  float  &getSoundEffVolume();
  bool   &getIsMusicEnabled();
  bool   &getIsSoundEffEnabled();
  int    &getLanguage();

private:
  //Klassenattribute
  float  mMusicVolume;
  float  mSoundEffVolume;
  bool   mMusicEnabled;
  bool   mSoundEffEnabled;
  int    mLanguage;
};
#endif //MAINSETTINGS_H