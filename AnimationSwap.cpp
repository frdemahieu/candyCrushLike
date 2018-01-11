#include "AnimationSwap.h"

Animation::Animation(){
	
}
void Animation::animerForme(){
	
	HANDLE id = CreateThread(NULL,0,animer,0,0,NULL);
	WaitForSingleObject(id, INFINITE);
	CloseHandle(id);
	
}

DWORD WINAPI animer(void * data){
	Modele *modele = Modele::getInstance();
	vector<vector<ref_ptr<MatrixTransform>>> *plateauMat =  PlateauJeu::getInstance()->getTabMatrix();
	selection formeSelectionner = modele->getSelection();
	if(formeSelectionner.x != -1){
		
		// Permet de définir le "cheminement" de l'animation
		ref_ptr<AnimationPath> chemin = new AnimationPath;
		ref_ptr<MatrixTransform> mtDepart = (*plateauMat)[formeSelectionner.x][formeSelectionner.y];
		ref_ptr<MatrixTransform> mtArriver = (*plateauMat)[formeSelectionner.x2][formeSelectionner.y2];
		// Permet de gérer l'animation via un mécanisme de callback
		ref_ptr<AnimationPathCallback> animCall = new AnimationPathCallback(); 
		animCall->setAnimationPath(chemin);
			
		chemin->insert(START_TIME, AnimationPath::ControlPoint(mtDepart.get()->getMatrix().getTrans())); // Positionnement de départ
		chemin->insert(500000, AnimationPath::ControlPoint(mtArriver.get()->getMatrix().getTrans())); // Positionnement d'arrivée
		
		chemin->setLoopMode(AnimationPath::NO_LOOPING);
		
		mtDepart->removeUpdateCallback(animCall);		
		mtDepart->setUpdateCallback(animCall);

	}
	return 0;
}


Animation::~Animation(){

}

