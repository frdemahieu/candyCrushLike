#include "Entete.h"


// Les membres static non constants doient �tres initialis�s dans le .cpp
Entete *Entete::instance = 0;


Entete *Entete::getInstance(){
	if (instance == 0)
		instance = new Entete();

	return instance;
}

Entete::Entete(){

	modele = Modele::getInstance();
	texteScoreMax = Util::IntToString(modele->getScoreMax());
	

	Vec3 eye = Vec3(0,0,0);
	Vec3 center = Vec3(0,0,-1);
	Vec3 up = Vec3(0,1,0);

	setViewMatrixAsLookAt(eye,center,up);
	setProjectionMatrixAsOrtho(0,14,0,2,0.5,2);
	setViewport(new Viewport(0,600,700,100)); 
	setReferenceFrame(Camera::ABSOLUTE_RF);
	setClearColor(Vec4(0.f,0.18f,0.18f,1.0f));

	osg::Vec3d axeX = osg::Vec3d(1,0,0);
	osg::Vec3d axeY = osg::Vec3d(0,1,0);
	osg::Vec3d axeZ = osg::Vec3d(0,0,1);

	ref_ptr<Geode> geoTexteScore = new Geode();
	geoTexteScore->addDrawable( Util::creerEtPlacerOsgText(TXT_SCORE,0.7,1.5,0,0.5));

	ref_ptr<Geode> geoTexteScoreNbr = new Geode();
	texteScoreNbr = Util::creerEtPlacerOsgText(Util::IntToString(modele->getScore()) +" / "+ texteScoreMax ,0.7,1,0,0.5);
	geoTexteScoreNbr->addDrawable(texteScoreNbr);

	ref_ptr<Geode> geoTexteDeplacement = new Geode();
	geoTexteDeplacement->addDrawable( Util::creerEtPlacerOsgText(TXT_DEPLACEMENT,10.5,1.5,0,0.5));

	ref_ptr<Geode> geoTexteDeplacementImpossible = new Geode();
	texteDeplacementImpossible = Util::creerEtPlacerOsgText("",4,0.2,0,0.5);
	geoTexteDeplacementImpossible->addDrawable(texteDeplacementImpossible);

	ref_ptr<Geode> geoTexteDeplacementNbr = new Geode();
	texteNbDeplacementRestant = Util::creerEtPlacerOsgText(Util::IntToString(modele->getNbDeplacementRestant()),11.5,1,0,0.5);
	geoTexteDeplacementNbr->addDrawable(texteNbDeplacementRestant);

	ref_ptr<Geode> geoTexteJeuFinis = new Geode();
	texteJeuFinis = Util::creerEtPlacerOsgText("",1,0.5,0,0.5);
	texteJeuFinis->setColor(Vec4(1,1,1,1.0f));
	geoTexteJeuFinis->addDrawable(texteJeuFinis);
	addChild(geoTexteJeuFinis);

	ref_ptr<Geode> geoNomFichier = new Geode();
	nomFichier = Util::creerEtPlacerOsgText("",1,0.5,0,0.5);
	nomFichier->setColor(Vec4(1,1,1,1.0f));
	geoNomFichier->addDrawable(nomFichier);
	addChild(geoNomFichier);

	ref_ptr<Geode> geo = new Geode();
	ShapeDrawable *drawable = new ShapeDrawable;
	drawable->setShape(new Box(Vec3(0,0,0),4,1,4));
	drawable->setColor(Vec4(0.f,0.18f,0.18f,1.0f));
	drawable->setStateSet(Util::getTexture2D("titre.png"));
	geo->addDrawable(drawable);
	ref_ptr<MatrixTransform> mt = new MatrixTransform;
	mt->postMult(Matrix::translate(6.5,1.5,1));
	mt->addChild(geo);
	addChild(mt);

	addChild(geoTexteScoreNbr);
	addChild(geoTexteScore);
	addChild(geoTexteDeplacement);
	addChild(geoTexteDeplacementImpossible);
	addChild(geoTexteDeplacementNbr);

	modele->ajouterObservateur(this);
	
}



void Entete::notifier(){

	if(!modele->getPlateauAJour()){
		texteNbDeplacementRestant->setText(Util::IntToString(modele->getNbDeplacementRestant()));
		texteScoreNbr->setText(Util::IntToString(modele->getScore()) +" / "+texteScoreMax );
	}
	if(modele->getEcritureEnCours() != 0){
		nomFichier->setText("Fichier : " + modele->getFichierSauvegarde());
	}
	else{
		nomFichier->setText("");
	}

	if(!modele->getAfficherMsgErreur())
		texteDeplacementImpossible->setText("");
	else
		texteDeplacementImpossible->setText(TXT_DEPLACEMENT_IMPOSSIBLE);

	if(modele->getJeuFinis()){
			texteJeuFinis->setCharacterSize(1); 
			if(modele->getScore() >= modele->getScoreMax())
				texteJeuFinis->setText(TXT_GAME_SUCCESS);
		else if(modele->getNbDeplacementRestant() == 0)
			texteJeuFinis->setText(TXT_GAME_OVER);
		else{
			texteJeuFinis->setCharacterSize(0.6); 
			texteJeuFinis->setText(TXT_AUCUNE_COMBINAISON);
		}
	}
}





