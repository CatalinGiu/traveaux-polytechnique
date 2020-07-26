/*
Fichier: ObjetNumerique.h
Auteur(s): Julien Gauthier, Catalin Giurca
Date de creation: 10 mars 2016
Date de modification: 29 mars 2016
Description: Initialisation des fonctions de la Classe ObjetNumerique
*/
#ifndef	OBJETNUMERIQUE_H
#define OBJETNUMERIQUE_H



#include <string>
#include <iostream>

//La classe ObjetNumerique reste inchangee du TP4
class ObjetNumerique
{
public:

	virtual ~ObjetNumerique() {};

	virtual void modifierTaille(unsigned int tailleOctet) = 0;
	virtual unsigned int obtenirTaille( ) const = 0;
	virtual void modifierLien(std::string lien) = 0;
	virtual std::string obtenirLien() const = 0;
	
};



#endif

