/*
Fichier: Dvd.h
Auteur(s): Julien Gauthier, Catalin Giurca
Date de creation: 10 mars 2016
Date de modification: 29 mars 2016
Description: Initialisation des fonctions de la Classe Dvd
*/

#ifndef DVD_H
#define DVD_H
#include "ObjetEmpruntable.h"
#include <list>

//Dvd est derivee de la classe ObjetEmpruntable
class Dvd :
	public ObjetEmpruntable
{
public:
	Dvd();		//Constructeurs par defaut et par parametres
	Dvd(const std::string& cote, const std::string& titre, unsigned int annee,
		unsigned int ageMin, unsigned int nbExemplaires, std::string const& realisateur, std::list<std::string> acteurs);

	virtual ~Dvd();		//Destructeur virtuel, pour que Dvd ait son propre destructeur (en raison de la list en attribut)

	std::string obtenirRealisateur() const;				//Methodes d'acces aux attributs
	std::list<std::string> obtenirActeur() const;

	void modifierRealisateur(std::string const& realisateur);		//Methode de modification d'un realisateur
	void ajouterActeur(std::string const& acteur);				//Methodes d'ajout et de retrait d'un acteur 
	void retirerActeur(std::string const& acteur);				//dans la liste d'acteurs

	//recherche renvoie true si motsCle est present dans les attributs de type string; false sinon
	virtual bool recherche(const std::string& motsCle) const;
	//Operateur d'affichage, trie des acteurs en ordre alphab�tique inverse
	friend std::ostream& operator<<(std::ostream& o, Dvd& dvd);

private:
	std::string realisateur_;
	//On remplace le vecteur par une list listeActeurs_
	std::list<std::string> listeActeurs_;

};
#endif

