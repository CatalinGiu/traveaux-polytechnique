/*
Fichier: Dvd.cpp
Auteur(s): Julien Gauthier, Catalin Giurca
Date de creation: 10 mars 2016
Date de modification: 29 mars 2016
Description: Initialisation des fonctions de la Classe Dvd
*/

#include "Dvd.h"
#include <iterator>

using namespace std;

Dvd::Dvd()
{
}
//Le constructeur par parametres utilise le constructeur de ObjetEmpruntable 
//pour cote, titre, annee, ageMin et nbExemplaires
Dvd::Dvd(const std::string & cote, const std::string & titre, unsigned int annee, unsigned int ageMin,
	unsigned int nbExemplaires, std::string const & realisateur, std::list<std::string> acteurs) :
	ObjetEmpruntable(cote, titre, annee, ageMin, nbExemplaires), realisateur_(realisateur), listeActeurs_(acteurs)
{
}


Dvd::~Dvd()
{
}

std::string Dvd::obtenirRealisateur() const
{
	return realisateur_;
}

std::list<std::string> Dvd::obtenirActeur() const
{
	return listeActeurs_;
}

void Dvd::modifierRealisateur(std::string const & realisateur)
{
	realisateur_ = realisateur;
}

void Dvd::ajouterActeur(std::string const & acteur)
{
	listeActeurs_.push_back(acteur);
}

void Dvd::retirerActeur(std::string const & acteur)
{
	unsigned int taille = listeActeurs_.size();
	listeActeurs_.remove(acteur);
}


bool Dvd::recherche(const std::string & motsCle) const
{
	bool present = false;
	std::size_t trouverRealisateur = convertirMinuscule(realisateur_).find(convertirMinuscule(motsCle));
	for (unsigned int i = 0; i < listeActeurs_.size(); i++)
	{
		bool trouveActeur = false;
		for(list<string>::const_iterator it = listeActeurs_.begin(); it != listeActeurs_.end() && !trouveActeur; it++){
			if(convertirMinuscule(*it) == convertirMinuscule(motsCle)){
				trouveActeur = true;
			}
		}
		present = present || (trouveActeur);
	}
	//Utilisation du demasquage pour appeler la methode de la classe mere
	bool trouve = ObjetEmpruntable::recherche(motsCle) 
		|| present
		|| (trouverRealisateur != string::npos);

	return trouve;
}

ostream & operator<<(ostream & o, Dvd & dvd)
{
	const ObjetEmpruntable* obj = (&dvd);
	o << "Information sur le Dvd :" << endl;
	o << *obj
		<< " Realisateur : " << dvd.realisateur_
		<< "; Acteurs : ";
	//affichage des acteurs
	dvd.listeActeurs_.sort();
	copy(dvd.listeActeurs_.rbegin(), dvd.listeActeurs_.rend(), ostream_iterator<string>(o, "; "));

	return o << endl;
}
