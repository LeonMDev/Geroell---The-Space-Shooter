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
  * R�ckgabe:  -
  * Dieser Konstruktor erstellt ein Objekt der Klasse MainSettings,
  * indem die Werte f�r die Musiklautst�rke, ob Musik angeschaltet ist, 
  * Soundeffektlautst�rke und, ob die Soundeffekte aktiviert sind sowie
  * die gew�hlte Sprache (1 = Deutsch, 2 = Englisch, 3 = Franz�sisch)
  * �bergeben werden.
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