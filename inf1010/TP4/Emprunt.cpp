/*
Fichier: Emprunt.cpp
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 25 fevrier 2016
Date de modification: 28 fevrier 2016
Description: Initialisation des fonctions de la Classe Emprunt
*/
#include <iostream>
#include "Emprunt.h"

using namespace std;


Emprunt::~Emprunt()
{

}

string Emprunt::obtenirMatricule() const
{
	return matricule_;
}



unsigned int Emprunt::obtenirDateRetour() const
{
	return dateRetour_;
}

void Emprunt::modifierMatricule(const string &matricule)
{
	matricule_ = matricule;
}

void Emprunt::modifierDateRetour(unsigned int date)
{
	dateRetour_ = date;
}


/// TP4


Emprunt::Emprunt(const std::string &matricule,ObjetEmpruntable* obj, unsigned int date) :matricule_(matricule),
				objEmprunt_(obj), dateRetour_(date) {

}

ObjetEmpruntable* Emprunt::obtenirObjetEmpruntable() const {
	return objEmprunt_;
}

void Emprunt::setObjet(ObjetEmpruntable* obj) {
	objEmprunt_ = obj;
}

std::ostream &operator<<(std::ostream &os, const Emprunt &emprunt) {
	os << emprunt.matricule_ << ". " << emprunt.objEmprunt_->obtenirNomClasse()
	<< ". ";
	emprunt.objEmprunt_->afficherObjetEmpruntable(os);
	os <<"Retour prevu: " << emprunt.dateRetour_ << endl;
	return os;
}
