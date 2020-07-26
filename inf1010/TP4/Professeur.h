/*
Fichier: Professeur.h
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 25 fevrier 2016
Date de modification: 28 fevrier 2016
Description: Initialisation des fonctions de la Classe Professeur
*/
#ifndef PROFESSEUR_H
#define PROFESSEUR_H


#include "Abonne.h"
class Professeur :			//Professeur est une classe derivee d'Abonne
	public Abonne
{
public:
	Professeur();		//constructeurs par defaut et par parametres
	Professeur(const std::string& matricule, const std::string& nom, const std::string& prenom, unsigned int age, std::vector<std::string> ecoles);
	~Professeur();		//destructeur

	std::vector<std::string> obtenirEcole() const;		//methode d'acces et de modification du vecteur d'ecoles
	void ajouterEcole(std::string const& ecole);
	bool retirerEcole(std::string const& ecole);
	unsigned int obtenirLimiteEmprunt() const;			//Professeur herite de la methode obtenirLimiteEmprunt() de Abonne, mais les deux
														//methodes sont differentes.
	friend std::ostream & operator<<(std::ostream & o, const Professeur & professeur);	//operateur de sortie pour un professeur

private:
	std::vector<std::string> vecEcole_;
};
#endif // !PROFESSEUR_H
