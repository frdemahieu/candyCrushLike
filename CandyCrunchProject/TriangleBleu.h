#pragma once
#include <osg/Geode> 
#include <osg/Geometry> 
#include <osg/ShapeDrawable> 
#include <osg/MatrixTransform>
#include <osgViewer/Viewer>
#include "Forme.h"
#include "Util.h"

using namespace osg;

/* class TriangleBleu qui hérite de Forme.
Cette classe créé un drawable triangle et ayant comme texture une image*/
class TriangleBleu : public Forme{

public :

	/*Constructeur de la class TriangleBleu*/
	TriangleBleu();
};