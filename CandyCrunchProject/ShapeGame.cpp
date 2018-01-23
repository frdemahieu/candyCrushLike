#pragma once
#include <osgViewer/Viewer>
#include <osgText/Text>
#include "Fenetre.h"

using namespace osg;

int main(void)
{

	ref_ptr<osgViewer::Viewer> viewer = Fenetre::getInstance()->construireScene();
	DisplaySettings::instance()->setNumMultiSamples( 16 ); 
	// Lancement de la boucle de rendu associ�e au viewer d�fini 
	return viewer->run();
}