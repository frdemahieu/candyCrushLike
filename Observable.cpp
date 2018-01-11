#include "Observable.h"

Observable::Observable(){
}

void Observable::notifierObservateurs() const
{
	list<IObservateur*>::const_iterator end = list_observateurs.end();
	for (list<IObservateur*>::const_iterator it = list_observateurs.begin(); it != end; it++)
			(*it)->notifier();
		
}

void Observable::ajouterObservateur(IObservateur* observateur)
{
	list_observateurs.push_front(observateur);
}

void Observable::supprimerObservateur(IObservateur* observateur)
{
	list_observateurs.remove(observateur);
}
