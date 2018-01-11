#pragma once
#include <osgViewer/Viewer> 
#include <osg/Geometry> 
#include <osg/ShapeDrawable> 
#include <osg/MatrixTransform>
#include <osgText/Text>
#include <string>
#include "Modele.h"
#include "Util.h"
#include "EnteteValeur.h"


#define TXT_SCORE "Score"
#define TXT_DEPLACEMENT "D�placement"
#define TXT_DEPLACEMENT_IMPOSSIBLE "Impossible"

#define TXT_GAME_OVER "Vous avez perdu"
#define TXT_GAME_SUCCESS "Vous avez gagn�"
#define TXT_AUCUNE_COMBINAISON "Plus de combinaison possible"

using namespace osgText;
using namespace std;


/* class Entete qui h�rite de Camera et de IObservateur.*/
class Entete : public osg::Camera, public IObservateur
{

private:
	/*instance de Entete singleton*/
	static Entete *instance; 

	/*D�finit un osg::Text qui contient le score courant du joueur*/
	ref_ptr<Text> texteScoreNbr;

	/*D�finit un osg::Text qui contient le nombre de d�placement courant du joueur*/
	ref_ptr<Text> texteNbDeplacementRestant;

	/*D�finit un osg::Text qui contient un message si le joueur essaye de faire une permutation non adjacente entre 2 formes (friandises)*/
	ref_ptr<Text>  texteDeplacementImpossible;

	/* D�finit un string qui contient le scoreMax*/
	string texteScoreMax;

	/*pointeur sur l'instance de la class modele.*/
	Modele * modele;


	/*D�finit un osg::Text qui contient le nom du fichier pour la sauvegarde ou le chargement du fichier de sauvegarde*/
	ref_ptr<Text>  nomFichier;
	
	ref_ptr<Switch> switchBox; 

	ref_ptr<Text>  texteJeuGagner;

	ref_ptr<Text>  texteJeuPerdu;

	ref_ptr<Text>  texteAucuneCombi;

public:

	/*Constructeur de la class Entete*/
	Entete();

	/*Instance du PlateauJeu pour le pattern singleton*/
	static Entete *getInstance();

	/*
	M�thode h�rit� de IObservateur. 
	La m�thode est appel� par les classes h�ritant de Observable quand l'�tat change. 
	return : void.
	*/
	virtual void notifier();

	void switchAllFalse();

};