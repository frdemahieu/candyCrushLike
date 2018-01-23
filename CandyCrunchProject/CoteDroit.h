#pragma once
#include <osgViewer/Viewer> 
#include <osg/Geometry> 
#include <osg/ShapeDrawable> 
#include <osg/MatrixTransform>
#include <osgText/Text>
#include <iostream>
#include "Util.h"
#include "Bouton.h"
#include "EvenementUtilisateur.h"

#define TXT_FORME "Actions"

using namespace osg;

/*Class CoteDroit qui hérite de Camera.
Class qui montre toutes les formes du jeu. */
class CoteDroit : public Camera{

public:
	/*Constructeur de la class CoteDroit*/
	CoteDroit();

};