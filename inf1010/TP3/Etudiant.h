/*
Fichier: Etudiant.h
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 11 fevrier 2016
Date de modification: 21 fevrier 2016
Description: Initialisation des fonctions de la Classe Etudiant
*/

#ifndef TP3_INF1010_ETUDIANT_H
#define TP3_INF1010_ETUDIANT_H

#include "Abonne.h"
#include "iostream"
using namespace std;

class Etudiant : public Abonne{			//la classe Etudiant est derivee de la classe Abonne

public:
    Etudiant();		//constructeur par defaut
    ~Etudiant();	//destructeur
    Etudiant(const string& matricule, const string& nom, const string& prenom, unsigned int age , const string& ecole);
	//constructeur par parametres (Etudiant herite des attributs de Abonne)

    friend ostream& operator<<(ostream& o, const Etudiant& etudiant);		//Operateur d'affichage des infos d'un etudiant

    unsigned int obtenirLimiteEmprunts() const ;		//methode d'acces a la limite d'emprunts



private:
    string ecole_;

};

#endif //TP3_INF1010_ETUDIANT_H
