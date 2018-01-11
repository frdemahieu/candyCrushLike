#pragma once
#include <string>
#include<vector>
#include <iostream>
#include <time.h>
#include <algorithm>
#include <fstream>
#include <stack> 
#include "Observable.h"
#include "EventValeur.h"
#include "Gardien.h"

using namespace std;

#define NB_DEPLACEMENT 20
#define VIDE -1

#define HORIZONTALE 0
#define VERTICALE 1

#define FRUSTRUM 1.24
#define ORTHO 6.4

#define COEFFICIENT 6.4
/*Structure utiliser pour retenir les coordonn�es des formes(friandises) selectionn�es.
si aucune forme n'est selectionn�e les coordonn�es dans la structure selection seront �gale � -1
*/
typedef struct selection{
	int x;
	int y;
	int x2;
	int y2;
}selection;

/*
Structure utilis� pour retenir les coordonn�es, l'alignement horizontal ou vertical 
et le nombre de formes successive.
*/
typedef struct coordonnee{
	int x;
	int y;
	int alignement;
	int nbCombinaison;
}coordonnee;




/*
Class Modele h�rite de Observable.
Class qui retient les donn�es, l'�tat du jeu.
*/
class Modele: public Observable
{

private:

	/*instance du model singleton*/
	static Modele *instance; 

	/* int, nb de deplacement d�finit dans le fichier config*/
	int nbDeplacementFichier;

	/*int, score de l'utilisateur*/
	int score;

	/* int, nb de deplacement que l'utilisteur peut encore �ffectuer*/
	int nbDeplacementRestant;

	/* int, nombre de colonne et de ligne pour le plateau de jeu*/
	int nb_cote;

	/*vector<vector<int>> * , Structure de donn�e qui contient des entiers. Chaque entier repr�sente une forme*/
	vector<vector<int>> *tableau;

	/*bool, si la variable est � true un message d'erreur s'affichera dans l'entete */
	bool afficherMsgErreur;

	/*bool, si la variable est � true le plateau est � jour */
	bool plateauAJour;

	/*bool, si la variable est � true le plateau le jeu est finis */
	bool jeuFinis;

	/*bool, si la variable est � true c'est qu'une forme a �t� s�l�ctionn�e */
	bool formeSelectionner;

	/*int, retient le nombre de formes s�l�ctionn�e */
	int nbFormeSelectionner;

	/*selection, structure selection qui contient les coordonn�es des formes s�lectionn�es */
	selection objetSelectione;

	/*int, score maximum*/
	int scoreMax;

	/*string, nom du fichier de sauvegarde */
	string fichierSauvegarde;

	/*int, si 1 = SAUVER, 2 = CHARGER, 0 = RIEN*/
	int ecritureEnCours;

	//coefficient en fonction du frustrum ou ortho
	double coefficient;

	//taille du zoom
	int zoom;


	bool boutonAJour;

	bool boutonAllumer;

	bool fichierCharger;

	int indiceBoutonAllumer;

	int indiceBoutonEteind;

	

	Gardien * gardien;

	Createur * createur;

	/*Constructeur de la class Modele*/
	Modele();

public:

	/*Instance du Modele pour le pattern singleton*/
	static Modele *getInstance();

	/*
	renvoie le champ fichierSauvegarde
	return : string
	*/
	string getFichierSauvegarde();

	/*
	change la valeur du champ fichierSauvegarde
	param : string fichier => nom donn� au fichier pour la sauvegarde
	return : void.
	*/
	void setFichierSauvegarde(string fichier);

	/*
	renvoie le champ ecritureEnCours
	return : int
	*/
	int getEcritureEnCours();


	/*
	change la valeur du champ ecritureEnCours
	param : int etat => 1 = SAUVER, 2 = CHARGER, 0 = RIEN
	return : void.
	*/
	void setEcritureEnCours(int etat);


	void setFichierCharger(bool change);

	bool getFichierCharger();

	/*
	renvoie le champ score
	return : int
	*/
	int getScore();

	/*
	renvoie le champ scoreMax
	return : int
	*/
	int getScoreMax();


	/*
	change la valeur du champ score
	param : int newScore => valeur du nouveau score
	return : void.
	*/
	void setScore(int newScore);

	/*
	renvoie le champ nbDeplacementRestant
	return : int
	*/
	int getNbDeplacementRestant();

	/*
	change la valeur du champ nbDeplacementRestant
	param : int newNbDeplacementRestant => valeur du nouveau champ nbDeplacementRestant
	return : void.
	*/
	void setNbDeplacementRestant(int newNbDeplacementRestant);

	/*
	renvoie le champ tableau
	return : vector<vector<int>> *
	*/
	vector<vector<int>> *getTableau();

	/*
	renvoie le champ nb_cote
	return : int
	*/
	int getNb_cote();

	/*
	change la valeur du champ nb_cote
	param : int newNb_cote => valeur du nouveau champ nb_cote
	return : void.
	*/
	void setNb_cote(int newNb_cote);

	/*
	change la valeur du champ afficherMsgErreur
	param : bool newValeur => valeur du nouveau champ afficherMsgErreur
	return : void.
	*/
	void setAfficherMsgErreur(bool newValeur);

