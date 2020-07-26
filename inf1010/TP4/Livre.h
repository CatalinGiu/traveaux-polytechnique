/*
Fichier: Livre.h
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 25 fevrier 2016
Date de modification: 28 fevrier 2016
Description: Initialisation des fonctions de la Classe Livre
*/
#ifndef LIVRE_H
#define LIVRE_H
#include "ObjetEmpruntable.h"


class Livre :					//Livre est une classe derivee de ObjetEmpruntable
	public ObjetEmpruntable
{
public:
	Livre();				//constructeurs par defaut et par parametres
	Livre(const std::string& cote, const std::string& titre, unsigned int annee,
		unsigned int ageMin, unsigned int nbExemplaires, const std::string& auteur, const std::string& genre);
	~Livre();		//destructeur

	std::string obtenirAuteur() const;			//methodes d'acces aux attributs
	std::string obtenirGenre() const;

	void modifierAuteur(std::string const& auteur);			//methodes de modification des attributs
	void modifierGenre(std::string const& genre);

	//recherche renvoie true si motsCle est pr�sent dans les attributs de type string; false sinon
	bool recherche(const std::string& motsCle) const;

	friend std::ostream& operator<<(std::ostream& o, const Livre& livre);		//operateur de sortie pour un livre

protected :
	std::string auteur_;
	std::string genre_;
};

#endif