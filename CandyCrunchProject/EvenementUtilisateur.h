#pragma once
#include "Modele.h"
#include "Controleur.h"
#include "Forme.h"
#include <iostream>
#include <osgGA/GUIEventAdapter>
#include <osgGA/EventVisitor>
#include <osg/MatrixTransform>
#include <osgUtil/LineSegmentIntersector>
#include "Fenetre.h"
#include "PlateauJeu.h"

#define SAUVER 1
#define CHARGER 2

using namespace osgUtil;
using namespace osg;
using namespace osgGA;
using namespace std;

/*
Classe qui va servir � d�finir un "event callback" li� aux actions de l'utilisateur.
*/
class EvenementUtilisateur : public NodeCallback{

private:

	/*instance du EvenementUtilisateur singleton.*/
	static EvenementUtilisateur *instance; 

	/*
	pointeur sur l'instance de la class controleur.
	*/
	Controleur * controleur;

	/*
	pointeur sur l'instance de la class modele.
	*/
	Modele * modele;


public:
	/*Constructeur de la class EvenementUtilisateur*/
	EvenementUtilisateur();

	/*Pattern singleton*/ 
	static EvenementUtilisateur *getInstance();

	/*C'est l'op�rateur ci-dessous, h�rit� de NodeCallback, qui doit �tre red�fini
	afin de g�rer des �v�nements li�s � un Node dans le cadre du parcours d'un NodeVisitor*/
	virtual void operator()(Node* node, NodeVisitor* nv);

	/*
	V�rifie si le clic m�ne � une intersection. 
	Si oui, par rapport aux coordonn�es x et y des m�thodes de la class Modele seron ex�cut�. 
	return:  void
	*/
	void selectionTouche(ref_ptr<GUIEventAdapter> ea, Node* node);

};