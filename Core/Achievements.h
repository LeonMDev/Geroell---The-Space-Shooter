#ifndef _ACHIEVEMENTS_H_
#define _ACHIEVEMENTS_H_

#include <string>
#include <sstream>
#include <SFML\Graphics.hpp>

class Achievements{
public:
  //Konstruktoren (Deklaration)
  Achievements();
  Achievements(Achievements &pAchievements);

  /********************************************************************
  * Konstruktorname: Achievements
  * Parameter: string sPlayerName, float fPlayerReachedScore, int iLevel
  * R�ckgabe:  -
  * Dieser Konstruktor erstellt ein Objekt der Klasse Achievements mit der
  * �bergabe des Spielernames, der erreichten Punkte und dem Level.
  ********************************************************************/
  Achievements(std::string sPlayerName, float fPlayerReachedScore, int iLevel);

  //Destruktor (Deklaration)
  virtual ~Achievements();

  //Klassenmethoden (Deklaration)
  //Setter
  void setPlayerName(std::string sPlayerName);
  void setLevel(int iLevel);
  void setReachedScorePlayer(float fPlayerReachedScore);

  //Getter
  const std::string getPlayerName();
  const int getLevel();
  const float getReachedScorePlayer();

private:
  //Klassenattribute
  std::string mPlayerName; 
  int         mLevel;
  float       mPlayerReachedScore;
};

//Operator (global) �berladen (Deklaration)
/********************************************************************
* Methodenname: std::ostream &operator<<
* Parameter: ostream &stream, Achievements &pAchievements
* R�ckgabe:  ostream
* Diese Funktion �berl�dt den Operator "<<".
********************************************************************/
std::ostream &operator<<(std::ostream &stream, Achievements &pAchievements);

#endif //ACHIEVEMENTS_H