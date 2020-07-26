cmake_minimum_required(VERSION 3.3)
project(TP3_inf1010)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Emprunt.cpp Emprunt.h Abonne.cpp Abonne.h ObjetEmpruntable.cpp ObjetEmpruntable.h Bibliotheque.cpp Bibliotheque.h DVD.cpp DVD.h Etudiant.cpp Etudiant.h EtudiantBaccalaureat.cpp EtudiantBaccalaureat.h Livre.cpp Livre.h Professeur.cpp Professeur.h)
add_executable(TP3_inf1010 ${SOURCE_FILES})