#include "PlateauJeu.h"


PlateauJeu *PlateauJeu::instance = 0;

PlateauJeu::PlateauJeu(){

	modele = Modele::getInstance();
	controleur = Controleur::getInstance();
	EvenementUtilisateur * eu = EvenementUtilisateur::getInstance();
	AnimationRotationPath * anim = new AnimationRotationPath();
	 groupeTable = new Group();

	setEventCallback(eu);
	setUpdateCallback(anim);
	
	

	setViewport(new Viewport(0,0,600,600)); 
	
	setReferenceFrame(Camera::ABSOLUTE_RF);
	setClearColor(Vec4(0.f,0.18f,0.18f,1.0f));

	osg::Light* pLight = new osg::Light; 
    pLight->setLightNum( 0 );// On change la lumière par défaut
    pLight->setAmbient( osg::Vec4d(1.0, 1.0, 1.0, 0.0) ); 
    pLight->setDiffuse( osg::Vec4(1.0f, 1.0f, 1.0f, 0.0f) ); 
    pLight->setSpecular(osg::Vec4(1.0f,1.0f,1.0f,1.0f)); 
    pLight->setPosition(osg::Vec4(5.0f,5.0f,2.0f,10.0f)); 
	pLight->setDirection(osg::Vec3(1.0f,5.0f,1.0f)); // direction dans le cas d'un spot 
	 
	pLight->setConstantAttenuation(20); 
	pLight->setLinearAttenuation(2); 
	pLight->setQuadraticAttenuation(0.2); 
	osg::LightSource* pLightSource = new osg::LightSource;    
	pLightSource->setLight( pLight );
	addChild(pLightSource);


	StateSet* state = getOrCreateStateSet(); 

	
	state->setMode( GL_LIGHT0, osg::StateAttribute::ON); 
	
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
	formes[BATEAU] = new TriangleBleu;
	formes[CARRE_GRIS] = new CarreGris;
	formes[ROND] = new RondRouge;

	tabMatrix =  new vector<vector<ref_ptr<MatrixTransform>>>(modele->getNb_cote(), vector<ref_ptr<MatrixTransform>>(modele->getNb_cote()));
	for(int i = 0; i < modele->getNb_cote(); i++){
		for(int j=0; j < modele->getNb_cote(); j++){
			(*tabMatrix)[j][i] = new MatrixTransform;
			addChild((*tabMatrix)[j][i]);
		}
	}
	miseAjourPlateauJeu();

	modele->ajouterObservateur(this);
}
PlateauJeu *PlateauJeu::getInstance(){
	if (instance == 0)
		instance = new PlateauJeu();

	return instance;
}


void PlateauJeu::miseAjourPlateauJeu(){


	
	Vec3 eye = Vec3(0,0,100+modele->getZoom());
	Vec3 center = Vec3(0,0,0);
	Vec3 up = Vec3(0,1000,1000);

	//configuration de la caméra
	setViewMatrixAsLookAt(eye,center,up);

	
	if(!modele->isFrustrum()){
		setProjectionMatrixAsOrtho(0,modele->getNb_cote()*modele->getCoefficient()+0.2+ modele->getZoom(),0,modele->getNb_cote()*modele->getCoefficient()+0.2   + modele->getZoom(),20,105);	
	}
	else
		setProjectionMatrixAsFrustum(0,(modele->getNb_cote()*modele->getCoefficient()+0.5) ,0,modele->getNb_cote()*modele->getCoefficient()+0.5,20,105);
	

	if(modele->getFichierCharger()){
		chargerNouveauPlateau();
		modele->setFichierCharger(false);
	}

	vector<vector<int>> *tab = modele->getTableau();

	
	//La boucle for place les éléments
	for(int i=0;i<modele->getNb_cote();i++){
		for(int j=0;j<modele->getNb_cote();j++){

			 if((*tab)[j][i] == ROND)
				(*tabMatrix)[j][i]->setMatrix(Matrix::rotate(23.7,5,0,0));
			else
				(*tabMatrix)[j][i]->setMatrix(Matrix::identity());

			(*tabMatrix)[j][i]->postMult(Matrix::translate(3.2+j*COEFFICIENT,3.2+i*COEFFICIENT,0));				
			
			//ajoute la forme aléatoire dans la matrix transform
			

			for(int l=0;l < 4;l++)
				(*tabMatrix)[j][i]->removeChild(formes[l]);

			(*tabMatrix)[j][i]->addChild(formes[(*tab)[j][i] ].get());
			
		}
	}



}

