#pragma once
#include "IObservateur.h"
#include <list>

using namespace std;

/*
class Observable. 
Class utiliser pour le design pattern Observer.
Toutes les class qui doivent se faire observer hérite de cette class.
*/
class Observable
{
public:

	/*Constructeur de la class Observable*/
	Observable();

	/*
	Parcours la liste d'IObservateur et exécute leur méthode notifier() (voir IObservateur). 
	return : void.
	*/
	void notifierObservateurs() const;

	/*
	Ajouter un IObservateur à la liste d'IObservateur. 
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