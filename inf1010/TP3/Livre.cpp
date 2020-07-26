/*
Fichier: Livre.cpp
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 11 fevrier 2016
Date de modification: 21 fevrier 2016
Description: Initialisation des fonctions de la Classe Livre
*/

#include "Livre.h"

//Toutes les m�thodes sont d�crites dans livre.h.

Livre::Livre() {

}

Livre::Livre(const string &cote, const string &titre, unsigned int annee, unsigned int ageMin,
             unsigned int nbExemplaires, const string &auteur, const string &genre): ObjetEmpruntable(cote, titre, annee, ageMin, nbExemplaires), auteur_(auteur), genre_(genre) {
}

string Livre::obtenirAuteur() const {
    return auteur_;
}

void Livre::setAuteur(const string &auteur) {
    auteur_ = auteur;
}

string Livre::obtenirGenre() const {
    return genre_;
}

void Livre::setGenre(const string &genre) {
    genre_ = genre;
}

ostream &operator<<(ostream &o, const Livre &livre) {
    return o << "Information sur le livre : " << endl << static_cast<const ObjetEmpruntable&>(livre) /* operateur << de ObjetEmpruntable */<<
            " Autheur: " << livre.auteur_ << "; Genre: " << livre.genre_ <<  endl;
}

std::string Livre::getType() const {
    return "Livre";
}

bool Livre::rechercher(const string &mot) const {
    bool livreTrouve = ObjetEmpruntable::rechercher(mot);
    if(!livreTrouve){
        livreTrouve = convertirMinuscule(auteur_).find(convertirMinuscule(mot)) != string::npos || convertirMinuscule(genre_).find(convertirMinuscule(mot)) != string::npos;
    }

    return livreTrouve;
}
