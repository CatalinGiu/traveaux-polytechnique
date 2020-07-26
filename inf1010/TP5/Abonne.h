/*
Fichier: Abonne.h
Auteur(s): Julien Gauthier, Catalin Giurca
Date de creation: 10 mars 2016
Date de modification: 29 mars 2016
Description: Description de la classe Abonne
*/

#ifndef ABONNE_H
#define ABONNE_H

#include <string>
#include "Emprunt.h"
#include "ObjetEmpruntable.h"
#include <iostream>

#define LIMITE_EMPRUNTS 2		//Limite d'emprunts definie a 2 pour un abonne normal


class Abonne
{
public:

	/// TP4
	virtual std::string obtenirNomClasse() const;


	/// TP3
	//Constructeurs par defaut et par paametres
	Abonne();
	Abonne(const std::string& matricule, const std::string& nom, const std::string& prenom, unsigned int age);

	~Abonne();	//destructeur

	std::string obtenirMatricule() const;		//methodes d'acces
	std::string obtenirNom() const;
	std::string obtenirPrenom() const;
	unsigned int obtenirAge() const;

	void modifierMatricule(const std::string& matricule);		//methodes de modification
	void modifierNom(const std::string& nom);	
	void modifierPrenom(const std::string& prenom);
	void modifierAge(unsigned int age);

	virtual unsigned int obtenirLimiteEmprunt() const;	//Methode d'acces a la limite d'emprunt d'un abonne normal (definie virtuelle)
	friend std::ostream& operator<<(std::ostream& o, const Abonne& abonne);			//Operateurs de sortie et de comparaison
	bool operator==(const Abonne& abonne) const;
	bool operator==(const std::string& matricule) const;
	friend bool operator==(const std::string& matricule, const Abonne& abonne);


private:
	std::string matricule_;
	std::string nom_;
	std::string prenom_;
	unsigned int age_;

	/// ____TP3_____
	unsigned int limiteEmprunt_;

};

	
#endif
