#pragma once
#include <osgText/Text>
#include <osgDB/ReadFile>
#include <osg/Material>
#include <string.h>
#include <sstream>
#include <iostream>

using namespace osg;
using namespace osgText;
using namespace std;

/* class Util définit des méthodes utilitaires.*/
class Util
{

public:

	/*
	Créé un osg::Text.  
	Parametre : string txt => le texte à afficher, 
	double x => coordonnée x, 
	double y => coordonnée y, 
	double z => coordonnée z, 
	double taillePolice => taille des caractères. 
	Return : ref_ptr<Text>
	*/
	static ref_ptr<Text> creerEtPlacerOsgText(string txt, double x, double y,double z, double taillePolice);

	/*
	Transforme un entier de type int en type string.  
	Parametre : int nbr => le nombre à transformer. 
	Return : string
	*/
	static string IntToString(int nbr);

	/*
	créé un état StateSet. 
	Parametre : string imgName => nom du fichier image a charger. 
	Return : ref_ptr<StateSet>
	*/
	static ref_ptr<StateSet> getTexture2D(string imgName, ref_ptr<StateSet> state = NULL);
	static Geometry* chargerFichier(string stringFichier,string texture);
	static float * getNormale(float * p1, float * p2, float * p3);
};