/***************************************************************************
* Klassenname Achievements
* Date
* Autor(en) Hein, Köhler, Meister
*
* Diese Klasse verwaltet die durch den Spieler erreichten Erfolge, z.B.
* Spielername, erreichte Level, erreichter GameScore....
**************************************************************************/
#include "Achievements.h"


//Konstruktoren (Definition)
Achievements::Achievements() : mPlayerName(""), mPlayerReachedScore(0),
    mLevel(0){

}

//Kopierkonstruktor
Achievements::Achievements(Achievements &pAchievements) :
    mPlayerName(pAchievements.mPlayerName), mLevel(pAchievements.mLevel),
    mPlayerReachedScore(pAchievements.mPlayerReachedScore){

}

Achievements::Achievements(std::string sPlayerName, float fPlayerReachedScore,
    int iLevel):mPlayerName(sPlayerName), mPlayerReachedScore(fPlayerReachedScore),
    mLevel(iLevel){
  
}

//Destruktor (Definition)
Achievements::~Achievements(){
}

//Klassenmethoden (Definition)
//Setter
void Achievements::setPlayerName(std::string sPlayerName){
  mPlayerName = sPlayerName;
}

void Achievements::setLevel(int iLevel){
  mLevel = iLevel;
}

void Achievements::setReachedScorePlayer(float fPlayerReachedScore){
  mPlayerReachedScore = fPlayerReachedScore;
}

//Getter
const std::string Achievements::getPlayerName(){
  return mPlayerName;
}

const int Achievements::getLevel(){
  return mLevel;
}

const float Achievements::getReachedScorePlayer(){
  return mPlayerReachedScore;
}

//Operatorüberladung
std::ostream &operator<<(std::ostream &stream, Achievements &pAchievements){
  stream << "Playername: " << pAchievements.getPlayerName() << std::endl
      << "ReachedScore: " << pAchievements.getReachedScorePlayer() << std::endl
      << "Level: " << pAchievements.getLevel() << std::endl;
  return stream;
}