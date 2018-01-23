#include "TriangleBleu.h"


TriangleBleu::TriangleBleu (){
	drawable = new ShapeDrawable;
	drawable->setShape(new Cone(Vec3(0,0,0),2,4));
	drawable->setColor(Vec4(0.015f,0.38f,.50f,1.0f));
	drawable->setStateSet(Util::getTexture2D("loupe.png"));
	addDrawable(drawable);
}
