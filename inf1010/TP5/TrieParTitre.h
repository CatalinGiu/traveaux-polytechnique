/*
Fichier: TrieParTitre.h
Auteur(s): Julien Gauthier, Catalin Giurca
Date de creation: 10 mars 2016
Date de modification: 29 mars 2016
Description: Foncteur qui compare les titres de deux objets empruntables
*/

#ifndef TP5_TRIEPARTITRE_H
#define TP5_TRIEPARTITRE_H


#include "ObjetEmpruntable.h"

class TrieParTitre{
public:
    TrieParTitre();
    bool operator()( ObjetEmpruntable* obj1, ObjetEmpruntable* obj2) const;
	
};

TrieParTitre::TrieParTitre() {
}
//Operateur qui retourne true si le titre du premier objet vient avant (ordre alphabetique) celui du 2e
bool TrieParTitre::operator()(ObjetEmpruntable* obj1, ObjetEmpruntable* obj2) const{
    return *obj1 < *obj2;
}

#endif //TP5_TRIEPARTITRE_H
