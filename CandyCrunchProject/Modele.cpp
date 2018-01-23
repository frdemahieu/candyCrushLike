#include "Modele.h"


// Les membres static non constants doient êtres initialisés dans le .cpp
Modele *Modele::instance = 0;


Modele::Modele(){
	ifstream fichier("config");
	score = 0;
	fichier >> nbDeplacementFichier;
	fichier >> nb_cote;
	fichier >> scoreMax;

	nbDeplacementRestant = nbDeplacementFichier;
	tableau = new vector<vector<int>>(nb_cote, vector<int>(nb_cote));
	afficherMsgErreur = false;
	plateauAJour = true;
	jeuFinis = false;
	formeSelectionner = false;
	ecritureEnCours = 0;

	objetSelectione.x = VIDE;
	objetSelectione.x2 = VIDE;
	objetSelectione.y = VIDE;
	objetSelectione.y2  = VIDE;
	nbFormeSelectionner = 0;
}

Modele *Modele::getInstance(){
	if (instance == 0)
		instance = new Modele();

	return instance;
}

int Modele::getScore(){
	return score;
}

int Modele::getScoreMax(){
	return scoreMax;
}


void Modele::setScore(int newScore){
	score = newScore;
}

int Modele::getNbDeplacementRestant(){
	return nbDeplacementRestant;
}

void Modele::setNbDeplacementRestant(int newNbDeplacementRestant){
	nbDeplacementRestant = newNbDeplacementRestant;
}

vector<vector<int>> *Modele::getTableau(){
	return tableau;
}


int Modele::getNb_cote(){
	return nb_cote;
}

void Modele::setNb_cote(int newNb_cote){
	nb_cote = newNb_cote;
	tableau = new vector<vector<int>>(newNb_cote, vector<int>(newNb_cote));
}

void Modele::setAfficherMsgErreur(bool newValeur){
	afficherMsgErreur = newValeur;
	notifierObservateurs();
}

bool Modele::getAfficherMsgErreur(){
	return afficherMsgErreur;
}

void Modele::setPlateauAJour(bool newValeur){
	reinitialiserSelection();
	plateauAJour = newValeur;
	if(plateauAJour == false){
		notifierObservateurs();
		plateauAJour = true;
	}
}
void Modele::setSelectionStruct(selection select){
	objetSelectione.x = select.x;
	objetSelectione.x2 = select.x2;
	objetSelectione.y = select.y;
	objetSelectione.y2 = select.y2;
	formeSelectionner = true;
	nbFormeSelectionner = 2;
	notifierObservateurs();
}
bool Modele::getPlateauAJour(){
	return plateauAJour;
}
selection Modele::getSelection(){
	return objetSelectione;
}

void Modele::setJeuFinis(bool newValeur){
	jeuFinis = newValeur;
	notifierObservateurs();
}

bool Modele::getJeuFinis(){
	return jeuFinis;
}

string Modele::getFichierSauvegarde(){
	return fichierSauvegarde;
}

void Modele::setFichierSauvegarde(string fichier){
	fichierSauvegarde=fichier;
	notifierObservateurs();

}
int Modele::getEcritureEnCours(){
	return ecritureEnCours;
}
void Modele::setEcritureEnCours(int etat){
	ecritureEnCours = etat;
	notifierObservateurs();
}

ostream& operator<<(ostream& os,Modele *modele){
	os << modele->getNb_cote() << endl;
	os << modele->getScore() << endl;
	os << modele->getNbDeplacementRestant() << endl;

	for(int i = 0; i < modele->getNb_cote();i++){
		for(int j = 0; j < modele->getNb_cote();j++){
			os << (*modele->getTableau())[j][i] << endl;
		}
	}
	return os;
}

istream& operator>>(istream& os,Modele *modele){
	int val;
	os >> val;
	modele->setNb_cote(val);
	os >> val;
	modele->setScore(val);
	os >> val;
	modele->setNbDeplacementRestant(val);

	vector<vector<int>> *tableau = new vector<vector<int>>(val, vector<int>(val));
	

	for(int i = 0; i < modele->getNb_cote();i++){
		for(int j = 0; j < modele->getNb_cote();j++){
			os >> (*modele->getTableau())[j][i];
		}
	}
	
	
	return os;
}




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
			
			cout << "plus de possibilité";
			
			jeuFinis = true;
			selection ret;
			ret.x = -1;
			return ret;
			
}

void Modele::deplacerDroite(){

	if(estSelectionner()){
		if(!formeSelectionner){
			objetSelectione.x += 1;
			if(objetSelectione.x >= nb_cote)
				objetSelectione.x = 0;
		}else{
			objetSelectione.x2+= 1;
			if(objetSelectione.x2 >= nb_cote)
				objetSelectione.x2 = 0;
		}
	}
	notifierObservateurs();
}

void Modele::deplacerGauche(){

	if(estSelectionner()){
		if(!formeSelectionner){
			objetSelectione.x -= 1;
			if(objetSelectione.x < 0)
				objetSelectione.x = nb_cote-1;
		}else{
			objetSelectione.x2 -= 1;
			if(objetSelectione.x2 < 0)
				objetSelectione.x2 = nb_cote-1;
		}
	}
	notifierObservateurs();
}

void Modele::deplacerHaut(){

	if(estSelectionner()){
		if(!formeSelectionner){
			objetSelectione.y += 1;
			if(objetSelectione.y >= nb_cote)
				objetSelectione.y = 0;
		}else{
			objetSelectione.y2 += 1;
			if(objetSelectione.y2 >= nb_cote)
				objetSelectione.y2 = 0;
		}
	}
	notifierObservateurs();
}

void Modele::deplacerBas(){

	if(estSelectionner()){
		if(!formeSelectionner){
			objetSelectione.y -= 1;
			if(objetSelectione.y < 0)
				objetSelectione.y = nb_cote -1;
		}else{
			objetSelectione.y2 -= 1;
			if(objetSelectione.y2 < 0)
				objetSelectione.y2 = nb_cote -1;
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
	notifierObservateurs();
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

		
		if(score >= scoreMax || nbDeplacementRestant == 0){
			setJeuFinis(true);
		}
	}	
}

Modele::~Modele(){
	free(tableau);
}