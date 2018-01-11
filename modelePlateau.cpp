#include "Modele.h"
#include "AnimationSwap.h"

void Modele::initialiserTableau(){


	srand(time(NULL));
	for(int i=0;i<getNb_cote();i++){
		for(int j=0;j<getNb_cote();j++){
			(*tableau)[i][j] = rand() % 4;
		}
	}


	while(true){
		vector<coordonnee> * v = existeCombinaison();
		if(v->size() == 0)
			break;
		supprimerCombinaison(v);
		remplacerCombinaison();
	}


}

vector<coordonnee> * Modele::existeCombinaison(){

	int cpt = 0;
	int precedent = -1;
	int x = 0;
	int y = 0;
	coordonnee *coord = new coordonnee();
	coord->alignement = HORIZONTALE;

	vector<coordonnee> * vecteurCoords = new vector<coordonnee>;

	for(int i=0;i<getNb_cote();i++){
		x = i;

		for(int j=0;j<getNb_cote();j++){


			if((*tableau)[i][j] == precedent){
				cpt++;

			}else{
				if(cpt >= 2){
					coord->x = x;
					coord->y = y;
					coord->nbCombinaison = cpt;
					vecteurCoords->push_back(*coord);
				}
				precedent = (*tableau)[i][j];
				cpt = 0;
				y = j;
			}
		}
		if(cpt >= 2){
			coord->x = x;
			coord->y = y;
			coord->nbCombinaison = cpt;
			vecteurCoords->push_back(*coord);
		}
		y = 0;
		cpt = 0;
		precedent = -1;
	}

	coord->alignement = VERTICALE;
	for(int i=0;i<getNb_cote();i++){
		x = i;
		for(int j=0;j<getNb_cote();j++){

			if((*tableau)[j][i] == precedent){
				cpt++;

			}else{
				if(cpt >= 2){
					coord->x = x;
					coord->y = y;
					coord->nbCombinaison = cpt;
					vecteurCoords->push_back(*coord);
				}
				precedent = (*tableau)[j][i];
				cpt = 0;
				y = j;
			}

		}
		if(cpt >= 2){
			coord->x = x;
			coord->y = y;
			coord->nbCombinaison = cpt;
			vecteurCoords->push_back(*coord);
		}
		cpt = 0;
		precedent = -1;
		y = 0;
	}

	return vecteurCoords;
}

int Modele::supprimerCombinaison(vector<coordonnee> * vecteurCoords){

	coordonnee coord;
	int taille = vecteurCoords->size();
	int tempScore = 0;

	for(int i = 0; i < taille; i++){
		coord = (*vecteurCoords)[i];

		for(int j = 0 ; j <= coord.nbCombinaison;j++){
			tempScore += (coord.nbCombinaison+1);
			if(coord.alignement == HORIZONTALE)
				(*tableau)[coord.x][coord.y +j] = -1;
			else
				(*tableau)[coord.y+j][coord.x ] = -1;

		}
	}
	return tempScore;
}

void Modele::remplacerCombinaison(){
	srand(time(NULL));
	
	for(int i=0;i<getNb_cote();i++){
		for(int j=0;j<getNb_cote();j++){
			if((*tableau)[i][j] == -1){
				(*tableau)[i].erase((*tableau)[i].begin() + j);
				(*tableau)[i].push_back(rand() % 4);
				j--;
			}
		}
	}

}

bool Modele::formeAdjacente(int x1,int y1,int x2, int y2){

	int difference = y1 - y2;
	if( x1 == x2 && difference <=1 && difference >= -1){
		return true;
	}

	difference = x1 - x2;
	if( y1 == y2 && difference <=1 && difference >= -1){
		return true;
	}
	return false;
}

void Modele::permuterForme(){
	
	Animation *animSwap  = new Animation();
	animSwap->animerForme();
	int tmp = (*tableau)[objetSelectione.x][objetSelectione.y];
	(*tableau)[objetSelectione.x][objetSelectione.y] = (*tableau)[objetSelectione.x2][objetSelectione.y2];
	(*tableau)[objetSelectione.x2][objetSelectione.y2] = tmp;
}


