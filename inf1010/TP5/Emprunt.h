/*
Fichier: Emprunt.h
Auteur(s): Julien Gauthier, Catalin Giurca
Date de creation: 10 mars 2016
Date de modification: 29 mars 2016
Description: Initialisation des fonctions de la Classe Emprunt
*/

#ifndef EMPRUNT_H
#define EMPRUNT_H

#include <string>
#include "Livre.h"
#include "Dvd.h"

class Emprunt
{
public:

	~Emprunt();	//destructeur

	std::string obtenirMatricule() const;			//Methodes d'acces aux attributs
	unsigned int obtenirDateRetour() const;

	void modifierMatricule(const std::string& matricule);	//Methodes de modification des attributs
	void modifierDateRetour(unsigned int date);


	/// _____ TP4 _____

	//Constructeur par parametres
	Emprunt(std::string matricule, ObjetEmpruntable* objEmprunt, unsigned int date);

	ObjetEmpruntable* obtenirObjetEmpruntable() const;		//Methode d'acces a un objet empruntable
		
	friend std::ostream& operator<<(std::ostream& o, const Emprunt& emprunt);	//Operateur de sortie
	
	
	/// _____ TP5 _____
	//Operateurs de comparaison 
	bool operator==(const Emprunt& emprunt) const;
	bool operator==(const std::string& matricule) const;
	bool operator==(const std::pair<std::string, std::string>&)const;		//On cree un objet qui associe un string a un autre,
																			//qui les met ensemble pour faire un pair.
	friend bool operator==(const std::string& matricule, const Emprunt& emprunt);
	friend bool operator==(const std::pair<std::string, std::string>&, const Emprunt& emprunt);

private:
	std::string matricule_;
	unsigned int dateRetour_;

	/// _____ TP4 _____
	ObjetEmpruntable* objEmprunt_;

};

#endif