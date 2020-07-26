/*
Fichier: EtudiantBaccalaureat.cpp
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 11 fevrier 2016
Date de modification: 21 fevrier 2016
Description: Initialisation des fonctions de la Classe EtudiantBaccalaureat
*/

#include "EtudiantBaccalaureat.h"

unsigned int EtudiantBaccalaureat::obtenirLimiteEmprunts() {		//Un etudiant au baccalaureat a la possibilite 
 return Etudiant::obtenirLimiteEmprunts() * 2;						//d'emprunter 2 fois plus qu'un etudiant normal.
}

EtudiantBaccalaureat::EtudiantBaccalaureat(const string &matricule, const string &nom, const string &prenom,
                                           unsigned int age) : Etudiant(matricule,nom, prenom, age, "Polytechnique Montreal"){
	}
//Un etudiant au baccalaureat a obligatoirement l'universite Polytechnique Montreal comme ecole.