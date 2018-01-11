#include "TriangleBleu.h"

//CHANGER LE NOM EN BATEAU.CPP /!\
//RAPPEL
TriangleBleu::TriangleBleu (){
	
	Geometry* forme = Util::chargerFichier("bateau.object","bois.png");
	osgUtil::SmoothingVisitor sv;
	accept(sv);
	addDrawable(forme);
	
}
