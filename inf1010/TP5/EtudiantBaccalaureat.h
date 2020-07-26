/*
Fichier: EtudiantBaccalaureat.h
Auteur(s): Julien Gauthier, Catalin Giurca
Date de creation: 10 mars 2016
Date de modification: 29 mars 2016
Description: Initialisation des fonctions de la Classe EtudiantBaccaLaureat
*/

#ifndef ETUDIANTBACCALAUREAT_H
#define ETUDIANTBACCALAUREAT_H
#include "Etudiant.h"

//La classe EtudiantBaccalaureat demeure pareil a celle du TP4

//EtudiantBaccalaureat est derivee de al classe Etudiant
class EtudiantBaccalaureat : public Etudiant
{
public:

	EtudiantBaccalaureat(const std::string& matricule, const std::string& nom, const std::string& prenom, unsigned int age);
	virtual unsigned int obtenirLimiteEmprunt() const;

};
#endif