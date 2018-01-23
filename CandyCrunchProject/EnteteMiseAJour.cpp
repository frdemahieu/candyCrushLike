#include "EnteteMiseAJour.h"
#include "Entete.h"

void EnteteMiseAJour::operator()(Node* node, NodeVisitor* nv)
{
	Modele* modele = Modele::getInstance(); // Récupère le modèle
	Entete * entete = Entete::getInstance();
	int s = modele->getScore();
	modele->setScore(s+1);
	MatrixTransform* mt = static_cast<MatrixTransform*>(node); // Particularise le Node à traiter
	_count++;
	entete->setScore(s);
	
	
	traverse(node,nv); // Obligatoire si le "visiteur" doit continuer son parcours
}