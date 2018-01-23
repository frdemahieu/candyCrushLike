#pragma once
#include <osgViewer/Viewer> 
#include <osgText/Text>
#include <osg/Geometry> 
#include <osg/ShapeDrawable> 
#include <osg/MatrixTransform>
#include <stdarg.h> 
#include <iostream>
#include "CarreVert.h"
#include "CarreGris.h"
#include "RondRouge.h"
#include "TriangleRouge.h"
#include "TriangleBleu.h"
#include "EvenementUtilisateur.h"
#include "Controleur.h"
#include "Modele.h"
#include "Forme.h"
#include "Util.h"


#define CARRE_VERT 0
#define TRIANGLE 1
#define CARRE_GRIS 2
#define ROND 3


#define  COEFFICIENT 6.4

using namespace osg;
using namespace osgText;

/*Classe qui gère le plateau de jeu hérite de Camera et de IObservateur*/
class PlateauJeu : public Camera, IObservateur{

private:

	/*instance du model singleton*/
	static PlateauJeu *instance;

	/*Pointeur sur l'instance de la class Modele*/
	Modele *modele;

	/*Pointeur sur l'instance de la class Controleur*/
	Controleur * controleur;

	/*Définit une pointeur intélligent sur un tableau de 4 formes */
	ref_ptr<Forme> formes[4];

	/*Pointeur de vecteur de vecteur de pointeur intélligent de MatrixTransform.
	Structure de données qui retient pour chaque case du plateau de jeu sa MatrixTransform.
	*/
	vector<vector<ref_ptr<MatrixTransform>>> * tabMatrix;

	/*Définit une Geode qui contiendra un osg::Text pour afficher un message quand 
	le jeu se termine.*/
	ref_ptr<Geode> geoTexteJeuFinis;

	/*Définit une MatrixTransform pour placer un drawable lorsqu'une première forme (friandise) est séléctionné */
	ref_ptr<MatrixTransform> mtSelection;

	/*Définit une MatrixTransform pour placer un drawable lorsqu'une deuxième forme (friandise) est séléctionné */
	ref_ptr<MatrixTransform> mtSelection2;

	/*Définit une MatrixTransform pour placer un drawable qui sera l'image de fond du plateau de jeu */
	ref_ptr<MatrixTransform> mtFond;

public:

	/*Constructeur de la class PlateauJeu*/
	PlateauJeu();

	/*Instance du PlateauJeu pour le pattern singleton*/
	static PlateauJeu *getInstance();

	/*
	Ajoute des lignes pour créé le quadrillage sur le plateau de jeu. 
	Parametre: (illimité)double num => les coordonnées des points
	return : ref_ptr<Geode>.
	*/
	ref_ptr<Geode> dessinerLigne(double num,...);

	/*
	Met a jour le plateau de jeu. 
	return: void.
	*/
	void miseAjourPlateauJeu();

	/*
	Méthode hérité de IObservateur. 
	La méthode est appelé par les classes héritant de Observable quand l'état change. 
	return : void.
	*/
	virtual void notifier();

	/*
	Renvoie le champ tabMatrix. 
	return : vector<vector<ref_ptr<MatrixTransform>>> *. 
	*/
	vector<vector<ref_ptr<MatrixTransform>>> * getTabMatrix();

	/*
	Met à jour les MatrixTransform dédié à la selection( mtSelection et mtSelection2).
	return void. 
	*/
	void afficherSelections();

	/*
	Destructeur de la class PlateauJeu.
	*/
	~PlateauJeu();
};