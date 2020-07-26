/*
Fichier: LivreNumerique.h
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 25 fevrier 2016
Date de modification: 28 fevrier 2016
Description: Initialisation des fonctions de la Classe LivreNumerique
*/
#ifndef LIVRENUMERIQUE_H
#define LIVRENUMERIQUE_H


#include "ObjetNumerique.h"
#include "Livre.h"
#include <string>
#include <iostream>


/* Enumeration pour les types de documents possibles
- FORMAT_PDF:		Le format du livre est en "pdf"
- FORMAT_EPUB:		Le format du livre est en "epub"
- FORMAT_DOCX:		Le format du livre est en "docx"
- FORMAT_TXT:		Le format du livre est en "txt"
- FORMAT_INCONNU :	Le format du livre est inconnu
*/
enum FORMAT_DOCUMENT
{
	FORMAT_PDF		= 0,
	FORMAT_EPUB		= 1,
	FORMAT_DOCX		= 2,
	FORMAT_TXT		= 3,
	FORMAT_INCONNU	= 4,
};


//LivreNumerique est une classe derivee des classes ObjetNumerique et Livre
class LivreNumerique :	public ObjetNumerique, public Livre
{
public:
	LivreNumerique();			//constructeurs par defaut et par parametres
	LivreNumerique(FORMAT_DOCUMENT format, unsigned int taille, std::string lien,
					const std::string& cote, const std::string& titre, unsigned int annee,
				   unsigned int ageMin, unsigned int nbExemplaires, const std::string& auteur, const std::string& genre);
	~LivreNumerique();			//destructeur

	std::string obtenirFormat() const;		//methodes d'acces aux attributs
	unsigned int obtenirTaille() const;
	std::string obtenirLien() const;

	void setFormat(FORMAT_DOCUMENT format);		//methodes de modification des attributs
	void setTaille(unsigned int taille);
	void setLien(const std::string& lien);

	bool recherche(const std::string& mot) const;		//Recherche un livre numerique avec un mot

	friend std::ostream&operator<<(std::ostream& os,const LivreNumerique& livreNum);		//operateur de sortie pour un livre numerique



private:
	FORMAT_DOCUMENT format_;
	unsigned int tailleOctet_;
	std::string lien_;

};


#endif // LIVRENUMERIQUE_H
