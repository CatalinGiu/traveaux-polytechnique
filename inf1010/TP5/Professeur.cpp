/*
Fichier: Professeur.cpp
Auteur(s): Julien Gauthier, Catalin Giurca
Date de creation: 10 mars 2016
Date de modification: 29 mars 2016
Description: Initialisation des fonctions de la Classe Professeur
*/

#include "Professeur.h"
#include <algorithm>
#include <iterator>

using namespace std;

Professeur::Professeur() : Abonne()
{

}
//Le constructeur par parametres prend le constructeur de la classe Abonne pour les attributs matricule, nom, prenom, age.
Professeur::Professeur(const string& matricule, const string& nom, const string& prenom, unsigned int age, list<string> ecoles) :
	Abonne(matricule, nom, prenom, age), listeEcole_(ecoles)
{

}
Professeur::~Professeur()
{

}

list<string> Professeur::obtenirEcole() const
{
	return listeEcole_;
}

void Professeur::ajouterEcole(std::string const & ecole)
{
	if (find(listeEcole_.begin(),listeEcole_.end(), ecole) != listeEcole_.end())
		listeEcole_.push_back(ecole);
}

bool Professeur::retirerEcole(std::string const & ecole)
{
	unsigned int taille = listeEcole_.size();
	listeEcole_.remove(ecole);
	return listeEcole_.size() < taille;			//Retourne true si l'operation a fonctionne (si la taille de la liste a diminue)
}

unsigned int Professeur::obtenirLimiteEmprunt() const
{
	return Abonne::obtenirLimiteEmprunt()* listeEcole_.size();
}


ostream & operator<<(ostream & o, Professeur & professeur)
{
	professeur.listeEcole_.sort();
	const Abonne* ab = &professeur;
	o << *ab
	<< "Limite d'emprunts : " << professeur.obtenirLimiteEmprunt() << endl;;


	o << "LISTE DES ECOLES : " ;

	// Affichage de la liste des ecoles
	copy(professeur.listeEcole_.rbegin(), professeur.listeEcole_.rend(),ostream_iterator<string>(o, "; "));

	o << endl;
	return o;
}