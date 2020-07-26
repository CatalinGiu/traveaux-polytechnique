/*
Fichier: Professeur.h
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 11 fevrier 2016
Date de modification: 21 fevrier 2016
Description: Initialisation des fonctions de la Classe Professeur
*/


#ifndef TP3_INF1010_PROFESSEUR_H
#define TP3_INF1010_PROFESSEUR_H


#include "Abonne.h"
#include <vector>
#include <iostream>

#define LIMITE_EMPRUNTS 2

using namespace std;

class Professeur : public Abonne {			//La classe Professeur est derivee de la classe Abonne.
public:
    Professeur();		//constructeur par defaut
    ~Professeur();		//destructeur

    Professeur(const string& matricule, const string& nom, const string& prenom, unsigned int age, vector<string> vEcoles);
	//constructeur par parametres (Professeur herite des attributs de Abonne)

    vector<string> obtenirVEcoles() const ;		//acces au vecteur de noms d'ecoles

    void ajouterEcole(const string& ecole);		//Methodes de modification du veteur d'ecoles (ajout ou retrait d'une ecole).
    bool retirerEcole(const string& ecole);

    unsigned int obtenirLimiteEmprunts() const;								//acces au nombre limite d'emprunts d'un professeur
    friend ostream& operator<<(ostream& o, const Professeur& professeur);	//operateur d'affichage des infos d'un professeur

private:
    vector<string> vEcoles_;
};


#endif //TP3_INF1010_PROFESSEUR_H
