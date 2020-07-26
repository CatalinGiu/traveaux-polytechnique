/*
Fichier: Etudiant.cpp
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 25 fevrier 2016
Date de modification: 28 fevrier 2016
Description: Initialisation des fonctions de la Classe Etudiant
*/
#include "Etudiant.h"

using namespace std;

Etudiant::Etudiant() : Abonne(), ecole_("")
{

}
//Le constructeur d'Etudiant utilise le constructeur d'Abonne pour le matricule, nom, prenom et age.
Etudiant::Etudiant(const string& matricule, const string& nom, const string& prenom, unsigned int age, const string& ecole) :
	Abonne(matricule, nom, prenom, age), ecole_(ecole)
{

}
Etudiant::~Etudiant()
{

}

string Etudiant::obtenirEcole() const
{
	return ecole_;
}

void Etudiant::modifierEcole(const string& ecole)
{
	ecole_ = ecole;
}

unsigned int Etudiant::obtenirLimiteEmprunt() const				//La limite d'emprunts d'un etudiant est 2 fois plus que celle d'un abonne normal.
{
	return Abonne::obtenirLimiteEmprunt() * 2;
}

ostream & operator<<(ostream & o, const Etudiant & etudiant)
{
	const Abonne* ab = &etudiant;
	return o << (*ab)
		<< "Ecole de provenance : "
		<< etudiant.ecole_ 
		<< "; Limite d'emprunts : " << etudiant.obtenirLimiteEmprunt() << endl;
}
