/*
Fichier: Emprunt.cpp
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 11 fevrier 2016
Date de modification: 21 fevrier 2016
Description: Initialisation des fonctions de la Classe Emprunt
*/

#include <iostream>
#include "Emprunt.h"

using namespace std;

//Toutes les methodes sont decrites dans Emprunt.h
Emprunt::~Emprunt()
{
}

string Emprunt::obtenirMatricule() const
{
	return matricule_;
}

ObjetEmpruntable* Emprunt::obtenirObjetEmpruntable() const
{
	ObjetEmpruntable* objetEmprunte = nullptr;		//On obtient un DVD avec cette methode si le pointeur vers la classe Livre est vide
	if(livre_ == nullptr)
		objetEmprunte = dvd_;
	else
		objetEmprunte = livre_;						//On obtient un livre avec cette methode si le pointeur vers Livre n'est pas vide
	return objetEmprunte;	
}


unsigned int Emprunt::obtenirDateRetour() const
{
	return dateRetour_;
}

void Emprunt::modifierMatricule(const string &matricule)
{
	matricule_ = matricule;
}

void Emprunt::modifierLivre(Livre* livre)
{
	if(livre_ != nullptr)
		livre_ = livre;
}


void Emprunt::modifierDateRetour(unsigned int date)
{
	dateRetour_ = date;
}

//Initialise le pointeur de DVD a null, puisque c'est le constructeur pour un emprunt de livre.
Emprunt::Emprunt(const string &matricule, unsigned int retour, Livre *livre) : matricule_(matricule), dateRetour_(retour), livre_(livre), dvd_(nullptr){
}

void Emprunt::modifierDvd(Dvd *dvd) {
	if(dvd_ != nullptr)			//On verifie d'abord qu'il existe deja un emprunt de DVD
		dvd_ = dvd;
}

ostream &operator<<(ostream &o, const Emprunt &emprunt) {
	o << "Usager #" << emprunt.matricule_;

	if(emprunt.obtenirObjetEmpruntable()->getType() == "Livre"){
		o << " Livre " << static_cast<Livre&>(*emprunt.obtenirObjetEmpruntable());
	}
	else if(emprunt.obtenirObjetEmpruntable()->getType() == "DVD"){
		o << " Dvd " << static_cast<Dvd&>(*emprunt.obtenirObjetEmpruntable());
	}
	return  o << "Retour prevu : " << emprunt.dateRetour_ << endl;
}

Emprunt::Emprunt(const string &matricule, unsigned int retour, Dvd *dvd) : matricule_(matricule), dateRetour_(retour), dvd_(dvd), livre_(nullptr){
}
//Initialise le pointeur de Livre a null, puisque c'est le constructeur pour un emprunt de DVD.