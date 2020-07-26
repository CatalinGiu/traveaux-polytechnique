/*
Fichier: Bibliotheque.cpp
Auteur(s): Julien Gauthier, Catalin Giurca
Date de creation: 10 mars 2016
Date de modification: 29 mars 2016
Description: la classe qui fait le lien entre toutes les autres classes
*/

#include "Bibliotheque.h"
#include "MemeObjet.h"
#include "RechercheObjetEmpruntable.h"
#include "TrieParTitre.h"
#include "Empruntable.h"
#include "EtudiantBaccalaureat.h"
#include "Professeur.h"
#include "DetruireEmprunt.h"
#include <iterator>
#include <algorithm>

using namespace std;

Bibliotheque::Bibliotheque() {

}

Bibliotheque::~Bibliotheque() {
	gestEmprunts_.retirerContenu(DetruireEmprunt());
}

Abonne *Bibliotheque::trouverAbonne(std::string &matricule) const {
    return gestAbonnes_.trouverElement(MemeObjet<string>(matricule));
}

ObjetEmpruntable *Bibliotheque::trouverObjetEmpruntable(std::string &cote) const {
    return gestObj_.trouverElement(MemeObjet<string>(cote));
}

std::string Bibliotheque::obtenirClasseObjet(std::string &cote) const {
    return trouverObjetEmpruntable(cote)->obtenirNomClasse();
}

//Toutes les methodes booleennes suivantes d'ajout et de retrait dans les gestionnaires retourenent
//true si l'operation a ete effectuee correctement, false si elle a echoue.

bool Bibliotheque::ajouterAbonne(Abonne &abonne) {
    return gestAbonnes_.ajouterElement(&abonne);
}

bool Bibliotheque::retirerAbonne(std::string &matricule) {
    if(gestEmprunts_.trouverElement(MemeObjet<string>(matricule))){
        return false;
    }

    return gestAbonnes_.retirerElement(trouverAbonne(matricule));
}

bool Bibliotheque::ajouterObjetEmpruntable(ObjetEmpruntable *objet) {
    return gestObj_.ajouterElement(objet);
}

bool Bibliotheque::retirerObjetEmpruntable(std::string &cote) {

    if(!gestObj_.trouverElement(MemeObjet<string>(cote))){
        return false;
    }

    return gestObj_.retirerElement(trouverObjetEmpruntable(cote));
}

void Bibliotheque::rechercherObjetEmpruntable(std::string &str) const {
    list<ObjetEmpruntable*> contenu = gestObj_.trouverContenu(RechercheObjetEmpruntable(str));
    if(contenu.size() != 0) {		//On verifie que le contenu a ete trouve (liste d'objets empruntables pas vide)
        contenu.sort(TrieParTitre());
        for(auto it = contenu.begin(); it != contenu.end(); it++){ //Utilisation de l'iterateur auto, le compilateur 
																	//utilise le bon type pour nous.
            cout << *(*it) << endl;
        }
    }
    else
        cout << "Aucun ouvrage avec <" << str << "> n'a ete trouve :-(";

}

bool Bibliotheque::emprunter(std::string &matricule, std::string &cote, unsigned int date) {
    unsigned int livresEmpruntes = 0;
    bool livreEmpruntable = true;
    ObjetEmpruntable* obj = trouverObjetEmpruntable(cote);
    Abonne* abonne = trouverAbonne(matricule);
    gestEmprunts_.trouverContenu(Empruntable(matricule, cote, livresEmpruntes, livreEmpruntable));
    if(livresEmpruntes < abonne->obtenirLimiteEmprunt() &&
            obj->obtenirNbDisponibles() &&
            obj->obtenirAgeMinimal() <= abonne->obtenirAge() && (livreEmpruntable)){

        obj->modifierNbDisponibles(obj->obtenirNbDisponibles() - 1);
        Emprunt* emprunt = new Emprunt(matricule, obj, date);
        livreEmpruntable = gestEmprunts_.ajouterElement(emprunt);

    }
    else
        livreEmpruntable = false;

    return livreEmpruntable;
}

bool Bibliotheque::retourner(std::string &matricule, std::string &cote) {
    pair<string, string> pairEmprunt (matricule, cote);
    Emprunt* emprunt = gestEmprunts_.trouverElement(MemeObjet<pair<string,string>>(pairEmprunt));
    if(!emprunt){
        return false;
    }
    ObjetEmpruntable* obj = trouverObjetEmpruntable(cote);
    obj->modifierNbDisponibles(obj->obtenirNbDisponibles() + 1);
    return gestEmprunts_.retirerElement(emprunt);
}

void Bibliotheque::infoAbonne(const string &matricule) const {
    //On doit v�rifier que tous les vecteurs sont parcourus
	string sMatricule = matricule;
	Abonne* ab = trouverAbonne(sMatricule);

    if (ab)
    {
        /*
         * typeid est Implementation Defined!!!
         * En travaillant sur CLion sur Ubuntu, typeid(obj).name()
         * retourne xObj, ou x est le nombre de caracteres dans le nom de
         * Obj (exemple - typeid(Professeur p).name() = 10Professeur)
         */
        if(ab->obtenirNomClasse().find("Abonne") != string::npos)
            cout << *ab << endl;
        else if (ab->obtenirNomClasse().find("EtudiantBaccalaureat") != string::npos)
            cout << dynamic_cast<EtudiantBaccalaureat&>(*ab) << endl;
        else if (ab->obtenirNomClasse().find("Etudiant") != string::npos)
            cout << dynamic_cast<Etudiant&>(*ab) << endl;
        else if (ab->obtenirNomClasse().find("Professeur") != string::npos)
            cout << dynamic_cast<Professeur&>(*ab) << endl;
        map<string, Emprunt*> emprunts = trierEmprunt(ab);
        for(auto it = emprunts.begin(); it != emprunts.end(); it++){
            cout << *(it->second) << endl;
        }
    }
    else
    {
        cout << "Abonne - " << matricule << " - non trouve" << endl;
    }

}


Bibliotheque &Bibliotheque::operator+=(Abonne *abonne) {
    ajouterAbonne(*abonne);
    return *this;
}

Bibliotheque &Bibliotheque::operator+=(ObjetEmpruntable *obj) {
    ajouterObjetEmpruntable(obj);
    return *this;}

Bibliotheque &Bibliotheque::operator-=(Abonne *abonne) {
    retirerAbonne(abonne->obtenirMatricule());
    return *this;
}

Bibliotheque &Bibliotheque::operator-=(ObjetEmpruntable *obj) {
    retirerObjetEmpruntable(obj->obtenirCote());
    return *this;
}

std::istream &operator>>(std::istream &in, const Bibliotheque &biblio) {
    string mot;
    in >> mot;
    biblio.rechercherObjetEmpruntable(mot);
    return in;
}

std::map<std::string, Emprunt *> Bibliotheque::trierEmprunt(Abonne *abonne) const {
    pair<string, Emprunt*> elemMap;
    map<std::string, Emprunt *> mapEmprunts;
    auto listEmprunt = gestEmprunts_.trouverContenu(MemeObjet<string>(abonne->obtenirMatricule()));

    for(auto it = listEmprunt.begin(); it != listEmprunt.end(); it++){
        elemMap  = make_pair((*it)->obtenirObjetEmpruntable()->obtenirTitre(), *it);
        mapEmprunts.insert(elemMap);
    }
    
    return mapEmprunts;
}
