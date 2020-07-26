/*
Fichier: Abonne.cpp
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 11 fevrier 2016
Date de modification: 21 fevrier 2016
Description: Initialisation des fonctions de la Classe Abonne
*/


#include <iostream>
#include "Abonne.h"

using namespace std;

//Toutes les methodes sont identifiees dans Abonne.h. Certaines obtiennent de la precision supplementaire ici.

Abonne::Abonne()
	:age_(0)
{

}

Abonne::Abonne(const std::string & matricule, const std::string & nom, const std::string & prenom, unsigned int age) 
	: matricule_(matricule), nom_(nom), prenom_(prenom), age_(age), limiteEmprunts_(LIMITE_EMPRUNTS)
{

}

Abonne::~Abonne()
{
	vecEmprunts_.clear();
}

string Abonne::obtenirMatricule() const
{
	return matricule_;
}

string Abonne::obtenirNom() const
{
	return nom_;
}

string Abonne::obtenirPrenom() const
{
	return prenom_;
}

unsigned int Abonne::obtenirAge() const
{
	return age_;
}

std::vector<Emprunt*> Abonne::obtenirEmprunts() const
{
	return vecEmprunts_;
}

void Abonne::modifierMatricule(const string& matricule)
{
	matricule_ = matricule;
}

void Abonne::modifierNom(const string& nom)
{
	nom_ = nom;
}

void Abonne::modifierPrenom(const string& prenom)
{
	prenom_ = prenom;
}

void Abonne::modifierAge(unsigned int age)
{
	age_ = age;
}

void Abonne::ajouterEmprunt(Emprunt * emprunt)
{
	vecEmprunts_.push_back(emprunt);
}

unsigned int Abonne::obtenirNombreEmprunte() const		//Le nombre d'emprunts est obtenus en retournant la grosseur (size) du 
{														//vecteur d'emprunts (correspond au nombre d'elements e l'interieur).
	return vecEmprunts_.size();
}


ostream & operator<<(ostream & o, const Abonne & abonne)
{
	// Affichage des informations de base
	o << abonne.prenom_ << ", " <<
		abonne.nom_ << ". " <<
		abonne.age_ << " ans. #" <<
		abonne.matricule_ << endl;

	o << "LISTE D'EMPRUNTS :" << endl;

	// Affichage de la liste de objetEmpruntables

	for (unsigned int i = 0; i < abonne.vecEmprunts_.size(); i++)
	{
		o << i + 1 << " - " << *(abonne.vecEmprunts_[i]) << endl;
	}
	// retour
	return o;

}

bool Abonne::operator==(const Abonne & abonne) const
{
	return
		(matricule_ == abonne.matricule_) &&				//Tous les attributs doivent �tre identiques pour retourner true.
		(nom_ == abonne.nom_) &&
		(prenom_ == abonne.prenom_) &&
		(age_ == abonne.age_);
}

bool Abonne::operator==(const std::string & matricule) const
{
	return matricule_ == matricule;
}

bool operator==(const std::string & matricule, const Abonne & abonne)
{
	return abonne == matricule;
}

unsigned int Abonne::obtenirLimiteEmprunts() const {
	return limiteEmprunts_;
}

bool Abonne::estEmprunte(const string& cote) const {				//Retourne true si l'objet identifie par sa cote est emprunte
	bool memeCote = false;											//(dans le vecteur d'emprunts).
	for(unsigned int i = 0; i < vecEmprunts_.size(); i++){
		if(*vecEmprunts_[i]->obtenirObjetEmpruntable() == cote){
			memeCote = true;
		}
	}
	return memeCote;
}

void Abonne::enleverEmprunt(unsigned int pos) {							//enleve un element du vecteur d'emprunts, meme 
	for (unsigned int i = pos; i < vecEmprunts_.size() - 1; i++) {		//au milieu du vecteur
		vecEmprunts_[i] = vecEmprunts_[i + 1];
	}
	vecEmprunts_.pop_back();
}

void Abonne::retirerEmprunt(const ObjetEmpruntable& objetEmpruntable) {		//retire un Emprunt du vecteur d'emprunts en prenant un objetEmpruntable
	bool retraitFait = false;												//en parametre. Fait appel a la fonction enleverEmprunt pour simplifier
	for (unsigned int i = 0; i < vecEmprunts_.size() && !retraitFait; i++) {
		if (*(vecEmprunts_[i]->obtenirObjetEmpruntable()) == objetEmpruntable) {
			enleverEmprunt(i);
			retraitFait = true;
		}
	}
}

