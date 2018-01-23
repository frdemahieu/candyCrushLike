#include "EvenementUtilisateur.h"


// Les membres static non constants doient êtres initialisés dans le .cpp
EvenementUtilisateur *EvenementUtilisateur::instance = 0;

EvenementUtilisateur *EvenementUtilisateur::getInstance(){
	if (instance == 0)
		instance = new EvenementUtilisateur();

	return instance;
}


EvenementUtilisateur::EvenementUtilisateur(){
	controleur = Controleur::getInstance();
	modele = Modele::getInstance();	
	
}

void EvenementUtilisateur::operator()(Node* node, NodeVisitor* nv)
{

	std::list<ref_ptr<GUIEventAdapter>> events; 
	EventVisitor* ev = dynamic_cast<EventVisitor*>(nv); 
	if(ev) events = ev->getEvents(); 
	ref_ptr<GUIEventAdapter> ea = events.back(); 
	events.pop_back(); 
	switch(ea->getEventType())
	{

	case GUIEventAdapter::PUSH:
		{ // Pression sur la souris
			switch(ea->getButton())
			{
			case GUIEventAdapter::LEFT_MOUSE_BUTTON:
				{ 					
						selectionTouche(ea, node);
					break;
				}

			default:
				break;
			}
		}
		
	
	case GUIEventAdapter::KEYUP:
		{
			if(node->getName() == "CoteDroit"){
				if(modele->getEcritureEnCours()){
					
					switch(ea->getKey()){
					case GUIEventAdapter::KEY_Return:
						if(modele->getEcritureEnCours() == SAUVER){
							controleur->sauvegarderJeu(modele->getFichierSauvegarde());
							modele->setFichierSauvegarde("");
							modele->setEcritureEnCours(0);
						}
						if(modele->getEcritureEnCours() == CHARGER) {
							controleur->chargerJeu(modele->getFichierSauvegarde());
							modele->setFichierSauvegarde("");
							modele->setEcritureEnCours(0);
						}
					break;

					case GUIEventAdapter::KEY_BackSpace:
						modele->setFichierSauvegarde(modele->getFichierSauvegarde().substr(0,modele->getFichierSauvegarde().size()-1));
					break;

					default:
						if(ea->getKey() > 0 && ea->getKey() < 256)
							modele->setFichierSauvegarde(modele->getFichierSauvegarde() + string(1,ea->getKey()) );
					break;

					}
					
				}
				else{
					switch(ea->getKey())
					{
					case GUIEventAdapter::KEY_Up:
						{ 
							modele->deplacerHaut();
							break;
						}
					case GUIEventAdapter::KEY_Down:
						{ 
							modele->deplacerBas();
							break;
						}

					case GUIEventAdapter::KEY_Right:
						{ 
							modele->deplacerDroite();
							break;
						}
					case GUIEventAdapter::KEY_Left:
						{ 
							modele->deplacerGauche();
							break;
						}

					case GUIEventAdapter::KEY_H:
						{	
							if(modele->getNbFormeSelectionner() != 2){
								selection coord = modele->trouverCombinaison();
								modele->setSelectionStruct(coord);	
								}
							break;
						}

					case GUIEventAdapter::KEY_S:
						{ 
							modele->setEcritureEnCours(SAUVER);
							break;
						}
			
					case GUIEventAdapter::KEY_C:
						{ 
							modele->setEcritureEnCours(CHARGER);
							break;
						}
					case GUIEventAdapter::KEY_R:
						{ 
							modele->redemarrer();
							break;
						}
					case GUIEventAdapter::KEY_Space:
						{ 
							modele->toucheEnter();
							break;
						}
					default:
						break;
					}	
				}
			}
		}
		
	default:
		break;

	}

	traverse(node,nv);
}

void EvenementUtilisateur::selectionTouche(ref_ptr<GUIEventAdapter> ea, Node* node){


	// Intersecteur à partir du point de l'écran (en pixels) au moment du click
	ref_ptr<LineSegmentIntersector> intersector = 
		new LineSegmentIntersector(Intersector::WINDOW,ea->getX(),ea->getY());


	// Visite des noeuds spécifiés pour déterminer si des Drawables entrent en intersection
	// avec la "ligne de mire" du click de la souris
	IntersectionVisitor iv(intersector);
	// chaque noeud visité sera traité pour la sélection via un click de la souris
	node->accept(iv);

	// si au moins un Drawable est sélectionné

	if(intersector->containsIntersections()){
		// on récupère le plus proche (?) et ses coordonnées dans l'univers de dessin
		LineSegmentIntersector::Intersection result = intersector->getFirstIntersection();
		float x = result.getWorldIntersectPoint().x();
		float y = result.getWorldIntersectPoint().y();


		if(node->getName() == "CoteDroit"){
			if(y > 3.5 && y < 4.44){
				//si on a déjà trouvé une combinaison on lui redonne la même réponse.
				if(modele->getNbFormeSelectionner() != 2){
					selection coord = modele->trouverCombinaison();
					modele->setSelectionStruct(coord);	
				}
				

			}
			else if(y > 5.5 && y < 6.44){
				if(modele->getEcritureEnCours() == CHARGER)
					modele->setEcritureEnCours(0);
				else
					modele->setEcritureEnCours(CHARGER);
				
			}
			else if(y > 7.5 && y < 8.44){
				if(modele->getEcritureEnCours() == SAUVER)
					modele->setEcritureEnCours(0);
				else
					modele->setEcritureEnCours(SAUVER);
			
			}
			else if(y > 9.5 && y < 10.44){
				modele->redemarrer();
			}
		}
		else{

			if(!modele->getJeuFinis()){
				int indiceX = x /6.4;
				int indiceY = y /6.4;

				selection select  = modele->getSelection();

				if(modele->getNbFormeSelectionner() == 2){
					modele->permuterForme();
					modele->executerSelection(indiceX,indiceY);
					modele->reinitialiserSelection();
				}
				else{
					modele->executerSelection(indiceX,indiceY);
				}
			}
		}
	}

}

 