/*
Fichier: EtudiantBaccalaureat.cpp
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 25 fevrier 2016
Date de modification: 28 fevrier 2016
Description: Initialisation des fonctions de la Classe EtudiantBaccalaureat
*/
#include "EtudiantBaccalaureat.h"

using namespace std;

//Le constructeur d'EtudiantBaccalaureat est le meme qu'Etudiant, mais l'ecole doit etre Polytechnique.
EtudiantBaccalaureat::EtudiantBaccalaureat(const std::string& matricule, const std::string& nom, const std::string& prenom, unsigned int age)
	: Etudiant(matricule, nom, prenom, age, "Polytechnique Montreal")
{

}

unsigned int EtudiantBaccalaureat::obtenirLimiteEmprunt() const		//La limite d'emprunts d'un etudiant au baccalaureat est 2 fois plus 
{																	//que celle d'un etudiant.
	return (Etudiant::obtenirLimiteEmprunt()) * 2;
}

