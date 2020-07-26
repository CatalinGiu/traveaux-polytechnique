/*
Fichier: Etudiant.h
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 25 fevrier 2016
Date de modification: 28 fevrier 2016
Description: Initialisation des fonctions de la Classe Etudiant
*/
#ifndef ETUDIANT_H
#define ETUDIANT_H
#include "Abonne.h"

class Etudiant :			//Etudiant est une classe derivee d'Abonne
	public Abonne
{
public:
	Etudiant();			//constructeurs par defaut et par parametres
	Etudiant(const std::string& matricule, const std::string& nom, const std::string& prenom, unsigned int age, const std::string& ecole);
	~Etudiant();		//destructeur

	std::string obtenirEcole() const;					//methodes d'acces et de modification de l'attribut
	void modifierEcole(const std::string& ecole);
	unsigned int obtenirLimiteEmprunt() const;			//Etudiant herite de la methode obtenirLimiteEmprunt() de Abonne, mais les deux
														//sont differentes.
	friend std::ostream & operator<<(std::ostream & o, const Etudiant & etudiant);		//operateur de sortie pour un etudiant

private :
	std::string ecole_;
};

#endif