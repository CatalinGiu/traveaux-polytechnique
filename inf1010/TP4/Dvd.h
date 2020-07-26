/*
Fichier: Dvd.h
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 25 fevrier 2016
Date de modification: 28 fevrier 2016
Description: Initialisation des fonctions de la Classe Dvd
*/
#ifndef DVD_H
#define DVD_H
#include "ObjetEmpruntable.h"
#include <vector>

class Dvd :						//Dvd est une classe derivee de ObjetEmpruntable
	public ObjetEmpruntable
{
public:
	Dvd();				//constructeurs par defaut et par parametres
	Dvd(const std::string& cote, const std::string& titre, unsigned int annee,
		unsigned int ageMin, unsigned int nbExemplaires, std::string const& realisateur, std::vector<std::string> acteurs);

	~Dvd();				//destructeur

	std::string obtenirRealisateur() const;				//methodes d'acces aux attributs
	std::vector<std::string> obtenirActeur() const;

	void modifierRealisateur(std::string const& realisateur);		//methodes de modification du string et du vecteur
	void ajouterActeur(std::string const& acteur);			
	void retirerActeur(std::string const& acteur);

	//recherche renvoie true si motsCle est présent dans les attributs de type string; false sinon
	bool recherche(const std::string& motsCle) const;

	friend std::ostream& operator<<(std::ostream& o, const Dvd& dvd);		//operateur de sortie pour un Dvd

private:
	std::string realisateur_;
	std::vector<std::string> vecActeurs_;

};
#endif

