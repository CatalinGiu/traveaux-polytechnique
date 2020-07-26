/*
Fichier: Professeur.cpp
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 11 fevrier 2016
Date de modification: 21 fevrier 2016
Description: Initialisation des fonctions de la Classe Professeur
*/


#include "Professeur.h"

//Toutes les methodes sont decrites dans Professeur.h

Professeur::Professeur() {

}

Professeur::~Professeur() {

}

Professeur::Professeur(const string &matricule, const string &nom, const string &prenom, unsigned int age,
                       vector<string> vEcoles) : Abonne(matricule, nom, prenom, age), vEcoles_(vEcoles) {
}

vector<string> Professeur::obtenirVEcoles() const {
    return vEcoles_;
}

void Professeur::ajouterEcole(const string &ecole) {
    vEcoles_.push_back(ecole);
}


bool Professeur::retirerEcole(const string &ecole) {
    bool ecoleRetiree = false;

    for(unsigned int i = 0; i < vEcoles_.size() ; i++){			//On prend en compte le cas ou l'ecole a retirer du vecteur est au milieu de celui-ci.
        if(vEcoles_[i] == ecole){
            ecoleRetiree = true;
        }
        if(ecoleRetiree && i < vEcoles_.size() - 1){
            vEcoles_[i] = vEcoles_[i + 1];
        }
        if(ecoleRetiree && i == vEcoles_.size() - 1){
            vEcoles_.pop_back();
        }
    }
    //
    return ecoleRetiree;
}

unsigned int Professeur::obtenirLimiteEmprunts() const{			//Un professeur peut emprunter un nombre illimite de livres/DVDs.
    return vEcoles_.size() * LIMITE_EMPRUNTS;
}

ostream &operator<<(ostream &o, const Professeur &professeur) {
    o << static_cast<const Abonne&>(professeur) /* Operateur  << de abonne */ << "LISTE DES ECOLES : ";

    for(unsigned int i = 0; i < professeur.vEcoles_.size() ; i++){
        o << professeur.vEcoles_[i] << "; ";
    }

    o << "Limite d'emprunts :" << professeur.obtenirLimiteEmprunts() << endl;
    return o;
}