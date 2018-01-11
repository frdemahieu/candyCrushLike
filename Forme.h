#pragma once
#include <osg/Geode> 
#include <osg/Geometry> 
#include <osg/ShapeDrawable> 
#include <osg/MatrixTransform>
#include <osgViewer/Viewer>

using namespace osg;

//class Forme qui h�rite de Geode.
//Class g�n�ral pour les formes (friandises) du plateau de jeu.
class Forme : public Geode
{
protected:

	//D�finit un drawable
	ref_ptr<ShapeDrawable> drawable;

public:

	//Constructeur de la class Forme
	Forme();

	//Change la couleur du drawable
	void setCouleur();

};

