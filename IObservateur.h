/*
class abstraite IObservateur.
Class utiliser pour le design pattern Observer.
Toutes les class qui doivent se mettre a jour quand le modele change doivent h�rit� de cette class.
*/
class IObservateur
{
public:

	/*
	M�thode abstraite qui sera impl�menter par les class h�ritant de IObservateur. 
	return : void
	*/
	virtual void notifier() = 0;
};