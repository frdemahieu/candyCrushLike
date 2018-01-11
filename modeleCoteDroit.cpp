#include "Modele.h"
bool Modele::getBoutonAJour(){
	return boutonAJour;
}

int Modele::getIndiceBoutonEteind(){
	return indiceBoutonEteind;
}

int Modele::getIndiceBoutonAllumer(){
	return indiceBoutonAllumer;
}

void Modele::changerAspectBouton(int indiceBouton){

	if(indiceBouton == -1 && boutonAllumer == false)
		return;

	
	
	if(indiceBouton == -1){
		int tmp = indiceBoutonAllumer;
		indiceBoutonAllumer = indiceBoutonEteind;
		indiceBoutonEteind = tmp;
		boutonAllumer = false;
	}else if(boutonAllumer == false){
		indiceBoutonAllumer = indiceBouton +4;
		indiceBoutonEteind = indiceBouton;
		boutonAllumer = true;
		
	}else{
		return;
	}

	boutonAJour = false;
	notifierObservateurs();
	boutonAJour = true;
}
