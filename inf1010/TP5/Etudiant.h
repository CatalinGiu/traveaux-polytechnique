/*
Fichier: Etudiant.h
Auteur(s): Julien Gauthier, Catalin Giurca
Date de creation: 10 mars 2016
Date de modification: 29 mars 2016
Description: Initialisation des fonctions de la Classe Etudiant
*/

#ifndef ETUDIANT_H
#define ETUDIANT_H
#include "Abonne.h"

//La classe Etudiant reste inchangee du TP4

//Etudiant est derivee de la classe Abonne
class Etudiant :
	public Abonne
{
public:
	Etudiant();
	Etudiant(const std::string& matricule, const std::string& nom, const std::string& prenom, unsigned int age, const std::string& ecole);
	~Etudiant();

	std::string obtenirEcole() const;
	void modifierEcole(const std::string& ecole);
	virtual unsigned int obtenirLimiteEmprunt() const;		//Virtuelle pour que chaque classe derivee ait sa propre limite d'emprunts

	friend std::ostream & operator<<(std::ostream & o, const Etudiant & etudiant);

private :
	std::string ecole_;
};

#endif