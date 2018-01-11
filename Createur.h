#pragma once 
#include<vector>

using namespace std;

typedef struct donneeModele{
	int score;
	int nbDeplacement;
	bool fin;
	bool msgErreur;
	vector<vector<int>> tableau;
}donneeModele;



class Createur{

private:

	donneeModele * etatModele;

public:

	class Memento{

	public: 
		donneeModele * etatMemento;

		Memento(donneeModele * newEtatModele);

		donneeModele * getEtatMemento();
	};


	Createur();

	Createur::Memento * sauverDansMemento();

	void restaurerDepuisMemento(Createur::Memento * newMemento);

	void setEtatModele(donneeModele * newEtatModele);

	donneeModele * getEtatModele();
	
	
};