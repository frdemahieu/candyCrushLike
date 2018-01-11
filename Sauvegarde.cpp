#include "Sauvegarde.h"

Sauvegarde::Sauvegarde(string nom) {
	fichierLecture = new ifstream(nom,ios::in);
	fichierEcriture =  new ofstream(nom,ios::trunc | ios::out );
	
}
ofstream *Sauvegarde::getFichierEcriture(){
	return fichierEcriture;
}
ifstream *Sauvegarde::getFichierLecture(){
	return fichierLecture;
}
Sauvegarde::~Sauvegarde(){
	fichierEcriture->close();
	fichierLecture->close();
}