/*
Fichier: Abonne.cpp
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 25 fevrier 2016
Date de modification: 28 fevrier 2016
Description: Initialisation des fonctions de la Classe Abonne
*/
#include <iostream>
#include "Abonne.h"

using namespace std;

std::string Abonne::obtenirNomClasse() const
{
	if (this != nullptr)
	{
		return typeid(*this).name();			//utilisation de typeid, qui donne le type dynamique d'un objet provenant 
												//du polymorphisme
	}
	else
	{
		return "nullptr";
	}

}

Abonne::Abonne()
	:age_(0)
{

}

Abonne::Abonne(const std::string & matricule, const std::string & nom, const std::string & prenom, unsigned int age) 
	: matricule_(matricule), nom_(nom), prenom_(prenom), age_(age), limiteEmprunt_(LIMITE_EMPRUNTS)
{

}

Abonne::~Abonne()
{

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


unsigned int Abonne::obtenirNombreEmprunte() const
{
	return vecEmprunts_.size();
}


ostream & operator<<(ostream & o, const Abonne & abonne)
{
	// Affichage des informations de base
	o << abonne.prenom_ << ", " <<
		abonne.nom_ << ". " <<
		abonne.age_ << " ans. #" <<
		abonne.matricule_ << endl;

	o << "LISTE DE LIVRES :" << endl;

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
		(matricule_ == abonne.matricule_) &&			//comparaison d'abonnes en utilisant tous les infos
		(nom_ == abonne.nom_) &&
		(prenom_ == abonne.prenom_) &&
		(age_ == abonne.age_);
}
	
bool Abonne::operator==(const std::string & matricule) const		//comparaison d'abonne en utilisant seulement le matricule
{
	return matricule_ == matricule;
}

bool operator==(const std::string & matricule, const Abonne & abonne)	
{
	return abonne == matricule;							//comparaison d'abonne en faisant abonne == matricule
}	

/// _____________TP3__________________

bool Abonne::estEmprunte(const ObjetEmpruntable & objetEmpruntable) const
{
	// v�rifier si le objetEmpruntable est d�j� emprunt�
	for (unsigned int i = 0; i < vecEmprunts_.size(); i++)
	{
		if ((*(vecEmprunts_[i]->obtenirObjetEmpruntable())) == objetEmpruntable)
		{
			return true;
		}
	}
	return false;
}

void Abonne::ajouterEmprunt(Emprunt * emprunt)
{
	vecEmprunts_.push_back(emprunt);
}

bool Abonne::retirerEmprunt(ObjetEmpruntable * objetEmpruntable)
{
	bool estRetire = false;
	for (unsigned int i = 0; i < vecEmprunts_.size(); i++)
	{
		if (*(vecEmprunts_[i]->obtenirObjetEmpruntable()) == *objetEmpruntable)
		{
			vecEmprunts_[i] = vecEmprunts_.back();
			vecEmprunts_.pop_back();
			estRetire = true;
		}
	}

	return estRetire;
}

unsigned int Abonne::obtenirLimiteEmprunt() const
{
	return limiteEmprunt_;
}
