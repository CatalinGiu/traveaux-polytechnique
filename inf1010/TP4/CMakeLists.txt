cmake_minimum_required(VERSION 3.3) 

project(TP4) 
 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") 
 

set(SOURCE_FILES main.cpp Abonne.h Abonne.cpp Bibliotheque.h Bibliotheque.cpp Dvd.h Dvd.cpp Emprunt.h Emprunt.cpp Etudiant.h Etudiant.cpp EtudiantBaccalaureat.h EtudiantBaccalaureat.cpp 
Livre.h Livre.cpp LivreNumerique.h LivreNumerique.cpp ObjetEmpruntable.h ObjetEmpruntable.cpp ObjetNumerique.h ObjetNumerique.cpp Professeur.h Professeur.cpp) 
 
add_executable(TP4 ${SOURCE_FILES})
