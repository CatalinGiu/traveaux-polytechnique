/*
Fichier: DVD.cpp
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 11 fevrier 2016
Date de modification: 21 fevrier 2016
Description: Initialisation des fonctions de la Classe DVD
*/


#include "DVD.h"

//Toutes les methodes sont decrites dans DVD.h, seulement quelques precisions sont presentes ici.

Dvd::Dvd(const string &cote, const string &titre, unsigned int annee, unsigned int ageMin, unsigned int nbExemplaires,
         const string &realisateur, vector<string> vActeurs) : ObjetEmpruntable(cote, titre, annee, ageMin, nbExemplaires), realisateur_(realisateur), vActeurs_(vActeurs){
}

bool Dvd::rechercher(const string &motCle) {
	//On convertit en minuscules le mot entre en parametre et les infos des DVDs afin de faciliter la recherhe.
    bool dvdTrouve = convertirMinuscule(realisateur_).find(convertirMinuscule(motCle)) != string::npos || ObjetEmpruntable::rechercher(motCle);
    for(unsigned int i = 0; i < vActeurs_.size() && !dvdTrouve; i++){
        if(convertirMinuscule(vActeurs_[i]).find(convertirMinuscule(motCle)) != string::npos){
            dvdTrouve = true;
        }
    }
    return dvdTrouve;
}

string Dvd::obtenirRealisateur() const {
    return realisateur_;
}

void Dvd::setRealisateur(const string &realisateur) {
    realisateur_ = realisateur;
}

void Dvd::addActor(const string &actor) {
    vActeurs_.push_back(actor);
}

bool Dvd::rmvActor(const string &actor) {
    bool acteurEnleve = false;
    for(unsigned int i = 0; i < vActeurs_.size(); i++){			//On inclut le cas ou l'acteur a enlever du vecteur est dans le milieu de celui-ci.
        if(vActeurs_[i] == actor){
            acteurEnleve = true;
        }
        if(acteurEnleve && i < vActeurs_.size() - 1){
            vActeurs_[i] = vActeurs_[i + 1];
        }
        if(acteurEnleve && i == vActeurs_.size() - 1){
            vActeurs_.pop_back();
        }
    }
    return acteurEnleve;
}

vector<string> Dvd::getVActor() const {
    return vActeurs_;
}

std::string Dvd::getType() const {
    return "DVD";
}

ostream &operator<<(ostream &o, const Dvd &dvd) {
    o << "Information sur le Dvd: " << endl << static_cast<const ObjetEmpruntable&>(dvd) /* operateur << de ObjetEmpruntale */ <<
            " Realisateur : " << dvd.realisateur_ << "; Acteurs : ";
    for(unsigned int i = 0; i < dvd.vActeurs_.size(); i++){
        o << dvd.vActeurs_[i] << "; ";
    }
    o << endl;
    return o;
}
