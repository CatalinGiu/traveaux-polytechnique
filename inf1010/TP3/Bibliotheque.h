/*
Fichier: Bibliotheque.h
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 11 fevrier 2016
Date de modification: 21 fevrier 2016
Description: Initialisation des fonctions de la Classe Bibliotheque
*/


#ifndef TP3_INF1010_BIBLIOTHEQUE_H
#define TP3_INF1010_BIBLIOTHEQUE_H

#include <vector>
#include "Abonne.h"

using namespace std;

class Bibliotheque {
public:
    Bibliotheque();				//constructeur par défaut
    ~Bibliotheque();			//destructeur

    Abonne* trouverAbonne(const string& matricule) const;					//trouve un abonné selon un matricule
    ObjetEmpruntable* trouverObjetEmpruntable(const string& cote) const;	//trouve un objet empruntable selon une cote

    string ObtenirClasseObjet(const string& cote) const;					//Accès à la classe d'un objet empruntable selon une cote

    bool ajouterAbonne(Abonne* abonne);				//ajoute un abonné au vecteur d'abonnés si celui-ci existe
    bool retirerAbonne(const string& matricule);	//Retire un abonné du vecteur d'abonnés si celui-ci en faisait partie
					
    bool ajouterLivre(Livre* livre);				//Ajoute un livre au vecteur de livres si le livre existe
    bool ajouterDVD(Dvd* dvd);						//Ajoute un DVD au vecteur de DVDs si le DVD existe

    bool retirerObjetEmpruntable(const string& cote);		//retire un objet empruntable de son vecteur (livre ou DVD)
    void rechercher(const string& mot) const;				//Recherche un objet empruntable (livre ou DVD) selon un string

    bool estEmpruntable(const string& matricule, const ObjetEmpruntable& objetEmpruntable) const;
	//vérifie qu'un objet est empruntable
    bool emprunter(const string& matricule, const string& cote, unsigned int retour);
	//ajoute un emprunt à la liste d'emprunts si l'objet est empruntable. Retourne true si l'emprunt est fait.

    bool retourner(const string& matricule, const string& cote);		//Retourne un objet emprunté. Retourne true si le retour est fait.
    void enleverEmprunt(unsigned int pos);								//méthode utile pour retirer un emprunt suite à un retour

    void infoAbonne(const string& matricule) const ;		//accès aux infos d'un abonné selon un matricule

    friend istream& operator>>(istream& i, const Bibliotheque& bibliotheque);	//opérateur d'entrée qui prend un mot et utilise une méthode
																				//de recherche d'objet dans la bibliothèque
    void operator+=(Abonne& abonne);		//opérateur pour ajouter un abonné
    void operator+=(Livre& livre);			//opérateur pour ajouter un livre
    void operator+=(Dvd& dvd);				//oprateur pour ajouter un DVD

    void operator-=(Abonne& abonne);						//opérateur pour retirer un abonné
    void operator-=(ObjetEmpruntable& objetEmpruntable);	//opérateur pour retirer un objet empruntable (livre ou DVD)


private:
    vector<Abonne*> vAbonnes_;
    vector<Livre*> vLivres_;
    vector<Dvd*> vDvd_;
    vector<Emprunt*> vEmprunts_;

};

#endif //TP3_INF1010_BIBLIOTHEQUE_H
