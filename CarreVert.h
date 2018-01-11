#pragma once
#include <osg/Geode> 
#include <osg/Geometry> 
#include <osg/ShapeDrawable> 
#include <osg/MatrixTransform>
#include <osgViewer/Viewer>
#include "Forme.h"
#include "Util.h"


using namespace osg;

/* class CarreVert qui hérite de Forme.
Cette classe créé un drawable carre et ayant comme texture une image*/
class  CarreVert : public Forme{

public :

	/*Constructeur de la class CarreVert*/
	CarreVert();

};