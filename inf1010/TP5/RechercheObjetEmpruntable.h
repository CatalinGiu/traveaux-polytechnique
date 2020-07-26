/*
Fichier: RechercheObjetEmpruntable.h
Auteur(s): Julien Gauthier, Catalin Giurca
Date de creation: 10 mars 2016
Date de modification: 29 mars 2016
Description: Foncteur qui recherche un mot (string) dans la liste des objets empruntables
*/

#ifndef TP5_RECHERCHEOBJETEMPRUNTABLE_H
#define TP5_RECHERCHEOBJETEMPRUNTABLE_H

#include <string>
#include "ObjetEmpruntable.h"

class RechercheObjetEmpruntable{
public:
    RechercheObjetEmpruntable(const std::string mot);
    bool operator()(ObjetEmpruntable* objetEmpruntable);
private:
    std::string mot_;
};

RechercheObjetEmpruntable::RechercheObjetEmpruntable(const std::string mot) : mot_(mot){
}
//Retourne true si l'attribut mot_ a ete trouvee dans les objets empruntables
bool RechercheObjetEmpruntable::operator()(ObjetEmpruntable *objetEmpruntable) {
    return objetEmpruntable->recherche(mot_);
}
#endif //TP5_RECHERCHEOBJETEMPRUNTABLE_H
