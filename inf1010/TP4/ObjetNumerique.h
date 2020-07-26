/*
Fichier: ObjetNumerique.h
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 25 fevrier 2016
Date de modification: 28 fevrier 2016
Description: Initialisation des fonctions de la Classe ObjetNumerique
*/
#ifndef	OBJETNUMERIQUE_H
#define OBJETNUMERIQUE_H

#include <string>



class ObjetNumerique			//ObjetNumerique est une classe abstraite, donc possede des methodes virtuelles pures.
{
public:
    ObjetNumerique();									//constructeur par defaut
    virtual unsigned int obtenirTaille() const = 0;		//Methodes virtuelles pures
    virtual std::string obtenirLien() const = 0;
    virtual ~ObjetNumerique();
	
	
	
	
};



#endif

