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

/*Classe qui g�re le plateau de jeu h�rite de Camera et de IObservateur*/
class PlateauJeu : public Camera, IObservateur{

private:

	/*instance du model singleton*/
	static PlateauJeu *instance;

	/*Pointeur sur l'instance de la class Modele*/
	Modele *modele;

	/*Pointeur sur l'instance de la class Controleur*/
	Controleur * controleur;

	/*D�finit une pointeur int�lligent sur un tableau de 4 formes */
	ref_ptr<Forme> formes[4];

	/*Pointeur de vecteur de vecteur de pointeur int�lligent de MatrixTransform.
	Structure de donn�es qui retient pour chaque case du plateau de jeu sa MatrixTransform.
	*/
	vector<vector<ref_ptr<MatrixTransform>>> * tabMatrix;

	/*D�finit une Geode qui contiendra un osg::Text pour afficher un message quand 
	le jeu se termine.*/
	ref_ptr<Geode> geoTexteJeuFinis;

	/*D�finit une MatrixTransform pour placer un drawable lorsqu'une premi�re forme (friandise) est s�l�ctionn� */
	ref_ptr<MatrixTransform> mtSelection;

	/*D�finit une MatrixTransform pour placer un drawable lorsqu'une deuxi�me forme (friandise) est s�l�ctionn� */
	ref_ptr<MatrixTransform> mtSelection2;

	/*D�finit une MatrixTransform pour placer un drawable qui sera l'image de fond du plateau de jeu */
	ref_ptr<MatrixTransform> mtFond;

public:

	/*Constructeur de la class PlateauJeu*/
	PlateauJeu();

	/*Instance du PlateauJeu pour le pattern singleton*/
	static PlateauJeu *getInstance();

	/*
	Ajoute des lignes pour cr�� le quadrillage sur le plateau de jeu. 
	Parametre: (illimit�)double num => les coordonn�es des points
	return : ref_ptr<Geode>.
	*/
	ref_ptr<Geode> dessinerLigne(double num,...);

	/*
	Met a jour le plateau de jeu. 
	return: void.
	*/
	void miseAjourPlateauJeu();

	/*
	M�thode h�rit� de IObservateur. 
	La m�thode est appel� par les classes h�ritant de Observable quand l'�tat change. 
	return : void.
	*/
	virtual void notifier();

	/*
	Renvoie le champ tabMatrix. 
	return : vector<vector<ref_ptr<MatrixTransform>>> *. 
	*/
	vector<vector<ref_ptr<MatrixTransform>>> * getTabMatrix();

	/*
	Met � jour les MatrixTransform d�di� � la selection( mtSelection et mtSelection2).
	return void. 
	*/
	void afficherSelections();

	/*
	Destructeur de la class PlateauJeu.
	*/
	~PlateauJeu();
};