//
// Created by catalin on 25/03/16.
//

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
    //trouve tous les ellements qui satisfont le predicat
    template <typename Predicate>
    std::list<T*> trouverContenu(const Predicate& p) const;


private:
    std::list<T*> listeElem_;

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
    return elemAjoute;
}
template <typename T>
bool Gestionnaire<T>::retirerElement(T *elem) {
    unsigned int taille = listeElem_.size();
    listeElem_.remove(elem);
    bool retour = listeElem_.size()!= taille;
    return retour;
}

template<typename T>
template<typename Predicate>
bool Gestionnaire<T>::retirerContenu(const Predicate &p) {
    unsigned int taille = listeElem_.size();
    listeElem_.remove_if(p);
    bool retour = listeElem_.size() < taille;
    return retour;
}

template<typename T>
template<typename Predicate>
T *Gestionnaire<T>::trouverElement(const Predicate &p) const{

    typename std::list<T*>::const_iterator iterElem = find_if(listeElem_.begin(), listeElem_.end(), p);
    if(iterElem == listeElem_.end())
        return nullptr;
    return *iterElem;
}

template<typename T>
bool Gestionnaire<T>::trouverElement(const T &elem) const{
    return !(find(listeElem_.begin(), listeElem_.end(), elem) == listeElem_.end());
}

template<typename T>
template<typename Predicate>
std::list<T *> Gestionnaire<T>::trouverContenu(const Predicate &p) const{
    std::list<T*> contenu;
    copy_if(listeElem_.begin(), listeElem_.end(),back_inserter(contenu), p);
    return contenu;
}


#endif //GESTIONNAIRE_GESTIONNAIRE_H
