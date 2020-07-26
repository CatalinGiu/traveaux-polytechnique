/*
Fichier: LivreNumerique.cpp
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 25 fevrier 2016
Date de modification: 28 fevrier 2016
Description: Initialisation des fonctions de la Classe LivreNumerique
*/
#include "LivreNumerique.h"


using namespace std;


LivreNumerique::LivreNumerique() {

}
//Le constructeur par parametres de LivreNumerique utilise le constructeur par parametre de Livre.
LivreNumerique::LivreNumerique(FORMAT_DOCUMENT format, unsigned int taille,
                               std::string lien, const std::string &cote, const std::string &titre, unsigned int annee,
                               unsigned int ageMin, unsigned int nbExemplaires, const std::string &auteur,
                               const std::string &genre) : Livre(cote, titre, annee, ageMin, nbExemplaires, auteur, genre),
                               format_(format), tailleOctet_(taille), lien_(lien){

}

LivreNumerique::~LivreNumerique() {

}

std::string LivreNumerique::obtenirFormat() const {
    string format;
    switch(format_){
        case FORMAT_PDF:
            format = "pdf";
            break;
        case FORMAT_DOCX :
            format = "docx";
            break;
        case FORMAT_EPUB:
            format = "epub";
            break;
        case FORMAT_TXT:
            format = "txt";
            break;
        case FORMAT_INCONNU:
            format = "inconnu";
            break;

    }
    return format;
}

unsigned int LivreNumerique::obtenirTaille() const {
    return tailleOctet_;
}

std::string LivreNumerique::obtenirLien() const {
    return lien_;
}

void LivreNumerique::setFormat(FORMAT_DOCUMENT format) {
    format_ = format;
}

void LivreNumerique::setTaille(unsigned int taille) {
    tailleOctet_ = taille;
}

void LivreNumerique::setLien(const std::string& lien) {
    lien_ = lien;
}

bool LivreNumerique::recherche(const std::string& mot) const{
    bool trouve = Livre::recherche(mot)
                || convertirMinuscule(mot) == obtenirFormat();
    return trouve;
}

std::ostream &operator<<(std::ostream &os, const LivreNumerique &livreNum) {
    os << "Objet Numerique! Taille : " << livreNum.tailleOctet_ << " oct. "
            << livreNum.lien_ << " Format : " << livreNum.obtenirFormat() << endl
            << dynamic_cast<const Livre&>(livreNum);
    return os;
}


