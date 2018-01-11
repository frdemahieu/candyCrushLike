#include "AnimationRotationPath.h"


AnimationRotationPath::AnimationRotationPath(){
	rotation = 0;
	frame = 0;
}
void AnimationRotationPath::operator()(Node* node, NodeVisitor* nv){
	Modele *modele = Modele::getInstance();
	selection selec = modele->getSelection();
	if(selec.x != -1){
		
		PlateauJeu *jeu = PlateauJeu::getInstance();
		vector<vector<ref_ptr<MatrixTransform>>> *plateau = new vector<vector<ref_ptr<MatrixTransform>>>(modele->getNb_cote(), vector<ref_ptr<MatrixTransform>>(modele->getNb_cote()));
		plateau = jeu->getTabMatrix();
		ref_ptr<MatrixTransform> pieceATourner = (*plateau)[selec.x][selec.y];
		

		if((*modele->getTableau())[selec.x][selec.y] == BATEAU)
				pieceATourner->setMatrix(Matrix::rotate(rotation+=0.1,Z_AXIS));
		else if((*modele->getTableau())[selec.x][selec.y]  == ROND)
				pieceATourner->setMatrix(Matrix::rotate(rotation+=0.1,X_AXIS));
		else
			pieceATourner->setMatrix(Matrix::rotate(rotation+=0.1,1,1,0));
			pieceATourner->postMult(Matrix::translate(3.2+selec.x*COEFFICIENT,3.2+selec.y*COEFFICIENT,0));			
		
	}	
	
}


