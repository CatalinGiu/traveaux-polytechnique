/*
Fichier: Etudiant.cpp
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 11 fevrier 2016
Date de modification: 21 fevrier 2016
Description: Initialisation des fonctions de la Classe Etudiant
*/

#include "Etudiant.h"

//Toutes les methodes sont decrites dans Etudiant.h

Etudiant::Etudiant(const string &matricule, const string &nom, const string &prenom, unsigned int age,
                   const string &ecole) : Abonne(matricule, nom, prenom, age), ecole_(ecole){
}

Etudiant::Etudiant() {

}

Etudiant::~Etudiant() {

}

ostream &operator<<(ostream &o, const Etudiant &etudiant) {
    return o << static_cast<const Abonne&>(etudiant) << "Ecole de Provenance: " << etudiant.ecole_ << "; Limite d'emprunts : " << etudiant.obtenirLimiteEmprunts() << endl;
}
//L'ecole d'un etudiant peut varier, contrairement a EtudiantBaccalaureat, c'est pourquoi l'ecole est un attribut d'etudiant.

unsigned int Etudiant::obtenirLimiteEmprunts() const {			//Un etudiant a le double de la limite d'emprunts d'un abonne, donc la limite d'emprunts
    return Abonne::obtenirLimiteEmprunts() * 2;					//est doublee.
}
