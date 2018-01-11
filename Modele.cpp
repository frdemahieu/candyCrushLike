#include "Modele.h"


// Les membres static non constants doient êtres initialisés dans le .cpp
Modele *Modele::instance = 0;


Modele::Modele(){
	ifstream fichier("config");
	score = 0;
	fichier >> nbDeplacementFichier;
	fichier >> nb_cote;
	fichier >> scoreMax;
	zoom = 0;
	coefficient = ORTHO;

	fichierCharger = true;
	nbDeplacementRestant = nbDeplacementFichier;
	tableau = new vector<vector<int>>(nb_cote, vector<int>(nb_cote));
	afficherMsgErreur = false;
	plateauAJour = true;
	jeuFinis = false;
	formeSelectionner = false;
	ecritureEnCours = 0;

	objetSelectione.x = VIDE;
	objetSelectione.x2 = VIDE;
	objetSelectione.y = VIDE;
	objetSelectione.y2  = VIDE;
	nbFormeSelectionner = 0;

	boutonAJour = true;
	boutonAllumer = false;
	indiceBoutonAllumer = -1;
	indiceBoutonEteind = -1;

	initialiserTableau();

	gardien = new Gardien();
	createur = new Createur();

	sauverEtatModele();
	
}

Modele *Modele::getInstance(){
	if (instance == 0)
		instance = new Modele();

	return instance;
}


vector<vector<int>> *Modele::getTableau(){
	return tableau;
}


int Modele::getNb_cote(){
	return nb_cote;
}

void Modele::setNb_cote(int newNb_cote){
	nb_cote = newNb_cote;
	tableau = new vector<vector<int>>(newNb_cote, vector<int>(newNb_cote));
}

void Modele::setAfficherMsgErreur(bool newValeur){
	afficherMsgErreur = newValeur;
	notifierObservateurs();
}

bool Modele::getAfficherMsgErreur(){
	return afficherMsgErreur;
}

void Modele::setPlateauAJour(bool newValeur){
	reinitialiserSelection();
	plateauAJour = newValeur;
	if(plateauAJour == false){
		notifierObservateurs();
		plateauAJour = true;
	}



}
void Modele::setSelectionStruct(selection select){
	objetSelectione.x = select.x;
	objetSelectione.x2 = select.x2;
	objetSelectione.y = select.y;
	objetSelectione.y2 = select.y2;
	formeSelectionner = true;
	nbFormeSelectionner = 2;
	notifierObservateurs();
}
bool Modele::getPlateauAJour(){
	return plateauAJour;
}
selection Modele::getSelection(){
	return objetSelectione;
}

void Modele::setJeuFinis(bool newValeur){
	jeuFinis = newValeur;
	notifierObservateurs();
}

bool Modele::getJeuFinis(){
	return jeuFinis;
}
void Modele::setFichierCharger(bool change){
	fichierCharger = change;
}
bool Modele::getFichierCharger(){
	return fichierCharger;
}


ostream& operator<<(ostream& os,Modele *modele){
	os << modele->getNb_cote() << endl;
	os << modele->getScore() << endl;
	os << modele->getNbDeplacementRestant() << endl;

	for(int i = 0; i < modele->getNb_cote();i++){
		for(int j = 0; j < modele->getNb_cote();j++){
			os << (*modele->getTableau())[j][i] << endl;
		}
	}
	return os;
}

istream& operator>>(istream& os,Modele *modele){
	int val;
	os >> val;
	modele->setNb_cote(val);
	os >> val;
	modele->setScore(val);
	os >> val;
	modele->setNbDeplacementRestant(val);

	vector<vector<int>> *tableau = new vector<vector<int>>(val, vector<int>(val));


	for(int i = 0; i < modele->getNb_cote();i++){
		for(int j = 0; j < modele->getNb_cote();j++){
			os >> (*modele->getTableau())[j][i];
		}
	}


	return os;
}





Modele::~Modele(){
	free(tableau);
}

vector<vector<int>> * Modele::copieVector(vector<vector<int>> * vectorCpy){
	vector<vector<int>> * v = new vector<vector<int>>(nb_cote, vector<int>(nb_cote));
	for (int i = 0; i<getNb_cote(); i++){
		for (int j = 0; j<getNb_cote(); j++){
			(*v)[i][j] = (*vectorCpy)[i][j];
		}
	}

	return v;
}


void Modele::sauverEtatModele(){

	donneeModele * etat = new donneeModele();
	etat->nbDeplacement = nbDeplacementRestant;
	etat->score = score;
	etat->tableau = *tableau;
	etat->fin = jeuFinis;
	etat->msgErreur = afficherMsgErreur;

	createur->setEtatModele(etat);
	gardien->ajouterMemento(createur->sauverDansMemento());
}

void Modele::restaurerEtatModele(){

	createur->restaurerDepuisMemento(gardien->getMemento());
	donneeModele * donneeModele = createur->getEtatModele();

	nbDeplacementRestant = donneeModele->nbDeplacement;
	score = donneeModele->score;
	*tableau = donneeModele->tableau;
	jeuFinis = donneeModele->fin;
	afficherMsgErreur = donneeModele->msgErreur;
	setPlateauAJour(false);

}

void Modele::viderEtatModele(){
	gardien->viderMemento();
	sauverEtatModele();
}