#include "CarreVert.h"


CarreVert::CarreVert(){
	drawable = new ShapeDrawable;
	drawable->setShape(new Box(Vec3(0,0,0),4,4,1));
	drawable->setColor(Vec4(0.026f,0.49f,0.18f,1.0f));
	drawable->setStateSet(Util::getTexture2D("luffy.png"));
	addDrawable(drawable);
}