	/*
	renvoie le champ afficherMsgErreur
	return : bool
	*/
	bool getAfficherMsgErreur();

	/*
	change la valeur du champ plateauAJour
	param : bool newValeur => valeur du nouveau champ plateauAJour
	return : void.
	*/
	void setPlateauAJour(bool newValeur);

	/*
	renvoie le champ plateauAJour
	return : bool
	*/
	bool getPlateauAJour();

	/*
	change la valeur du champ jeuFinis
	param : bool newValeur => valeur du nouveau champ jeuFinis
	return : void.
	*/
	void setJeuFinis(bool newValeur);

	/*
	renvoie le champ jeuFinis
	return : bool
	*/
	bool getJeuFinis();

	/*
	renvoie le champ objetSelectione
	return : selection
	*/
	selection getSelection();

	/*
	change la valeur des coordonn�es de x et y ou de x2 et y2 du champ objetSelectione.
	param : int x  => valeur de la coordonn�e x
	int y  => valeur de la coordonn�e y
	return : void.
	*/
	void setSelection(int x, int y);

	/*
	Initialise le champs tableau en placant des entiers de 0 � 3 de mani�re al�atoires dans chacune de ses cases.
	return void
	*/
	void initialiserTableau();

	/*
	parcour le tableau de maniere horizontal et vertical. Si il trouve plus de 2 formes succesives (combinaison),
	on les met dans une structure coordonnee et on le rajoute dans le vector � renvoyer.
	return : vector<coordonnee>
	*/
	vector<coordonnee> * existeCombinaison();

	/*
	On parcour le vector de coordonnee en remplacant les combinaisons par -1, 
	on renvoie le score qui est le nombre de forme remplac�.
	parametre: vector<coordonnee> * vecteurCoords => vecteur contenant des structures coordonnee qui nous permettront
	de retrouver les combinaisons.
	return : int
	*/
	int supprimerCombinaison(vector<coordonnee> * vecteurCoords);

	/*
	Parcours le tableau en supprimant les -1 et en rajoutant les nouvelles formes al�atoires.
	return void
	*/
	void remplacerCombinaison();

	/*
	verifier que les coordonn�es sont adjacente
	return : bool
	*/
	bool formeAdjacente(int x1,int y1,int x2, int y2);

	/*
	Permute x avec x2 et y avec y2 dans la structure objetSelectione
	return:  void
	*/
	void permuterForme();

	/*
	Parcour le tableau et cherche si en permutant 2 formes une combinaison est possible. 
	Si Aucune combinaison est possible, on met dans la structure a renvoyer x � -1.
	return: selection
	*/
	selection trouverCombinaison();


	/*
	D�place les coordonn�es de la structure objetSelectione vers la droite
	return:  void
	*/
	void deplacerDroite();

	/*
	D�place les coordonn�es de la structure objetSelectione vers la gauche
	return:  void
	*/
	void deplacerGauche();

	/*
	D�place les coordonn�es de la structure objetSelectione vers le haut
	return:  void
	*/
	void deplacerHaut();

	/*
	D�place les coordonn�es de la structure objetSelectione vers le bas
	return:  void
	*/
	void deplacerBas();


	void deplacerSelection(int direction);


	/*
	Execute la methode executerSelection(int x, int y) avec comme parametre les champs de la structure objetSelectione
	return:  void
	*/
	void toucheEnter();

	/*
	V�rifie si une forme est deja selectionner,
	si aucune forme est selectionner le x ou x2 et y ou y2 de de la structure objetSelectione sont a 0.
	return: bool
	*/
	bool estSelectionner();

	/*
	renvoie le champ nbFormeSelectionner
	return : int
	*/
	int getNbFormeSelectionner();

	/*
	Remet les champs � certaines valeurs pour que plus aucune formes ne sois selectionner.
	return : void
	*/
	void reinitialiserSelection();

	/*
	Algorithme du jeu, Si deux formes sont selectionn�, on va lancer toutes les operations pour v�rifier et supprimer les combinaisons.
	Verifie si le jeu est termin�.
	return : void
	*/
	void executerSelection(int x, int y);

	/*
	R�initialise tout les champs
	return : void
	*/
	void redemarrer();

	/*
	change la valeur des coordonn�es de x et y ou de x2 et y2 du champ objetSelectione.
	param : selection select => change les valeurs de la structure objetSelectione par celle-ci.
	return : void.
	*/
	void setSelectionStruct(selection select);

	//change le coefficient soit frustrum soit ortho
	void changeCoeffficient();

	double getCoefficient();

	bool isFrustrum();

	int getZoom();

	void zoomer();

	void deZoomer();

	bool getBoutonAJour();

	int getIndiceBoutonEteind();

	int getIndiceBoutonAllumer();

	void changerAspectBouton(int indiceBouton);


	void sauverEtatModele();

	void restaurerEtatModele();

	void viderEtatModele();

	vector<vector<int>> * copieVector(vector<vector<int>> * vectorCpy);

	/* Destructeur de la class Modele*/
	~Modele();

};

/*redirection de flux */
istream& operator>>(istream& os,Modele *modele);

/*redirection de flux*/
ostream& operator<<(ostream& os,Modele *modele);


