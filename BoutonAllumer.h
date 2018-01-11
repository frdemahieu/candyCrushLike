#pragma once
#include <osg/Geode> 
#include <osg/Geometry> 
#include <osg/ShapeDrawable> 
#include <string.h>
#include "Util.h"


using namespace osg;
using namespace std;


/* class Bouton qui h�rite de Geode.
Cette classe cr�� un drawable rond et ayant comme texture une image */
class BoutonAllumer : public Geode{

private:

	/*D�finit un drawable*/
	ref_ptr<ShapeDrawable> drawable;

public :

	/*Constructeur de la class Bouton
	parametre : string fileName => nom du fichier image a charger pour le drawable */
	BoutonAllumer(string fileName);
};