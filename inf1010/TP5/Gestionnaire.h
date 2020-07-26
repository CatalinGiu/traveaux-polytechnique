/*
Fichier: Gestionnaire.h
Auteur(s): Julien Gauthier, Catalin Giurca
Date de creation: 10 mars 2016
Date de modification: 29 mars 2016
Description: Classe generique 
*/

#ifndef GESTIONNAIRE_GESTIONNAIRE_H
#define GESTIONNAIRE_GESTIONNAIRE_H

#include <list>
#include <algorithm>
#include <iterator>

template <typename T>
class Gestionnaire {
public:
    //constructeur par defaut
    Gestionnaire();
    //destructeur
    ~Gestionnaire();
    //ajouter un element a la liste
    bool ajouterElement(T* elem);
    //retirer une element de la lsite
    bool retirerElement(T* elem);
    //retirer Contenu de la liste
    template <typename Predicate>
    bool retirerContenu(const Predicate& p);
    //recherche un objet dans la liste
    template <typename Predicate>
    T* trouverElement(const Predicate& p) const;
    //surcharge de trouverElement
    bool trouverElement(const T& elem) const;
    //trouve tous les elements qui satisfont le predicat
    template <typename Predicate>
    std::list<T*> trouverContenu(const Predicate& p) const;


private:
    std::list<T*> listeElem_;	//L'attribut est une liste d'elements pouvant etre changes  
								//(Abonne, ObjetEmpruntable ou Emprunt), comme on peut
								//le voir et l'utiliser dans la classe Bibliotheque.
};
template <typename T>
Gestionnaire<T>::Gestionnaire() {

}

template <typename T>
Gestionnaire<T>::~Gestionnaire() {

}
template <typename T>
bool Gestionnaire<T>::ajouterElement(T *elem) {
    bool elemAjoute = false;
    if(std::find(listeElem_.begin(), listeElem_.end(), elem) == listeElem_.end()){
        elemAjoute = true;
        listeElem_.push_back(elem);
    }
    return elemAjoute;		//Retourne true si l'ajout a ete effectue avec succes
}
template <typename T>
bool Gestionnaire<T>::retirerElement(T *elem) {
    unsigned int taille = listeElem_.size();
    listeElem_.remove(elem);
    bool retour = listeElem_.size()!= taille;
    return retour;			//Retourne true si l'element a bien ete retire, donc si 
}							//la taille de la liste d'elements a diminue.

template<typename T>
template<typename Predicate>
bool Gestionnaire<T>::retirerContenu(const Predicate &p) {		//Prend un predicat unaire en parametre
    unsigned int taille = listeElem_.size();
    listeElem_.remove_if(p);
    bool retour = listeElem_.size() < taille;
    return retour;		//Retourne true si l'element du conteneur verifiant le predicat a ete retire de la liste
}

template<typename T>
template<typename Predicate>
T *Gestionnaire<T>::trouverElement(const Predicate &p) const{		//Prend un predicat unaire en parametre

    auto iterElem = find_if(listeElem_.begin(), listeElem_.end(), p);
    if(iterElem == listeElem_.end())
        return nullptr;
    return *iterElem;		//Retourne un pointeur de type T, qui correspond a l'element qui verifie le predicat
}

template<typename T>
bool Gestionnaire<T>::trouverElement(const T &elem) const{
    return !(find(listeElem_.begin(), listeElem_.end(), elem) == listeElem_.end());
}	//Retourne true si l'element est trouve

template<typename T>
template<typename Predicate>
std::list<T *> Gestionnaire<T>::trouverContenu(const Predicate &p) const{
    std::list<T*> contenu;
    copy_if(listeElem_.begin(), listeElem_.end(),back_inserter(contenu), p);
    return contenu;
}	//Retourne une liste de pointeurs de type T, c'est-a-dire tous les elements du conteneur
	//qui verifie le predicat.

#endif //GESTIONNAIRE_GESTIONNAIRE_H
