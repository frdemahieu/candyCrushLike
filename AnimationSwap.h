#pragma once
#include <Windows.h>
#include <vector>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>
#include <osg/AnimationPath>
#include "Modele.h"
#include "PlateauJeu.h"



using namespace osg;
using namespace std;

#define START_TIME 0
#define STOP_TIME 1

class Animation{

public:

	Animation();
	void animerForme();


	~Animation();
};

DWORD WINAPI animer(void * data);