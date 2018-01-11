#pragma once
#include <stack>
#include "Createur.h"


class Gardien{

private:
	
	stack<Createur::Memento *> * pileDeMemento;


public:
	
	Gardien();

	void ajouterMemento(Createur::Memento * memento);

	Createur::Memento * getMemento();

	void viderMemento();
	
};