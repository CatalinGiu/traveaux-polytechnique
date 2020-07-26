/*
Fichier: Empruntable.h
Auteur(s): Julien Gauthier, Catalin Giurca
Date de creation: 10 mars 2016
Date de modification: 29 mars 2016
Description: Foncteur qui compte les emprunts d'un abonne et verifie qu'un objet n'a pas
deja ete emprunte.
*/

#ifndef TP5_EMPRUNTABLE_H
#define TP5_EMPRUNTABLE_H

#include "Emprunt.h"
#include <string>

class Empruntable{
public:
	//Constructeur par parametres
    Empruntable(const std::string matricule, const std::string cote, unsigned int& compteur, bool& estEmpruntable);
    bool operator()(Emprunt* emprunt);


private:
    std::string matricule_;		//Empruntable possede comme attributs le matricule de l'abonne  
    std::string cote_;			//et la cote de l'objet en question,

    unsigned int* compteur_;	//ainsi qu'un compteur d'emprunts et un booleen.
    bool* estEmpruntable_;

};

Empruntable::Empruntable(const std::string matricule, const std::string cote, unsigned int& compteur,
                         bool& estEmpruntable) : matricule_(matricule), cote_(cote), compteur_(&compteur), estEmpruntable_(&estEmpruntable){
}

//Operateur responsable de la fonction du foncteur
bool Empruntable::operator()(Emprunt *emprunt) {					//Prend un emprunt en parametre
    if(*estEmpruntable_) {												
        if (*emprunt == matricule_) {								//Verifie que l'emprunt apparatient a l'abonne en question

            (*compteur_)++;											//Incremente le nombre d'emprunts

            if (cote_ == *(emprunt->obtenirObjetEmpruntable() )) {	//Verifie si l'objet en question est deja emprunte
                *estEmpruntable_ = false;							//Retourne false si l'emprunt est deja fait
            }
        }
    }
    return *estEmpruntable_;										//Retourne true si l'emprunt est faisable

}

#endif //TP5_EMPRUNTABLE_H

