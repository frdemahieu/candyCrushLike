#include "CoteDroit.h"

CoteDroit::CoteDroit(){


	Vec3 eye = Vec3(0,0,0);
	Vec3 center = Vec3(0,0,-1);
	Vec3 up = Vec3(0,1,0);

	EvenementUtilisateur * eu = EvenementUtilisateur::getInstance();
	setEventCallback(eu);
	setName("CoteDroit");

	ref_ptr<Geode> geoTexte = new Geode();
	geoTexte->addDrawable(Util::creerEtPlacerOsgText(TXT_FORME,0.5,12,0,0.4));

	setViewMatrixAsLookAt(eye,center,up);
	setProjectionMatrixAsOrtho(0,2,0,14,0.5,2);
	setViewport(new Viewport(600,0,100,600)); 
	setReferenceFrame(Camera::ABSOLUTE_RF);
	setClearColor(Vec4(0.f,0.18f,0.18f,1.0f));

	ref_ptr<MatrixTransform> mtBoutonRejouer = new MatrixTransform;
	mtBoutonRejouer->postMult(Matrix::translate(1,10,0));
	mtBoutonRejouer->addChild(new Bouton("rejouer.png"));
	mtBoutonRejouer->setName("rejouer");

	ref_ptr<MatrixTransform> mtBoutonSauver = new MatrixTransform;
	mtBoutonSauver->postMult(Matrix::translate(1,8,0));
	mtBoutonSauver->addChild(new Bouton("sauver.png"));
	mtBoutonSauver->setName("sauver");


	ref_ptr<MatrixTransform> mtBoutonCharger= new MatrixTransform;
	mtBoutonCharger->postMult(Matrix::translate(1,6,0));
	mtBoutonCharger->addChild(new Bouton("charger.png"));
	mtBoutonCharger->setName("charger");

	ref_ptr<MatrixTransform> mtBoutonAide= new MatrixTransform;
	mtBoutonAide->postMult(Matrix::translate(1,4,0));
	mtBoutonAide->addChild(new Bouton("aide.png"));
	mtBoutonAide->setName("aide");

	addChild(mtBoutonSauver);
	addChild(mtBoutonRejouer);
	addChild(mtBoutonCharger);
	addChild(mtBoutonAide);

	addChild(geoTexte);

}