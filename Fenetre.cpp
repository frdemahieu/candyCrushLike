#include "Fenetre.h"

Fenetre *Fenetre::instance = 0;

Fenetre::Fenetre(){

}

Fenetre *Fenetre::getInstance(){
	if (instance == 0)
		instance = new Fenetre();

	return instance;
}

ref_ptr<osgViewer::Viewer> Fenetre::construireScene()
{
	ref_ptr<osgViewer::Viewer> fenetre = new osgViewer::Viewer;
	fenetre->setUpViewInWindow(200, 64, 700, 700);
	fenetre->getCamera()->setAllowEventFocus(false);

	osgViewer::Viewer::Windows windows;
	fenetre->getWindows( windows );
	windows[0]->setWindowName("onePiece crunch");

	ref_ptr<Group> groupe;

	groupe = new Group();
	groupe->setName("blaaaa");
	groupe->addChild(PlateauJeu::getInstance());
	groupe->addChild(new CoteDroit);
	groupe->addChild(Entete::getInstance());
	fenetre->setSceneData(groupe);

	return fenetre;
}

