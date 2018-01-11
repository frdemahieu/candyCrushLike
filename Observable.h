#pragma once
#include "IObservateur.h"
#include <list>

using namespace std;

/*
class Observable. 
Class utiliser pour le design pattern Observer.
Toutes les class qui doivent se faire observer h�rite de cette class.
*/
class Observable
{
public:

	/*Constructeur de la class Observable*/
	Observable();

	/*
	Parcours la liste d'IObservateur et ex�cute leur m�thode notifier() (voir IObservateur). 
	return : void.
	*/
	void notifierObservateurs() const;

	/*
	Ajouter un IObservateur � la liste d'IObservateur. 
	return void.
	*/
	void ajouterObservateur(IObservateur* observateur);

	/*
	supprime un IObservateur de la liste d'IObservateur. 
	return void.
	*/
	void supprimerObservateur(IObservateur* observateur);

private:
	/*
	Liste d'IObservateur, 
	*/
	list<IObservateur*> list_observateurs;
};