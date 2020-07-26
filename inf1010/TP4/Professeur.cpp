/*
Fichier: Professeur.cpp
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 25 fevrier 2016
Date de modification: 28 fevrier 2016
Description: Initialisation des fonctions de la Classe Professeur
*/
#include "Professeur.h"

using namespace std;

Professeur::Professeur() : Abonne()
{

}
//Le constructeur par parametres de Professeur utilise le constructeur par parametres de Abonne pour le matricule, l'age, le nom et le prenom.
Professeur::Professeur(const string& matricule, const string& nom, const string& prenom, unsigned int age, vector<string> ecoles) :
	Abonne(matricule, nom, prenom, age), vecEcole_(ecoles)
{

}
Professeur::~Professeur()
{

}

vector<string> Professeur::obtenirEcole() const
{
	return vecEcole_;
}

void Professeur::ajouterEcole(std::string const & ecole)
{
	bool present = false;
	// ajoute l'ecole que si elle n'est pas déjà présente dans le vecteur

	for  (unsigned int i = 0; i < vecEcole_.size(); i++)
	{
		if (vecEcole_[i] == ecole)
		{
			present = true;
		}
	}
	if (!present)
		vecEcole_.push_back(ecole);
}

bool Professeur::retirerEcole(std::string const & ecole)
{
	for (unsigned int i = 0; i < vecEcole_.size(); i++)
	{
		// retire l'ecole que si elle est présente dans le vecteur

		if (vecEcole_[i] == ecole)
		{
			vecEcole_[i] = vecEcole_.back();
			vecEcole_.pop_back();
			return true;
		}
	}
	return false;
}

unsigned int Professeur::obtenirLimiteEmprunt() const		//La limite d'emprunts d'un professeur est la meme que celle d'un abonne normal,
{															//multipliee par le nomre d'ecole a lesquelles il enseigne.
	return Abonne::obtenirLimiteEmprunt()*vecEcole_.size();
}


ostream & operator<<(ostream & o, const Professeur & professeur)
{
	const Abonne* ab = &professeur;
	o << *ab 
	<< "Limite d'emprunts : " << professeur.obtenirLimiteEmprunt() << endl;;
		

	o << "LISTE DES ECOLES : " ;

	// Affichage de la liste des ecoles

	for (size_t i = 0; i < professeur.vecEcole_.size(); i++)
	{
		o << professeur.vecEcole_[i] << "; ";
	}
	o << endl;
	return o;
}