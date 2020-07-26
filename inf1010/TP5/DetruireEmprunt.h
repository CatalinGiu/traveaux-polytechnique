/*
Fichier: DetruireEmprunt.h
Auteur(s): Julien Gauthier, Catalin Giurca
Date de creation: 10 mars 2016
Date de modification: 29 mars 2016
Description: Foncteur qui detruit tous les emprunts de la Bibliotheque contenus dans 
le gestionnaire d'emprunts.
*/

#ifndef TP5_DETRUIREEMPRUNT_H
#define TP5_DETRUIREEMPRUNT_H

#include "Emprunt.h"

class DetruireEmprunt{
public:
	DetruireEmprunt();
    void operator()(Emprunt* emprunt);
};

DetruireEmprunt::DetruireEmprunt() {
}
//Operateur qui detruit les emprunts.
void DetruireEmprunt::operator()(Emprunt *emprunt) {
    delete emprunt;
}

#endif //TP5_DETRUIREEMPRUNT_H
