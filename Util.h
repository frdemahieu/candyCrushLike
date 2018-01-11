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

/* class Util d�finit des m�thodes utilitaires.*/
class Util
{

public:

	/*
	Cr�� un osg::Text.  
	Parametre : string txt => le texte � afficher, 
	double x => coordonn�e x, 
	double y => coordonn�e y, 
	double z => coordonn�e z, 
	double taillePolice => taille des caract�res. 
	Return : ref_ptr<Text>
	*/
	static ref_ptr<Text> creerEtPlacerOsgText(string txt, double x, double y,double z, double taillePolice);

	/*
	Transforme un entier de type int en type string.  
	Parametre : int nbr => le nombre � transformer. 
	Return : string
	*/
	static string IntToString(int nbr);

	/*
	cr�� un �tat StateSet. 
	Parametre : string imgName => nom du fichier image a charger. 
	Return : ref_ptr<StateSet>
	*/
	static ref_ptr<StateSet> getTexture2D(string imgName, ref_ptr<StateSet> state = NULL);
	static Geometry* chargerFichier(string stringFichier,string texture);
	static float * getNormale(float * p1, float * p2, float * p3);
};