//Aide l'utilisateur à trouver une combinaison valide.
selection Modele::trouverCombinaison(){
	int nbrCote = getNb_cote();
	selection retour;
	cout << "trouverCombinaison" << endl;
	for(int i = 0; i < nbrCote; i++){
		for(int j = 0; j < nbrCote;j++){

			int x = i;
			int y = j;
			retour.x = x;
			retour.y = y;
			vector<coordonnee> * v;

			int forme = (*tableau)[x][y];
			int formeTemp;

			if(y < nbrCote-1){
				formeTemp = (*tableau)[x][y+1];

				(*tableau)[x][y+1] = forme;
				(*tableau)[x][y] = formeTemp;
				v = existeCombinaison();
				if(v->size() != 0 ){
					retour.x2 = x;
					retour.y2 = y+1;
					return retour;
				}
				else{
					(*tableau)[x][y+1] = formeTemp;
					(*tableau)[x][y] = forme;
				}
			}
			if( y > 0){
				formeTemp = (*tableau)[x][y-1];
				(*tableau)[x][y-1] = forme;
				(*tableau)[x][y] = formeTemp;
				v = existeCombinaison();
				if(v->size() != 0){
					retour.x2 = x;
					retour.y2 = y-1;
					return retour;
				}
				else{
					(*tableau)[x][y-1] = formeTemp;
					(*tableau)[x][y] = forme;
				}
			}
			if( x > 0){
				formeTemp = (*tableau)[x-1][y];
				(*tableau)[x-1][y] = forme;
				(*tableau)[x][y] = formeTemp;
				v = existeCombinaison();
				if(v->size() != 0){
					retour.x2 = x-1;
					retour.y2 = y;
					return retour;
				}
				else{
					(*tableau)[x-1][y] = formeTemp;
					(*tableau)[x][y] = forme;
				}
			}
			if( x < nbrCote -1){
				formeTemp = (*tableau)[x+1][y];
				(*tableau)[x+1][y] = forme;
				(*tableau)[x][y] = formeTemp;
				v = existeCombinaison();
				if(v->size() != 0){
					retour.x2 = x+1;
					retour.y2 = y;
					return retour;
				}
				else{
					(*tableau)[x+1][y] = formeTemp;
					(*tableau)[x][y] = forme;
				}
			}

		}
	}

	jeuFinis = true;
	selection ret;
	ret.x = -1;
	return ret;

}


void Modele::deplacerSelection(int direction){

	if(estSelectionner()){
		if(!formeSelectionner){
			switch(direction){
			case EV::EventValeur::DROITE :{
				objetSelectione.x += 1;
				if(objetSelectione.x >= nb_cote)
					objetSelectione.x = 0;
				break;
										  }
			case EV::EventValeur::GAUCHE:{
				objetSelectione.x -= 1;
				if(objetSelectione.x < 0)
					objetSelectione.x = nb_cote-1;
				break;
										 }
			case EV::EventValeur::HAUT:{
				objetSelectione.y += 1;
				if(objetSelectione.y >= nb_cote)
					objetSelectione.y = 0;
				break;
									   }
			case EV::EventValeur::BAS:{
				objetSelectione.y -= 1;
				if(objetSelectione.y < 0)
					objetSelectione.y = nb_cote -1;
				break;
									  }

			}
		}else{

			switch(direction){
			case EV::EventValeur::DROITE:{
				objetSelectione.x2+= 1;
				if(objetSelectione.x2 >= nb_cote)
					objetSelectione.x2 = 0;
				break;
										 }
			case EV::EventValeur::GAUCHE:{
				objetSelectione.x2 -= 1;
				if(objetSelectione.x2 < 0)
					objetSelectione.x2 = nb_cote-1;
				break;
										 }
			case EV::EventValeur::HAUT:{
				objetSelectione.y2 += 1;
				if(objetSelectione.y2 >= nb_cote)
					objetSelectione.y2 = 0;
				break;
									   }
			case EV::EventValeur::BAS:{
				objetSelectione.y2 -= 1;
				if(objetSelectione.y2 < 0)
					objetSelectione.y2 = nb_cote -1;
				break;
									  }

			}
		}

	}
	notifierObservateurs();
}

