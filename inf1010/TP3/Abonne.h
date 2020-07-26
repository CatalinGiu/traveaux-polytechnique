/*
Fichier: Abonne.h
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 11 fevrier 2016
Date de modification: 21 fevrier 2016
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
using namespace std;
class Abonne
{
public:

	Abonne();
	//constructeur par defaut
	Abonne(const std::string& matricule, const std::string& nom, const std::string& prenom, unsigned int age);
	//constructeur par parametres
	~Abonne();
	//destructeur

	std::string obtenirMatricule() const;						//méthodes d'accès des attributs
	std::string obtenirNom() const;								
	std::string obtenirPrenom() const;					
	unsigned int obtenirAge() const;						
	std::vector<Emprunt*> obtenirEmprunts() const;				

	void modifierMatricule(const std::string& matricule);		//méthodes de modification des attributs
	void modifierNom(const std::string& nom);
	void modifierPrenom(const std::string& prenom);
	void modifierAge(unsigned int age);

	void ajouterEmprunt(Emprunt * emprunt);						//méthode d'ajout d'un emprunt dans le vecteur d'emprunts
	unsigned int obtenirNombreEmprunte() const;					//méthode d'accès au nombre d'emprunts

	friend std::ostream& operator<<(std::ostream& o, const Abonne& abonne);		//opérateur de sortie 
	bool operator==(const Abonne& abonne) const;								//compare les attributs de deux abonnés 
	bool operator==(const std::string& matricule) const;						//compare les matricules de deux abonnés
	friend bool operator==(const std::string& matricule, const Abonne& abonne);	//fait Abonne==matricule

	unsigned int obtenirLimiteEmprunts() const;							//méthode virtual pour l'accès à la limite d'emprunts
	bool estEmprunte(const string& cote) const;					//vérifie si un objet est emprunté, selon sa cote

	void enleverEmprunt(unsigned int pos);								//méthode non demandée qui permet de retirer dans
																		//la liste d'emprunts, même au milieu du vecteur
	void retirerEmprunt(const ObjetEmpruntable& objetEmpruntable);		//méthode qui retire un objet de la liste d'emprunt


private:
	std::string matricule_;
	std::string nom_;
	std::string prenom_;
	unsigned int age_;
	std::vector<Emprunt*> vecEmprunts_;
	unsigned int limiteEmprunts_;

};

	
#endif
