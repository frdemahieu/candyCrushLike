#include "Controleur.h"


// Les membres static non constants doient êtres initialisés dans le .cpp
Controleur *Controleur::instance = 0;

Controleur::Controleur(){
	modeleControleur = Modele::getInstance();
}

Controleur *Controleur::getInstance(){
	if (instance == 0)
		instance = new Controleur();

	return instance;
}
void Controleur::sauvegarderJeu(string nom){
	ofstream fichier (nom);
	fichier << modeleControleur;
	fichier.close();
}

void Controleur::chargerJeu(string nom){
	ifstream fichier (nom);
	modeleControleur->setFichierCharger(true);
	if(fichier.fail()){
		cout << "Le fichier n'existe pas" << endl;
		return;
	}
	fichier >> modeleControleur;
	modeleControleur->setJeuFinis(false);
	modeleControleur->setPlateauAJour(false);
	fichier.close();
}

