/*
Fichier: Livre.h
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 11 fevrier 2016
Date de modification: 21 fevrier 2016
Description: Initialisation des fonctions de la Classe Livre
*/

#ifndef TP3_INF1010_LIVRE_H
#define TP3_INF1010_LIVRE_H


#include "ObjetEmpruntable.h"
#include <iostream>

using namespace std;
class Livre : public ObjetEmpruntable {			//La classe Livre est derivee de la classe ObjetEmpruntable, par un procede d'heritage.
public:
    Livre();
	//constructeur par defaut
    Livre(const string& cote, const string& titre, unsigned int annee, unsigned int ageMin, unsigned int nbExemplaires, const string& auteur, const string& genre);
	//constructeur par parametres (Livre herite des attributs de ObjetEmpruntable)

    string obtenirAuteur() const;			//methode d'acces de l'auteur du livre
    void setAuteur(const string& auteur);	//methode de modification de l'auteur

    string obtenirGenre() const;			//methode d'acces du genre
    void setGenre(const string& genre);		//methode de modification du genre

    friend ostream&operator<<(ostream& o, const Livre& livre);		//operateur de sortie pour afficher les infos d'un livre
    virtual std::string getType() const;							//methode virtual pour obtenir le type

    bool rechercher(const string& mot) const;

private:
    string auteur_;
    string genre_;
};


#endif //TP3_INF1010_LIVRE_H
