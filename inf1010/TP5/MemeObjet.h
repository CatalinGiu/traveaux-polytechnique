/*
Fichier: MemeObjet.h
Auteur(s): Julien Gauthier, Catalin Giurca
Date de creation: 10 mars 2016
Date de modification: 29 mars 2016
Description: Foncteur qui permet de trouver un objet identique dans le conteneur
*/

#ifndef TP5_MEMEOBJET_H
#define TP5_MEMEOBJET_H
template <class P>
class MemeObjet{
public:
    MemeObjet(P& obj );
    template < typename T>				//Le pointeur de type P est compare au pointeur de type T en parametre
    bool operator()( T* obj2) const;

private:
    P* obj_;		//Attribut pointeur de type P (type dans le template)
};

template <class P>
MemeObjet<P>::MemeObjet(P& obj): obj_(&obj){
}

template <class P>
template <typename T>
bool MemeObjet<P>::operator()(T* obj2) const{		//Operateur qui retourne true si le pointeur P est pareil
    return *obj_ == *obj2;							//au pointeur T		
};
#endif //TP5_MEMEOBJET_H
