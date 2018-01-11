#include "Modele.h"
int Modele::getScore(){
	return score;
}

int Modele::getScoreMax(){
	return scoreMax;
}


void Modele::setScore(int newScore){
	score = newScore;
}

int Modele::getNbDeplacementRestant(){
	return nbDeplacementRestant;
}

void Modele::setNbDeplacementRestant(int newNbDeplacementRestant){
	nbDeplacementRestant = newNbDeplacementRestant;
}

string Modele::getFichierSauvegarde(){
	return fichierSauvegarde;
}

void Modele::setFichierSauvegarde(string fichier){
	fichierSauvegarde=fichier;
	notifierObservateurs();

}
int Modele::getEcritureEnCours(){
	return ecritureEnCours;
}
void Modele::setEcritureEnCours(int etat){
	ecritureEnCours = etat;
	notifierObservateurs();
}
