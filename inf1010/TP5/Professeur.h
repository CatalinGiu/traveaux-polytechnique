/*
Fichier: Professeur.h
Auteur(s): Julien Gauthier, Catalin Giurca
Date de creation: 10 mars 2016
Date de modification: 29 mars 2016
Description: Initialisation des fonctions de la Classe Professeur
*/
#ifndef PROFESSEUR_H
#define PROFESSEUR_H


#include "Abonne.h"
#include <list>

class Professeur :	//La classe Professeur est derivee de la classe Abonne
	public Abonne
{
public:
	//Constructeurs par defaut et par parametres, destructeur
	Professeur();
	Professeur(const std::string& matricule, const std::string& nom, const std::string& prenom, unsigned int age, std::list<std::string> ecoles);
	~Professeur();

	std::list<std::string> obtenirEcole() const;			//Methode d'acces a la liste d'ecoles
	void ajouterEcole(std::string const& ecole);			//Methodes d'ajout et de retrait d'un ecole dans la liste 
	bool retirerEcole(std::string const& ecole);
	virtual unsigned int obtenirLimiteEmprunt() const;		//Methode d'acces a la limite d'emprunt d'un professeur (virtuelle 
															//pour se dissocier de la limite d'emprunts d'un abonne normal).
	
	//Operateur d'affichage, trie des acteurs en ordre alphabétique inverse
	friend std::ostream & operator<<(std::ostream & o, Professeur & professeur);

private:
	
	std::list<std::string> listeEcole_;			//Liste de string qui contient les ecoles
};
#endif // !PROFESSEUR_H
