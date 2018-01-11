#include "Gardien.h"
#include <iostream>
using namespace std;

Gardien::Gardien(){
	pileDeMemento = new stack<Createur::Memento *>();
}


void Gardien::ajouterMemento(Createur::Memento * memento){

	cout << "ajout" << endl;
	pileDeMemento->push(memento);
}

Createur::Memento * Gardien::getMemento(){
	if(pileDeMemento->size() >1){
		pileDeMemento->pop();
	}

	return pileDeMemento->top();
}

void Gardien::viderMemento(){
	pileDeMemento = new stack<Createur::Memento *>();
}


