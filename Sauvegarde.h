#pragma once
#include <iostream>
#include<vector>
#include <fstream>
using namespace std;

class Sauvegarde{
	private:
		ofstream *fichierEcriture;
		ifstream *fichierLecture;
	public:
		Sauvegarde(string nomFichier);
		~Sauvegarde();
		ifstream *getFichierLecture();
		ofstream *getFichierEcriture();
	
};
