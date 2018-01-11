#pragma once
#include "Modele.h"
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <osg/MatrixTransform>
#include <fstream>

using namespace std;
using namespace osg;

/*Class Controleur.
Class qui permet la sauvegarde et le chargement d'un fichier de sauvegarde*/
class Controleur
{

private:

	/*instance du controleur singleton*/
	static Controleur *instance; 

	/*Pointeur sur l'instance de la class Modele*/
	Modele * modeleControleur;

public:

	/*Constructeur de la class Controleur*/
	Controleur();

	/*Instance du PlateauJeu pour le pattern singleton*/
	static Controleur *getInstance();

	/*	
	Sauvegarde le jeu.
	Parametre: string nom => nom donné au fichier de sauvegarde
	Return : void.
	*/
	void sauvegarderJeu(string nom);

	/*	
	charge le jeu.
	Parametre: string nom => nom donné au fichier sauvegardé
	Return : void.
	*/
	void chargerJeu(string nom);

};