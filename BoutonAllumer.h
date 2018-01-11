#pragma once
#include <osg/Geode> 
#include <osg/Geometry> 
#include <osg/ShapeDrawable> 
#include <string.h>
#include "Util.h"


using namespace osg;
using namespace std;


/* class Bouton qui hérite de Geode.
Cette classe créé un drawable rond et ayant comme texture une image */
class BoutonAllumer : public Geode{

private:

	/*Définit un drawable*/
	ref_ptr<ShapeDrawable> drawable;

public :

	/*Constructeur de la class Bouton
	parametre : string fileName => nom du fichier image a charger pour le drawable */
	BoutonAllumer(string fileName);
};