/*
Fichier: ObjetEmpruntable.h
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 25 fevrier 2016
Date de modification: 28 fevrier 2016
Description: Initialisation des fonctions de la Classe ObjetEmpruntable
*/
#ifndef OBJETEMPRUNTABLE_H
#define OBJETEMPRUNTABLE_H

#include <string>
#include <iostream>
#include <typeinfo>


class ObjetEmpruntable
{
public :

	/// TP4
	void afficherObjetEmpruntable(std::ostream& os) const;			//methode d'affichage d'un objet selon son type (livre, livre numerique ou dvd)
	std::string obtenirNomClasse() const;							//methode d'obtention du nom de la classe (livre, livre numerique, dvd)
	
	/// Anciens TP
	ObjetEmpruntable();			//constructeurs par defaut et par parametres
	ObjetEmpruntable(const std::string& cote, const std::string& titre, unsigned int annee,
		unsigned int ageMin, unsigned int nbExemplaires);
	~ObjetEmpruntable();

	std::string obtenirCote() const;		//Methodes d'acces aux attributs
	std::string obtenirTitre() const;
	unsigned int obtenirAnnee() const;
	unsigned int obtenirAgeMinimal() const;
	unsigned int obtenirNbExemplaires() const;
	unsigned int obtenirNbDisponibles() const;

	//convertirMinuscule permet de convertir une phrase en minuscule
	std::string convertirMinuscule(const std::string& phrase) const;

	void modifierNbExemplaires(unsigned int nbExemplaires);			//methodes de modification des attributs
	void modifierNbDisponibles(unsigned int nbDisponibles);
	void modifierTitre(const std::string& titre);
	void modifierCote(const std::string& cote);
	void modifierAnnee(unsigned int annee);
	//recherche renvoie un true si le motsCle est pr�sent dans le titre ou dans la cote; false sinon
	virtual bool recherche(const std::string& motsCle) const;


	friend std::ostream& operator<<(std::ostream& o, const ObjetEmpruntable& objetEmpruntable);		//operateur de sortie pour un objet empruntable
	bool operator==(const ObjetEmpruntable& objetEmpruntable) const;								//operateur de comparaison de deux objets empruntables
	bool operator==(const std::string& cote) const;
	friend bool operator==(const std::string& cote,  const ObjetEmpruntable& objetEmpruntable);
	bool operator< (const ObjetEmpruntable& objetEmpruntable) const;		//operateur de comparaison entre deux objets empruntables, par l'ordre
																			//alphabetique de leur titre


	
protected:
	std::string cote_;
	std::string titre_;
	unsigned int annee_;
	unsigned int ageMinimal_;
	unsigned int nbExemplaires_;
	unsigned int nbDisponibles_;
};

#endif
