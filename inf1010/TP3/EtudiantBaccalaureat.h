/*
Fichier: EtudiantBaccalaureat.h
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 11 fevrier 2016
Date de modification: 21 fevrier 2016
Description: Initialisation des fonctions de la Classe EtudiantBaccalaureat
*/

#ifndef TP3_INF1010_ETUDIANTBACCALAUREAT_H
#define TP3_INF1010_ETUDIANTBACCALAUREAT_H


#include "Etudiant.h"

class EtudiantBaccalaureat : public Etudiant {		//La classe EtudiantBaccalaureat est derivee de la classe Etudiant.
public:
    EtudiantBaccalaureat(const string& matricule, const string& nom, const string& prenom, unsigned int age);
	//constructeur par parametres (EtudiantBaccalaureat herite des attributs de Etudiants, qui herite de Abonne)

    unsigned int obtenirLimiteEmprunts();		//acces a la limite d'emprunts
};


#endif //TP3_INF1010_ETUDIANTBACCALAUREAT_H
