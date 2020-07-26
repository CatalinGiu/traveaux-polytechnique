/*
Fichier: ObjetEmpruntable.h
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 11 fevrier 2016
Date de modification: 21 fevrier 2016
Description: Initialisation des fonctions de la Classe ObjetEmpruntable
*/

#ifndef OBJETEMPRUNTABLE_H
#define OBJETEMPRUNTABLE_H

#include <string>
#include <iostream>

class ObjetEmpruntable
{
public :
	ObjetEmpruntable();
	//constructeur par defaut
	ObjetEmpruntable(const std::string& cote, const std::string& titre, unsigned int annee,
		unsigned int ageMin, unsigned int nbExemplaires);
	//constructeur par parametres
	~ObjetEmpruntable();				//destructeur

	std::string obtenirCote() const;				//methodes d'acces des attributs
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
	//recherche renvoie un true si le motsCle est present dans le titre ou dans la cote; false sinon
	bool rechercher(const std::string& motsCle) const;


	friend std::ostream& operator<<(std::ostream& o, const ObjetEmpruntable& objetEmpruntable);	//operateur d'affichage d'un objet empruntable
	bool operator==(const ObjetEmpruntable& objetEmpruntable) const;							//compare deux objets empruntables avec la cote et le titre
	bool operator==(const std::string& cote) const;												//compare deux objets avec leur cote
	friend bool operator==(const std::string& cote,  const ObjetEmpruntable& objetEmpruntable);	//fait objetEmpruntable == cote
	bool operator< (const ObjetEmpruntable& objetEmpruntable) const;							//classe les objets empruntables en ordre selon leur titre

	virtual std::string getType() const;

private:
	std::string cote_;
	std::string titre_;
	unsigned int annee_;
	unsigned int ageMinimal_;
	unsigned int nbExemplaires_;
	unsigned int nbDisponibles_;
};

#endif
