#pragma once
#include <osgViewer/Viewer> 
#include <osg/Geometry> 
#include <osg/ShapeDrawable> 
#include <osg/MatrixTransform>
#include <osgText/Text>
#include <iostream>
#include "Util.h"
#include "Bouton.h"
#include "BoutonAllumer.h"
#include "EvenementUtilisateur.h"
#include "Modele.h"

#define TXT_FORME "Actions"

using namespace osg;

/*Class CoteDroit qui hérite de Camera.
Class qui montre toutes les formes du jeu. */
class CoteDroit : public Camera, public IObservateur{

private:
	ref_ptr<Switch> switchBox; 

	/*pointeur sur l'instance de la class modele.*/
	Modele * modele;

public:
	/*Constructeur de la class CoteDroit*/
	CoteDroit();
	ref_ptr<Switch> getSwitchBox();

	/*
	Méthode hérité de IObservateur. 
	La méthode est appelé par les classes héritant de Observable quand l'état change. 
	return : void.
	*/
	virtual void notifier();
};