/*
Fichier: Emprunt.h
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 11 fevrier 2016
Date de modification: 21 fevrier 2016
Description: Initialisation des fonctions de la Classe Emprunt
*/

#ifndef EMPRUNT_H
#define EMPRUNT_H

#include <string>
#include "Livre.h"
#include "DVD.h"
#include <iostream>
class Emprunt
{
public:

	~Emprunt();													//destructeur

	std::string obtenirMatricule() const;						//methodes d'acces aux attributs
	//Livre* obtenirLivre() const;
	unsigned int obtenirDateRetour() const;

	void modifierMatricule(const std::string& matricule);		//methodes de modification des attributs
	void modifierLivre(Livre *livre);
	void modifierDateRetour(unsigned int date);

//____________________________________A COMPLETER !
	Emprunt(const string& matricule, unsigned int retour, Livre* livre);	//constructeur par parametres avec un livre
	Emprunt(const string& matricule, unsigned int retour, Dvd* dvd);		//constructeur par parametres avec un DVD
	//Emprunt(const string& matricule, unsigned int retour, Dvd* dvd);

	void modifierDvd(Dvd* dvd);					//methode de modification du pointeur de DVD
	//Dvd* obtenirDvd() const;
	ObjetEmpruntable* obtenirObjetEmpruntable() const;			//methode d'acces a un objet empruntable

	friend ostream&operator<<(ostream& o, const Emprunt& emprunt);		//Operateur d'affichage des informations sur un emprunt

private:
	std::string matricule_;
	Livre *livre_;
	Dvd *dvd_;
	unsigned int dateRetour_;

};

#endif