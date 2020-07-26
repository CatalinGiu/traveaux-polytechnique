/*
Fichier: DVD.h
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 11 fevrier 2016
Date de modification: 21 fevrier 2016
Description: Initialisation des fonctions de la Classe DVD
*/

#ifndef TP3_INF1010_DVD_H
#define TP3_INF1010_DVD_H


#include "ObjetEmpruntable.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Dvd : public ObjetEmpruntable{			//La classe DVD est derivee de la classe ObjetEmpruntable, par un procede d'heritage.

public:
    Dvd(const string &cote, const string &titre, unsigned int annee, unsigned int ageMin, unsigned int nbExemplaires, const string &realisateur, vector<string> vActeurs);
   //constructeur par parametres (DVD herite des attributs de ObjetEmpruntable)

	bool rechercher(const string& motCle);		//recherche un DVD avec tous ses attributs avec un mot entree en parametre

    string obtenirRealisateur() const;				//methodes d'acces et de modification de realisateur
    void setRealisateur(const string& realisateur);

    void addActor(const string& actor);					//methode de modification du vecteur d'acteurs, avec les options 	
    bool rmvActor(const string& actor);					//d'ajouter ou de retirer un acteur.

    vector<string> getVActor() const ;					//methode d'acces du vecteur d'acteurs
    virtual std::string getType() const;				//acces au type

    friend ostream&operator<<(ostream& o, const Dvd& dvd);		//operateur d'affichage des infos d'un DVD

private:
    string realisateur_;
    vector<string> vActeurs_;
};


#endif //TP3_INF1010_DVD_H