void PlateauJeu::chargerNouveauPlateau(){

		removeChild(mtFond);
	mtFond = new MatrixTransform;
	ShapeDrawable *drawable = new ShapeDrawable;
	double tailleFond = 0;

	if(modele->isFrustrum())
		tailleFond = (6.2+modele->getCoefficient())*modele->getNb_cote();
	else
		tailleFond = (modele->getCoefficient())*modele->getNb_cote();

	drawable->setShape(new Box(Vec3(0,0,0),tailleFond+2,tailleFond+2,1));
	drawable->setColor(Vec4(0.026f,0.49f,0.18f,1.0f));
	drawable->setStateSet(Util::getTexture2D("fond.png"));
	Geode *geo = new Geode();
	geo->addDrawable(drawable);
	mtFond->setMatrix(Matrix::identity());
	mtFond->postMult(Matrix::translate(tailleFond/2,tailleFond/2,-16));
	mtFond->addChild(geo);
	addChild(mtFond);


	dessinerTableau();
}

void PlateauJeu::dessinerTableau(){
	double longueur = COEFFICIENT*modele->getNb_cote();
	double largeur = 0.1*COEFFICIENT;
	
	removeChild(groupeTable);
	groupeTable = new Group();
	groupeTable->addChild(dessinerLigne(2,Vec3f(largeur,largeur,0),Vec3f(largeur,longueur,0)));
	groupeTable->addChild(dessinerLigne(2,Vec3f(largeur,largeur,0),Vec3f(longueur,largeur,0)));	
	for(int i=0;i<modele->getNb_cote();i++){
		//Ajout de ligne vertical
			groupeTable->addChild(dessinerLigne(2,Vec3f((i+1)*COEFFICIENT,0.1*COEFFICIENT,0),Vec3f((i+1)*COEFFICIENT,COEFFICIENT*modele->getNb_cote(),0)));
		//ajout ligne horizontal
		for(int j=0;j<modele->getNb_cote();j++){
			groupeTable->addChild(dessinerLigne(2,Vec3f(0.1*COEFFICIENT,(j+1)*COEFFICIENT,0),Vec3f(COEFFICIENT*modele->getNb_cote(),(j+1)*COEFFICIENT,0)));
		}
	}
	addChild(groupeTable);
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
vector<vector<ref_ptr<MatrixTransform>>> *PlateauJeu::getTabMatrix(){
	return tabMatrix;
}
void PlateauJeu::afficherSelections(){

	mtSelection.get()->setMatrix(Matrix::identity());
	mtSelection2.get()->setMatrix(Matrix::identity());

	mtSelection->postMult(Matrix::translate(0,0,-5));
	mtSelection2->postMult(Matrix::translate(0,0,-5));
	selection select = modele->getSelection();
	if(modele->isFrustrum()){
		mtSelection->postMult(Matrix::translate(3.2+select.x*(5.8+modele->getCoefficient()),3.2+select.y*(5.8+modele->getCoefficient()),-5));
		mtSelection2->postMult(Matrix::translate(3.2+select.x2*(5.8+modele->getCoefficient()),3.2+select.y2*(5.8+modele->getCoefficient()),-5));
	}
	else{
			mtSelection->postMult(Matrix::translate(3.2+select.x*(modele->getCoefficient()),3.2+select.y*(modele->getCoefficient()),-5));
		mtSelection2->postMult(Matrix::translate(3.2+select.x2*(modele->getCoefficient()),3.2+select.y2*(modele->getCoefficient()),-5));

	}
	addChild(mtSelection);
	addChild(mtSelection2);

}

PlateauJeu::~PlateauJeu(){
	free(tabMatrix);
}