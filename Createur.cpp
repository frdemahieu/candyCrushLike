#include "Createur.h"


Createur::Memento * Createur::sauverDansMemento(){
	return new Memento(etatModele);
}

void Createur::restaurerDepuisMemento(Createur::Memento * memento){
	etatModele = memento->getEtatMemento();
}

void Createur::setEtatModele(donneeModele * newEtatModele){
	etatModele = newEtatModele;
}

donneeModele * Createur::getEtatModele(){
	return etatModele;
}

Createur::Memento::Memento(donneeModele * newEtatModele){
	Createur::Memento::etatMemento = newEtatModele;
}

donneeModele * Createur::Memento::getEtatMemento(){
	return Createur::Memento::etatMemento;
}

Createur::Createur(){
}