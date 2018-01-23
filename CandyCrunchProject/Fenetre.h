#pragma once
#include <osgViewer/Viewer>
#include "PlateauJeu.h"
#include "CoteDroit.h"
#include "Entete.h"	
#include "Util.h"


using namespace osg;

/*
class Fenetre.
Cette class construit le graphe de scene.
*/
class Fenetre
{
private:

	/*Instance de la Fenetre pour le pattern singleton. */
	static Fenetre *instance;	

public:
	/*Construit le graphe de scène. 
	return:  ref_ptr<osgViewer::Viewer>
	*/
	ref_ptr<osgViewer::Viewer> construireScene();

	/*
	Constructeur de la class Fenetre.
	*/
	Fenetre();

	/*Pattern singleton*/
	static Fenetre *getInstance();

};