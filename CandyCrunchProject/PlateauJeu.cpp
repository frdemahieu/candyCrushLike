#include "PlateauJeu.h"


PlateauJeu *PlateauJeu::instance = 0;

PlateauJeu::PlateauJeu(){

	modele = Modele::getInstance();
	controleur = Controleur::getInstance();
	EvenementUtilisateur * eu = EvenementUtilisateur::getInstance();

	setEventCallback(eu);

	modele->initialiserTableau();

	Vec3 eye = Vec3(0,0,10);
	Vec3 center = Vec3(0,0,-1);
	Vec3 up = Vec3(0,1,0);

	//configuration de la caméra
	setViewMatrixAsLookAt(eye,center,up);
	setViewport(new Viewport(0,0,600,600)); 
	
	setReferenceFrame(Camera::ABSOLUTE_RF);
	setClearColor(Vec4(0.f,0.18f,0.18f,1.0f));


	//Création de la box pour la sélection.
	ShapeDrawable *fondSelection = new ShapeDrawable;
	fondSelection->setShape(new Box(Vec3(0,0,0),6,6,0));
	fondSelection->setColor(Vec4(.5f,0,0,1.0f));
	Geode *geode = new Geode();
	geode->addDrawable(fondSelection);
	mtSelection = new MatrixTransform;
	mtSelection2 = new MatrixTransform;
	mtSelection2->addChild(geode);
	mtSelection->addChild(geode);

	double longueur = COEFFICIENT*modele->getNb_cote();
	double largeur = 0.1*COEFFICIENT;

	
	formes[CARRE_VERT] = new CarreVert;
	formes[TRIANGLE] = new TriangleBleu;
	formes[CARRE_GRIS] = new CarreGris;
	formes[ROND] = new RondRouge;

	tabMatrix =  new vector<vector<ref_ptr<MatrixTransform>>>(modele->getNb_cote(), vector<ref_ptr<MatrixTransform>>(modele->getNb_cote()));

	miseAjourPlateauJeu();

	modele->ajouterObservateur(this);
}
PlateauJeu *PlateauJeu::getInstance(){
	if (instance == 0)
		instance = new PlateauJeu();

	return instance;
}


void PlateauJeu::miseAjourPlateauJeu(){

	setProjectionMatrixAsOrtho(0,modele->getNb_cote()*COEFFICIENT+0.2,0,modele->getNb_cote()*COEFFICIENT+0.2,0.5,15);
	double longueur = COEFFICIENT*modele->getNb_cote();
	double largeur = 0.1*COEFFICIENT;
	
	removeChild(mtFond);
	mtFond = new MatrixTransform;
	ShapeDrawable *drawable = new ShapeDrawable;
	double tailleFond = 6.5*modele->getNb_cote();
	drawable->setShape(new Box(Vec3(0,0,0),tailleFond+2,tailleFond+2,1));
	drawable->setColor(Vec4(0.026f,0.49f,0.18f,1.0f));
	drawable->setStateSet(Util::getTexture2D("fond.png"));
	Geode *geo = new Geode();
	geo->addDrawable(drawable);
	mtFond->setMatrix(Matrix::identity());
	mtFond->postMult(Matrix::translate(tailleFond/2,tailleFond/2,-16));
	mtFond->addChild(geo);
	addChild(mtFond);

	for(int i = 0; i < tabMatrix->size();i++){
		for(int j = 0; j < tabMatrix->size();j++){
			removeChild((*tabMatrix)[j][i]);
		}
	}



	vector<vector<int>> *tab = modele->getTableau();
	tabMatrix =  new vector<vector<ref_ptr<MatrixTransform>>>(modele->getNb_cote(), vector<ref_ptr<MatrixTransform>>(modele->getNb_cote()));
	addChild(dessinerLigne(2,Vec3f(largeur,largeur,0),Vec3f(largeur,longueur,0)));
	addChild(dessinerLigne(2,Vec3f(largeur,largeur,0),Vec3f(longueur,largeur,0)));
	//La boucle for dessine un tableau
	for(int i=0;i<modele->getNb_cote();i++){
		//Ajout de ligne vertical
			addChild(dessinerLigne(2,Vec3f((i+1)*COEFFICIENT,0.1*COEFFICIENT,0),Vec3f((i+1)*COEFFICIENT,COEFFICIENT*modele->getNb_cote(),0)));
		//ajout ligne horizontal
		for(int j=0;j<modele->getNb_cote();j++){

				addChild(dessinerLigne(2,Vec3f(0.1*COEFFICIENT,(j+1)*COEFFICIENT,0),Vec3f(COEFFICIENT*modele->getNb_cote(),(j+1)*COEFFICIENT,0)));

			ref_ptr<MatrixTransform> mt = new MatrixTransform;

			if((*tab)[j][i] == TRIANGLE)
				mt->setMatrix(Matrix::rotate(5.1,1,0,0));
			else if((*tab)[j][i] == ROND)
				mt->setMatrix(Matrix::rotate(23.7,5,0,0));
			else
				mt->setMatrix(Matrix::identity());

			mt->postMult(Matrix::translate(3.2+j*COEFFICIENT,3.2+i*COEFFICIENT,0));				
			
			//ajoute la forme aléatoire dans la matrix transform
			mt->addChild(formes[(*tab)[j][i] ].get());
			(*tabMatrix)[j][i] = mt;
			addChild(mt);
		}
	}

}


//dessine une ligne et renvoie un géode ( paramètre illimité )
ref_ptr<Geode> PlateauJeu::dessinerLigne(double nbrPoint,...){
	va_list arguments;
	va_start(arguments,nbrPoint);

	//Variable pour les lignes
	ref_ptr<Geometry> lignesGeometrie = new Geometry;
	ref_ptr<Vec3Array> pointsAttachement = new Vec3Array;
	lignesGeometrie->setVertexArray(pointsAttachement.get());

	for(int i=0;i<nbrPoint;i++){
		pointsAttachement->push_back( va_arg(arguments,Vec3f));
	}

	//on dessine les lignes
	lignesGeometrie->addPrimitiveSet(new DrawArrays(PrimitiveSet::LINE_STRIP, 0, nbrPoint));

	ref_ptr<Geode> geode= new Geode;
	geode->addDrawable(lignesGeometrie.get());

	va_end(arguments);

	return geode;

}



void PlateauJeu::notifier(){

	if(!modele->getPlateauAJour()){
		miseAjourPlateauJeu();
	}

	afficherSelections();
			

}

void PlateauJeu::afficherSelections(){

	mtSelection.get()->setMatrix(Matrix::identity());
	mtSelection2.get()->setMatrix(Matrix::identity());

	mtSelection->postMult(Matrix::translate(0,0,-5));
	mtSelection2->postMult(Matrix::translate(0,0,-5));
	selection select = modele->getSelection();

	mtSelection->postMult(Matrix::translate(3.2+select.x*COEFFICIENT,3.2+select.y*COEFFICIENT,-5));
	mtSelection2->postMult(Matrix::translate(3.2+select.x2*COEFFICIENT,3.2+select.y2*COEFFICIENT,-5));
	
	addChild(mtSelection);
	addChild(mtSelection2);

}

PlateauJeu::~PlateauJeu(){
	free(tabMatrix);
}