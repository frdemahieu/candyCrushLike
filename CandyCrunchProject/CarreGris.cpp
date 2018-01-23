#include "CarreGris.h"


CarreGris::CarreGris(){
	drawable = new ShapeDrawable;
	drawable->setShape(new Box(Vec3(0,0,0),4,4,1));
	drawable->setColor(Vec4(.5f,.5f,.5f,1.0f));
	
	drawable->setStateSet(Util::getTexture2D("zorro.png"));

	addDrawable(drawable);
}