//
//  maingestionnaire.cpp
//  pratique
//
//  Created by Martine Bellaiche on 2016-03-04.
//  Copyright © 2016 Martine Bellaiche. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <list>
#include "Gestionnaire.h"

using namespace std;


 bool predicate1(int * entier)
{ return *entier > 90;}

bool predicate2 (int * entier)
{
    return (*entier >= 0  && *entier <= 10);
}



int main()
{
    srand (time(nullptr));
    Gestionnaire <int> maListe;
    int * tableau [2000];
    int *retirerEle;
    for ( int i = 0 ; i < 2000 ;i++)
    {   tableau[i] = new int(rand()%101);
        maListe.ajouterElement(tableau[i]);
        retirerEle = tableau[i];
    }


   
    if (maListe.retirerElement(retirerEle))
        cout << "retrait réussi"<< endl;
    else
        cout << " Element n'existe pas dans la liste"<< endl;;
    
    if( maListe.retirerContenu(predicate1))
        cout << "retrait  des elements > 90 "<< endl;
    else
        cout << " Aucun element retire"<< endl;;
    
    int * intTrouver = maListe.trouverElement(predicate2);

    
    if (intTrouver != nullptr)
        cout <<  *intTrouver<<endl;
    else cout << " non trouve dans le gestionnaire"<<endl;
    
    
    list<int* > autreListe;
    
    autreListe = maListe.trouverContenu(predicate2);
    cout << autreListe.size();
    
    
    return 0;
    
}
