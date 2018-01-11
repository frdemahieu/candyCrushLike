#include "BoutonAllumer.h"


BoutonAllumer::BoutonAllumer(string fileName){
	drawable = new ShapeDrawable;
	drawable->setShape(new Box(Vec3(0,0,0),1,1,1));
	drawable->setColor(Vec4(0.f,0.18f,0.18f,1.0f));
	drawable->setStateSet(Util::getTexture2D(fileName));
	addDrawable(drawable);
}