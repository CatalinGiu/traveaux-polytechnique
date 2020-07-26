/*
Fichier: Livre.h
Auteur(s): Julien Gauthier, Catalin Giurca
Date de creation: 10 mars 2016
Date de modification: 29 mars 2016
Description: Initialisation des fonctions de la Classe Livre
*/

#ifndef LIVRE_H
#define LIVRE_H
#include "ObjetEmpruntable.h"

//La classe Livre demeure inchangee du TP4, aucun commentaire supplementaire
//n'est donc ajoute.

//Livre est une classe derivee de la classe ObjetEmpruntable
class Livre :
	public ObjetEmpruntable
{
public:
	Livre();
	Livre(const std::string& cote, const std::string& titre, unsigned int annee,
		unsigned int ageMin, unsigned int nbExemplaires, const std::string& auteur, const std::string& genre);
	virtual ~Livre();

	std::string obtenirAuteur() const;
	std::string obtenirGenre() const;

	void modifierAuteur(std::string const& auteur);
	void modifierGenre(std::string const& genre);

	//recherche renvoie true si motsCle est présent dans les attributs de type string; false sinon
	virtual bool recherche(const std::string& motsCle) const;

	friend std::ostream& operator<<(std::ostream& o, const Livre& livre);

protected :
	std::string auteur_;
	std::string genre_;
};

#endif