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
    Bibliotheque();				//constructeur par d�faut
    ~Bibliotheque();			//destructeur

    Abonne* trouverAbonne(const string& matricule) const;					//trouve un abonn� selon un matricule
    ObjetEmpruntable* trouverObjetEmpruntable(const string& cote) const;	//trouve un objet empruntable selon une cote

    string ObtenirClasseObjet(const string& cote) const;					//Acc�s � la classe d'un objet empruntable selon une cote

    bool ajouterAbonne(Abonne* abonne);				//ajoute un abonn� au vecteur d'abonn�s si celui-ci existe
    bool retirerAbonne(const string& matricule);	//Retire un abonn� du vecteur d'abonn�s si celui-ci en faisait partie
					
    bool ajouterLivre(Livre* livre);				//Ajoute un livre au vecteur de livres si le livre existe
    bool ajouterDVD(Dvd* dvd);						//Ajoute un DVD au vecteur de DVDs si le DVD existe

    bool retirerObjetEmpruntable(const string& cote);		//retire un objet empruntable de son vecteur (livre ou DVD)
    void rechercher(const string& mot) const;				//Recherche un objet empruntable (livre ou DVD) selon un string

    bool estEmpruntable(const string& matricule, const ObjetEmpruntable& objetEmpruntable) const;
	//v�rifie qu'un objet est empruntable
    bool emprunter(const string& matricule, const string& cote, unsigned int retour);
	//ajoute un emprunt � la liste d'emprunts si l'objet est empruntable. Retourne true si l'emprunt est fait.

    bool retourner(const string& matricule, const string& cote);		//Retourne un objet emprunt�. Retourne true si le retour est fait.
    void enleverEmprunt(unsigned int pos);								//m�thode utile pour retirer un emprunt suite � un retour

    void infoAbonne(const string& matricule) const ;		//acc�s aux infos d'un abonn� selon un matricule

    friend istream& operator>>(istream& i, const Bibliotheque& bibliotheque);	//op�rateur d'entr�e qui prend un mot et utilise une m�thode
																				//de recherche d'objet dans la biblioth�que
    void operator+=(Abonne& abonne);		//op�rateur pour ajouter un abonn�
    void operator+=(Livre& livre);			//op�rateur pour ajouter un livre
    void operator+=(Dvd& dvd);				//oprateur pour ajouter un DVD

    void operator-=(Abonne& abonne);						//op�rateur pour retirer un abonn�
    void operator-=(ObjetEmpruntable& objetEmpruntable);	//op�rateur pour retirer un objet empruntable (livre ou DVD)


private:
    vector<Abonne*> vAbonnes_;
    vector<Livre*> vLivres_;
    vector<Dvd*> vDvd_;
    vector<Emprunt*> vEmprunts_;

};

#endif //TP3_INF1010_BIBLIOTHEQUE_H
