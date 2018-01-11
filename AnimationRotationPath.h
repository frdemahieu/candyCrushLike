#pragma once
#include <iostream>
#include <osg/PositionAttitudeTransform>
#include "Modele.h"
#include "PlateauJeu.h"

#define DEBUT 0
#define FIN	1

using namespace osg;
using namespace std;

class AnimationRotationPath : public NodeCallback{


private:
	AnimationPath *path;
	Modele *modele;
	double rotation;
	int frame;
public:	
	AnimationRotationPath();
	virtual void operator()(Node* node, NodeVisitor* nv);



};