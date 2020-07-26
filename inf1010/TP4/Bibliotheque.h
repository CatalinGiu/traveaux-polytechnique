/*
Fichier: Bibliotheque.h
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 25 fevrier 2016
Date de modification: 28 fevrier 2016
Description: Initialisation des fonctions de la Classe Bibliotheque
*/
#ifndef BIBLIOTHEQUE_H
#define BIBLIOTHEQUE_H

#include <string>
#include <vector>
#include "Abonne.h"
#include "Etudiant.h"
#include "Professeur.h"
#include "ObjetEmpruntable.h"
#include "Emprunt.h"
#include <iostream>


class Bibliotheque
{
public:

	Bibliotheque();				//constructeur par defaut
	~Bibliotheque();			//destructeur

	Abonne* trouverAbonne(const std::string& matricule) const;

	ObjetEmpruntable* trouverObjetEmpruntable(const std::string& cote) const;

	std::string obtenirClasseObjet(std::string const& cote) const;

	bool ajouterAbonne(Abonne& abonne);						//methodes de modification du vecteur d'abonne
	bool retirerAbonne(const std::string& matricule);	

	bool ajouterObjetEmpruntable(ObjetEmpruntable* objet);				//methodes de modification du vecteur d'objets empruntables
	
	bool retirerObjetEmpruntable(const std::string& cote);
	void rechercherObjetEmpruntable(const std::string& str) const;		//rechercher un objet empruntable dans le vecteur

	bool estEmpruntable(const std::string& matricule, const ObjetEmpruntable& objetEmpruntable) const;	//verification que l'objet est empruntable
																										//(quantite suffisante, age de l'abonne)
	
	//Methode qui, si l'objet est empruntable, ajoute un emprunt dans la liste et diminue de 1 la quantite de l'objet
	bool emprunter(const std::string& matricule, const std::string& cote, unsigned int date);			
	bool retourner(const std::string& matricule, const std::string& cote);			//Retourne un objet et elimine l'emprunt associe a l'objet retourne

	void infoAbonne(const std::string& matricule) const;		//Methode pour obtenir les infos d'un abonne a partir de son matricule

	Bibliotheque& operator+=(Abonne* abonne);
	Bibliotheque& operator+=(ObjetEmpruntable* obj);			//Operateurs pour les operations sur les vecteurs
	Bibliotheque& operator-=(Abonne* abonne);
	Bibliotheque& operator-=(ObjetEmpruntable* obj);

	friend std::istream& operator>>(std::istream& in, const Bibliotheque& biblio);		//operateur d'entree


private:
	std::vector<Abonne*> vecAbonnes_;
	std::vector<Emprunt*> vecEmprunts_;

	/// ____ TP4 ___
	std::vector<ObjetEmpruntable*> vecObj_;
};

#endif