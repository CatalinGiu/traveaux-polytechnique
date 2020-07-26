/*
Fichier: ObjetEmpruntable.cpp
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 25 fevrier 2016
Date de modification: 28 fevrier 2016
Description: Initialisation des fonctions de la Classe ObjetEmpruntable
*/
#include <iostream>
#include <algorithm>
#include "ObjetEmpruntable.h"
#include "Livre.h"
#include "LivreNumerique.h"
#include "Dvd.h"

using namespace std;




ObjetEmpruntable::ObjetEmpruntable()
	: nbExemplaires_(0), nbDisponibles_(0), ageMinimal_(0)
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

std::string ObjetEmpruntable::obtenirNomClasse() const
{
	if (this != nullptr)
	{
		return typeid(*this).name();
	}
	else
	{
		return "nullptr";
	}
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
	if (nbExemplaires >= nbExemplaires_)
		nbExemplaires_ = nbExemplaires;
	else
	{
		if (nbExemplaires - nbDisponibles_ >= 0)
		{
			nbExemplaires_ = nbExemplaires;
			nbDisponibles_ -= nbExemplaires;
		}
		else
		{
			cout << "Il n'y a pas assez d'exemplaires disponibles pour en supprimer ! " << endl;
		}
	}
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

// Recherche les informations d'un objetEmpruntable � partir d'un mot cl�
bool ObjetEmpruntable::recherche(const std::string & motsCle) const
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

void ObjetEmpruntable::afficherObjetEmpruntable(std::ostream &os) const {
	if(obtenirNomClasse().find("LivreNumerique") != string::npos)
		os << dynamic_cast<const LivreNumerique&>(*this);					//utilisation de dynamic_cast pour convertir les classes derivees 
	else if(obtenirNomClasse().find("Livre") != string::npos)				//d'ObjetEmpruntable en une autre classe de l'heritage (en ObjetEmpruntable).
		os << dynamic_cast<const Livre&>(*this);
	else if(obtenirNomClasse().find("Dvd") != string::npos)
		os << dynamic_cast<const Dvd&>(*this);
}
