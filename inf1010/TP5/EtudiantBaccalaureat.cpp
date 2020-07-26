/*
Fichier: EtudiantBaccalaureat.cpp
Auteur(s): Julien Gauthier, Catalin Giurca
Date de creation: 10 mars 2016
Date de modification: 29 mars 2016
Description: Initialisation des fonctions de la Classe EtudiantBaccaLaureat
*/

#include "EtudiantBaccalaureat.h"

using namespace std;

EtudiantBaccalaureat::EtudiantBaccalaureat(const std::string& matricule, const std::string& nom, const std::string& prenom, unsigned int age)
	: Etudiant(matricule, nom, prenom, age, "Polytechnique Montreal")
{

}

unsigned int EtudiantBaccalaureat::obtenirLimiteEmprunt() const
{
	return (Etudiant::obtenirLimiteEmprunt()) * 2;		//La limite d'emprunt est 2 fois plus que celle d'un etudiant normal.
}
