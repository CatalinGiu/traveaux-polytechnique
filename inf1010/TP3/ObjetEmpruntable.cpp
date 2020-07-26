/*
Fichier: ObjetEmpruntable.cpp
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 11 fevrier 2016
Date de modification: 21 fevrier 2016
Description: Initialisation des fonctions de la Classe ObjetEmpruntable
*/

#include <iostream>
#include <algorithm>
#include "ObjetEmpruntable.h"

using namespace std;

//Les methodes de construction, de destruction, d'acces, de modification sont et les operateurs sont decrites dans ObjetEmpruntbale.h

ObjetEmpruntable::ObjetEmpruntable()
	: nbExemplaires_(0), nbDisponibles_(0), ageMinimal_(0)			//les attributs par defaut prennent la valeur de 0
{

}

ObjetEmpruntable::ObjetEmpruntable(const string& cote, const string& titre, unsigned int annee, unsigned int ageMin, unsigned int nbExemplaires)
	: cote_(cote), titre_(titre), annee_(annee), ageMinimal_(ageMin), nbExemplaires_(nbExemplaires), nbDisponibles_(nbExemplaires)
{

}
ObjetEmpruntable::~ObjetEmpruntable()
{

}

string ObjetEmpruntable::obtenirCote() const
{
	return cote_;
}

string ObjetEmpruntable::obtenirTitre() const
{
	return titre_;
}

unsigned int ObjetEmpruntable::obtenirAnnee() const
{
	return annee_;
}

unsigned int ObjetEmpruntable::obtenirAgeMinimal() const
{
	return ageMinimal_;
}

unsigned int ObjetEmpruntable::obtenirNbExemplaires() const
{
	return nbExemplaires_;
}

unsigned int ObjetEmpruntable::obtenirNbDisponibles() const
{
	return nbDisponibles_;
}

// Converti une phrase en minuscule
std::string ObjetEmpruntable::convertirMinuscule(const std::string & phrase) const
{
	string phraseRetour = phrase;
	std::transform(phrase.begin(), phrase.end(), phraseRetour.begin(), ::tolower);
	return phraseRetour;
}

void ObjetEmpruntable::modifierNbExemplaires(unsigned int nbExemplaires)
{
	nbExemplaires_ = nbExemplaires;
}

void ObjetEmpruntable::modifierNbDisponibles(unsigned int nbDisponibles)
{
	nbDisponibles_ = nbDisponibles;
}

void ObjetEmpruntable::modifierTitre(const std::string & titre)
{
	titre_ = titre;
}

void ObjetEmpruntable::modifierCote(const std::string & cote)
{
	cote_ = cote;
}

void ObjetEmpruntable::modifierAnnee(unsigned int annee)
{
	annee_ = annee;
}


bool ObjetEmpruntable::operator==(const ObjetEmpruntable & objetEmpruntable) const
{
	return
		(titre_ == objetEmpruntable.titre_) &&
		(cote_ == objetEmpruntable.cote_);
}

bool ObjetEmpruntable::operator==(const std::string & cote) const
{
	return cote_ == cote;
}

bool operator==(const std::string & cote, const ObjetEmpruntable & objetEmpruntable)
{
	return objetEmpruntable == cote;
}

bool ObjetEmpruntable::operator<(const ObjetEmpruntable & objetEmpruntable) const
{
	return titre_ < objetEmpruntable.titre_;
}

// Recherche les informations d'un objetEmpruntable a partir d'un mot cle
bool ObjetEmpruntable::rechercher(const std::string & motsCle) const
{
	std::size_t trouveTitre = convertirMinuscule(titre_).find(convertirMinuscule(motsCle));
	std::size_t trouveCote = convertirMinuscule(cote_).find(convertirMinuscule(motsCle));

	bool estTrouve =
		(trouveTitre != string::npos) ||
		(trouveCote != string::npos);

	return estTrouve;
}

std::ostream & operator<<(std::ostream & o, const ObjetEmpruntable & objetEmpruntable)
{
	return o << 
		objetEmpruntable.cote_ << ". " <<
		objetEmpruntable.titre_ << ". " <<
		objetEmpruntable.annee_ << ". " <<
		objetEmpruntable.ageMinimal_ << " ans et plus.";
}

std::string ObjetEmpruntable::getType() const {
	return "ObjetEmpruntable";
}
