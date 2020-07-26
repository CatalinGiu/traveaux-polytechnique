/*
Fichier: Abonne.h
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 25 fevrier 2016
Date de modification: 28 fevrier 2016
Description: Initialisation des fonctions de la Classe Abonne
*/
#ifndef ABONNE_H
#define ABONNE_H

#include <string>
#include "Emprunt.h"
#include "ObjetEmpruntable.h"
#include <vector>
#include <iostream>

#define LIMITE_EMPRUNTS 2

class Abonne
{
public:

	/// TP4
	std::string obtenirNomClasse() const;			//methode d'obtention du nom de la classe (etudiant, professeur, etc)


	/// TP3
	//Constructeurs par defaut et par parametres
	Abonne();
	Abonne(const std::string& matricule, const std::string& nom, const std::string& prenom, unsigned int age);

	~Abonne();		//destructeur

	std::string obtenirMatricule() const;	//methodes d'acces
	std::string obtenirNom() const;
	std::string obtenirPrenom() const;
	unsigned int obtenirAge() const;

	void modifierMatricule(const std::string& matricule);		//methodes de modification
	void modifierNom(const std::string& nom);	
	void modifierPrenom(const std::string& prenom);
	void modifierAge(unsigned int age);

	std::vector<Emprunt*> obtenirEmprunts() const;				//methode d'acces au vecteur d'emprunts

	unsigned int obtenirNombreEmprunte() const;									
	friend std::ostream& operator<<(std::ostream& o, const Abonne& abonne);			//operateurs d'affichage (<<) et de comparaison (==)
	bool operator==(const Abonne& abonne) const;
	bool operator==(const std::string& matricule) const;
	friend bool operator==(const std::string& matricule, const Abonne& abonne);

	/// ____TP3_____
	virtual unsigned int obtenirLimiteEmprunt() const;						//methode d'obtention de la limite d'emprunt de l'abonne.
																			//Elle est virtuelle pour que chacune des classes derivees aillent
																			//leur propre limite d'emprunts.
	bool estEmprunte(const ObjetEmpruntable& objetEmpruntable) const;		//methode de verification d'un emprunt fait
	void ajouterEmprunt(Emprunt * emprunt);									//methodes de modification de la liste d'emprunts
	bool retirerEmprunt(ObjetEmpruntable * objetEmpruntable);

private:
	std::string matricule_;
	std::string nom_;
	std::string prenom_;
	unsigned int age_;
	std::vector<Emprunt*> vecEmprunts_;

	/// ____TP3_____
	unsigned int limiteEmprunt_;

};

	
#endif