void Modele::toucheEnter(){

	if(formeSelectionner){
		executerSelection(objetSelectione.x2,objetSelectione.y2);

	}else{
		executerSelection(objetSelectione.x,objetSelectione.y);
	}

}
void Modele::redemarrer(){
	reinitialiserSelection();
	setScore(0);
	initialiserTableau();
	nbDeplacementRestant = nbDeplacementFichier;
	plateauAJour = false;
	jeuFinis = false;
	afficherMsgErreur = false;
	viderEtatModele();
	//notifierObservateurs();
}

bool Modele::estSelectionner(){

	if(!formeSelectionner){
		if(objetSelectione.x == VIDE && objetSelectione.y == VIDE){
			objetSelectione.x = 0;
			objetSelectione.y = 0;
			return false;
		}
	}else{

		if(objetSelectione.x2 == VIDE && objetSelectione.y2 == VIDE){
			objetSelectione.x2 = 0;
			objetSelectione.y2 = 0;
			return false;
		}
	}
	return true;
}


void Modele::setSelection(int x, int y){

	afficherMsgErreur = false;

	if(formeSelectionner){
		if(objetSelectione.x == x && objetSelectione.y == y ){
			reinitialiserSelection();
		}
		else if(!formeAdjacente(objetSelectione.x,objetSelectione.y,x,y)){
			afficherMsgErreur = true;
			reinitialiserSelection();
		}
		else{
			objetSelectione.x2 = x;
			objetSelectione.y2 = y;
			nbFormeSelectionner = 2;
		}
	}else{
		objetSelectione.x = x;
		objetSelectione.y = y;
		formeSelectionner = true;
		nbFormeSelectionner = 1;
	}

	notifierObservateurs();

}

int Modele::getNbFormeSelectionner(){
	return nbFormeSelectionner;
}

void Modele::reinitialiserSelection(){
	objetSelectione.x = VIDE;
	objetSelectione.x2 = VIDE;
	objetSelectione.y = VIDE;
	objetSelectione.y2  = VIDE;
	formeSelectionner = false;
	nbFormeSelectionner = 0;
}

void Modele::executerSelection(int x, int y){

	int temp = 0;
	if(x != VIDE && y != VIDE)
		setSelection(x,y);

	if(nbFormeSelectionner == 2){

		permuterForme();
		vector<coordonnee> * v = existeCombinaison();
		if(v->size() == 0){
			permuterForme();
			reinitialiserSelection();
			notifierObservateurs();
		}
		else{
			temp = supprimerCombinaison(v);
			while(v->size() != 0){
				supprimerCombinaison(v);
				remplacerCombinaison();
				v = existeCombinaison();
			}

			nbDeplacementRestant -= 1;
			score += temp;
			setPlateauAJour(false);


		}

		sauverEtatModele();
		if(score >= scoreMax || nbDeplacementRestant == 0){
			setJeuFinis(true);
		}
	}	
}

void Modele::changeCoeffficient(){
	if(coefficient == FRUSTRUM)
		coefficient = ORTHO;
	else
		coefficient = FRUSTRUM;
}

double Modele::getCoefficient(){
	return coefficient;
}

bool Modele::isFrustrum(){
	if(getCoefficient() == FRUSTRUM)
		return true;
	else
		return false;
}
int Modele::getZoom(){
	return zoom;
}

void Modele::zoomer(){
	if(!isFrustrum() && zoom > -25){
		zoom-=2;
		plateauAJour = false;
		notifierObservateurs();
	}
	else if(isFrustrum() && zoom > -90){
		zoom-=2;
		plateauAJour = false;
		notifierObservateurs();
	}
}

void Modele::deZoomer(){
	if(zoom < 50){
		zoom+=2;
		plateauAJour = false;
		notifierObservateurs();
	}
}