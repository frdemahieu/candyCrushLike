/*
class abstraite IObservateur.
Class utiliser pour le design pattern Observer.
Toutes les class qui doivent se mettre a jour quand le modele change doivent hérité de cette class.
*/
class IObservateur
{
public:

	/*
	Méthode abstraite qui sera implémenter par les class héritant de IObservateur. 
	return : void
	*/
	virtual void notifier() = 0;
};