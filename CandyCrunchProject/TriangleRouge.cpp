#include "TriangleRouge.h"

TriangleRouge::TriangleRouge(){

	Geometry *geo = new Geometry;

	Vec3Array *tabSommet =  new Vec3Array;
	tabSommet->push_back(Vec3(-1,0,-1));
	tabSommet->push_back(Vec3(1,0,-1));
	tabSommet->push_back(Vec3(0,0,1));

	geo->setVertexArray(tabSommet);

	DrawElementsUInt *primitiveSet = new DrawElementsUInt(PrimitiveSet::TRIANGLES, 0);
	primitiveSet->push_back(0);
	primitiveSet->push_back(1);
	primitiveSet->push_back(2);

	geo->addPrimitiveSet(primitiveSet);

     Vec4Array* tabCouleur = new osg::Vec4Array; 
     tabCouleur->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f)); 
     geo->setColorArray(tabCouleur); 
	 geo->setColorBinding(osg::Geometry::BIND_OVERALL); 
	 addDrawable(geo);

}