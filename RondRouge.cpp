#include "RondRouge.h"

RondRouge::RondRouge(){
	
	
	drawable = new ShapeDrawable;
	drawable->setShape(new Sphere(Vec3(0,0,0),2.0f));
	drawable->setStateSet(Util::getTexture2D("sandy.png"));
	addDrawable(drawable);
}