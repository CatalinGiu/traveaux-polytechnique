/*
Fichier: EtudiantBaccalaureat.h
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 25 fevrier 2016
Date de modification: 28 fevrier 2016
Description: Initialisation des fonctions de la Classe EtudiantBaccalaureat
*/
#ifndef ETUDIANTBACCALAUREAT_H
#define ETUDIANTBACCALAUREAT_H
#include "Etudiant.h"

class EtudiantBaccalaureat : public Etudiant		//EtudiantBaccalaureat est une classe derivee de Etudiant
{
public:
	//constructeur par parametres
	EtudiantBaccalaureat(const std::string& matricule, const std::string& nom, const std::string& prenom, unsigned int age);
	unsigned int obtenirLimiteEmprunt() const;

};
#endif