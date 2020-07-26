/*
Fichier: Emprunt.h
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 25 fevrier 2016
Date de modification: 28 fevrier 2016
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

	~Emprunt();			//destructeur

	std::string obtenirMatricule() const;			//methodes d'acces aux attributs
	unsigned int obtenirDateRetour() const;
		
	void modifierMatricule(const std::string& matricule);		//methodes de modification des attributs
	void modifierDateRetour(unsigned int date);


	/// _____ TP4 _____

	Emprunt(const std::string& matricule,ObjetEmpruntable* obj, unsigned int date);		//constructeur par parametres
	ObjetEmpruntable* obtenirObjetEmpruntable() const;		//methode d'acces a l'attribut objEmprunt_

	void setObjet(ObjetEmpruntable* obj);					//methode de modification de l'attribut objEmprunt_

	friend std::ostream&operator<<(std::ostream& os, const Emprunt& emprunt);		//operateur de sortie pour un emprunt





private:
	std::string matricule_;
	unsigned int dateRetour_;

	/// _____ TP4 _____
	ObjetEmpruntable* objEmprunt_;

};

#endif