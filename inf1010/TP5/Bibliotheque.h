/*
Fichier: Bibliotheque.h
Auteur(s): Julien Gauthier, Catalin Giurca
Date de creation: 10 mars 2016
Date de modification: 29 mars 2016
Description: la classe qui fait le lien entre toutes les autres classes 
*/
#ifndef BIBLIOTHEQUE_H
#define BIBLIOTHEQUE_H

#include <string>
#include <map>
#include "Abonne.h"
#include "ObjetEmpruntable.h"
#include "Emprunt.h"
#include "Gestionnaire.h"
#include <iostream>
#include <map>


class Bibliotheque
{
public:

	Bibliotheque();	//constructeur par defaut
	~Bibliotheque();	//destructeur

	Abonne* trouverAbonne(std::string& matricule) const;	//methode pour trouver un abonne selon son matricule

	ObjetEmpruntable* trouverObjetEmpruntable(std::string& cote) const;	//Trouver un objet empruntable selon sa cote

	std::string obtenirClasseObjet(std::string & cote) const;		//methode d'acces a la classe d'un objet

	bool ajouterAbonne(Abonne& abonne);					//Methodes d'ajout et de retrait d'un abonne dans le 
	bool retirerAbonne(std::string& matricule);			//gestionnaire d'abonnes

	bool ajouterObjetEmpruntable(ObjetEmpruntable* objet);	//Methodes d'ajout, de retrait et de recherche d'un objet empruntable
	bool retirerObjetEmpruntable(std::string& cote);		//dans le gestionnaire d'objets empruntables
	void rechercherObjetEmpruntable(std::string& str) const;

	//Methodes pour ajouter un emprunt a un abonne et pour en enlever un dans le gestionnaire d'emprunts
	bool emprunter(std::string& matricule, std::string& cote, unsigned int date);	 
	bool retourner(std::string& matricule, std::string& cote);

	void infoAbonne(const std::string& matricule) const;	//Obtenir les infos d'un abonne (emprunts, etc) selon son matricule

	Bibliotheque& operator+=(Abonne* abonne);			//Operateurs d'ajout et de retrait d'un abonne ou d'un objet empruntable
	Bibliotheque& operator+=(ObjetEmpruntable* obj);
	Bibliotheque& operator-=(Abonne* abonne);
	Bibliotheque& operator-=(ObjetEmpruntable* obj);

	friend std::istream& operator>>(std::istream& in, const Bibliotheque& biblio);	//Operateur d'entree d'une bibliotheque

	/// ____ TP5 ___
	std::map<std::string, Emprunt*> trierEmprunt(Abonne * abonne) const;	//Methode qui retourne une map, qui associe une cle
																		//a une valeur et trie les emprunts en ordre alphabetique
																			
private:

	/// ____ TP5 ___
	Gestionnaire<Abonne> gestAbonnes_;			//Les attributs de la classe Bibliotheque proviennent de la classe Gestionnaire
	Gestionnaire<Emprunt> gestEmprunts_;
	Gestionnaire<ObjetEmpruntable>gestObj_;
};

#endif