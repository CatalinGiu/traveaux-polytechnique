/*
Fichier: ObjetEmpruntable.h
Auteur(s): Julien Gauthier, Catalin Giurca
Date de creation: 10 mars 2016
Date de modification: 29 mars 2016
Description: Initialisation des fonctions de la Classe ObjetEmpruntable
*/

#ifndef OBJETEMPRUNTABLE_H
#define OBJETEMPRUNTABLE_H

#include <string>
#include <iostream>
#include <typeinfo>

//La classe ObjetEmpruntable reste inchangee du TP4, aucune description (commentaire)
//supplementaire ne sera donc mentionnee ici.
class ObjetEmpruntable
{
public :

	/// TP4

	virtual std::string obtenirNomClasse() const;
	void afficherObjetEmpruntable(std::ostream& o) const;

	/// Anciens TP
	ObjetEmpruntable();
	ObjetEmpruntable(const std::string& cote, const std::string& titre, unsigned int annee,
		unsigned int ageMin, unsigned int nbExemplaires);
	virtual ~ObjetEmpruntable() = 0;

	std::string obtenirCote() const;
	std::string obtenirTitre() const;
	unsigned int obtenirAnnee() const;
	unsigned int obtenirAgeMinimal() const;
	unsigned int obtenirNbExemplaires() const;
	unsigned int obtenirNbDisponibles() const;

	//convertirMinuscule permet de convertir une phrase en minuscule
	std::string convertirMinuscule(const std::string& phrase) const;

	void modifierNbExemplaires(unsigned int nbExemplaires);
	void modifierNbDisponibles(unsigned int nbDisponibles);
	void modifierTitre(const std::string& titre);
	void modifierCote(const std::string& cote);
	void modifierAnnee(unsigned int annee);
	//recherche renvoie un true si le motsCle est pr�sent dans le titre ou dans la cote; false sinon
	virtual bool recherche(const std::string& motsCle) const;


	friend std::ostream& operator<<(std::ostream& o, const ObjetEmpruntable& objetEmpruntable);
	bool operator==(const ObjetEmpruntable& objetEmpruntable) const;
	bool operator==(const std::string& cote) const;
	friend bool operator==(const std::string& cote,  const ObjetEmpruntable& objetEmpruntable);
	bool operator< (const ObjetEmpruntable& objetEmpruntable) const;



	
protected:
	std::string cote_;
	std::string titre_;
	unsigned int annee_;
	unsigned int ageMinimal_;
	unsigned int nbExemplaires_;
	unsigned int nbDisponibles_;
};

#endif
