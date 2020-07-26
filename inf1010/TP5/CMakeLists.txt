cmake_minimum_required(VERSION 3.3)
project(TP5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp
        Gestionnaire.h
        MemeObjet.h
        RechercheObjetEmpruntable.h
        DetruireEmprunt.h
        TrieParTitre.h
        Empruntable.h
        Abonne.cpp Abonne.h
        Bibliotheque.cpp Bibliotheque.h
        Dvd.cpp Dvd.h
        Emprunt.cpp Emprunt.h
        Etudiant.cpp Etudiant.h
        EtudiantBaccalaureat.cpp EtudiantBaccalaureat.h
        Livre.cpp Livre.h
        LivreNumerique.cpp LivreNumerique.h
        ObjetEmpruntable.cpp ObjetEmpruntable.h
        ObjetNumerique.h
        Professeur.cpp Professeur.h)
add_executable(TP5 ${SOURCE_FILES})
