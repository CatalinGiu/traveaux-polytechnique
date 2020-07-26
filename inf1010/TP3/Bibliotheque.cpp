/*
Fichier: Bibliotheque.cpp
Auteur(s): Catalin Giurca & Julien Gauthier
Date de creation: 11 fevrier 2016
Date de modification: 21 fevrier 2016
Description: Initialisation des fonctions de la Classe Bibliotheque
*/


#include "Bibliotheque.h"

Bibliotheque::Bibliotheque() {

}

Bibliotheque::~Bibliotheque() {											//On delete les les espaces alloues dans le vecteur d'emprunts 
	for (unsigned int i = 0; i < vEmprunts_.size(); i++) {				//(c'est le seul qui est alloue et non delete dans le programme)
		delete vEmprunts_[i];
	}
	vEmprunts_.clear();													//On clear les vecteurs avec les pointeurs
	vAbonnes_.clear();
	vLivres_.clear();
	vDvd_.clear();
}

Abonne *Bibliotheque::trouverAbonne(const string &matricule) const {
    Abonne* abonne = nullptr;
    bool abonneTrouve = false;
    for(unsigned int i = 0; i < vAbonnes_.size() && !abonneTrouve; i++ ){
        if(*vAbonnes_[i] == matricule){											//cherche dans le vecteur d'abonnes
            abonne = vAbonnes_[i];
            abonneTrouve = true;
        }
    }
    if(!abonneTrouve){													//Si l'abonne n'est pas trouve, on affiche non trouve dans la console.
        cout << "Abonne - " << matricule << "- non trouve" << endl;
    }
    return abonne;
}

ObjetEmpruntable *Bibliotheque::trouverObjetEmpruntable(const string &cote) const {
    bool objetTrouve = false;
    ObjetEmpruntable* objet = nullptr;

    for(unsigned int i = 0; i < vLivres_.size() && !objetTrouve; i++){	//Si le livre est trouve, on sort de la boucle
        if(*vLivres_[i] == cote){
            objet = vLivres_[i];
        }
    }
    for(unsigned int i = 0; i < vDvd_.size() && !objetTrouve; i++){		//Si le DVD est trouve, on sort de la boucle
        if(*vDvd_[i] == cote){
            objet = vDvd_[i];
        }
    }
    return objet;
}

string Bibliotheque::ObtenirClasseObjet(const string &cote) const {
    return trouverObjetEmpruntable(cote)->getType();
}

bool Bibliotheque::ajouterAbonne(Abonne *abonne) {
    bool abonneExiste = false;
    for(unsigned int i = 0; i < vAbonnes_.size() && !abonneExiste; i++){
        if(*vAbonnes_[i] == *abonne){										//Si l'abonne pris en parametre n'est pas d�j� 
            abonneExiste = true;											//dans le vecteur d'abonnes, il est ajout�.
        }
    }
    if(!abonneExiste)					
        vAbonnes_.push_back(abonne);

    return !abonneExiste;
}

bool Bibliotheque::retirerAbonne(const string &matricule) {
    bool abonneTrouve = false;
    for(unsigned int i = 0; i < vAbonnes_.size(); i++){				//Si l'abonne est trouve dans le vecteur d'abonnes,
        if(*vAbonnes_[i] == matricule){								//il en est retire.
            abonneTrouve = true;
            //delete listeAbonne_[i];
        }
        if(abonneTrouve && i != (vAbonnes_.size() - 1)){
            vAbonnes_[i] = vAbonnes_[i+1];
        }
        else if(abonneTrouve && i == vAbonnes_.size() - 1){
            vAbonnes_.pop_back();
        }
    }
    return abonneTrouve;						//En cas de succes, on retourne true. Sinon false.
}

bool Bibliotheque::ajouterLivre(Livre *livre) {
    bool livreTrouve = false;
    for(unsigned int i = 0; i < vLivres_.size() && !livreTrouve; i++){
        if(*vLivres_[i] == *livre){
            livreTrouve = true;
        }											//Le livre est ajoute au vecteur de livres si il n'est pas deja dans celui-ci.
    }

    if(!livreTrouve){
        vLivres_.push_back(livre);
    }
    return !livreTrouve;
}

bool Bibliotheque::ajouterDVD(Dvd *dvd) {
    bool dvdTrouve = false;
    for(unsigned int i = 0; i < vDvd_.size() && !dvdTrouve; i++){
        if(*vDvd_[i] == *dvd){
            dvdTrouve = true;
        }													//Meme chose qu'avec ajouterLivre, mais avec un DVD.
    }

    if(!dvdTrouve){
        vDvd_.push_back(dvd);
    }
    return false;
}

bool Bibliotheque::retirerObjetEmpruntable(const string &cote) {
    bool objetEnlevable = true;
    bool objetEnleve = false;
    ObjetEmpruntable* objetEmpruntable = trouverObjetEmpruntable(cote);

    if(objetEmpruntable->obtenirNbDisponibles() != objetEmpruntable->obtenirNbExemplaires() || objetEmpruntable == nullptr)
        objetEnlevable = false;

    if(objetEnlevable){												//On verifie d'abord que l'objet peut etre enlever du vecteur,
																	
        if(objetEmpruntable->getType() == "DVD") {
            for(unsigned int i = 0; i < vDvd_.size(); i++){			//Si l'objet est un DVD, on le retire du vecteur de DVDs
                if(*vDvd_[i] == *objetEmpruntable){
                    objetEnleve = true;
                    //delete listeLivre_[i];
                }
                if(objetEnleve && i != (vDvd_.size() - 1)){
                    vDvd_[i] = vDvd_[i+1];
                }
                else if(objetEnleve && i == vDvd_.size() - 1){
                    vDvd_.pop_back();
                }
            }
        }

        else if(objetEmpruntable->getType() == "Livre") {
            for(unsigned int i = 0; i < vLivres_.size(); i++){		//Si l'objet est un livre, on le retire du vecteur de livres
                if(*vLivres_[i] == *objetEmpruntable){
                    objetEnleve = true;
                    //delete listeLivre_[i];
                }
                if(objetEnleve && i != (vLivres_.size() - 1)){
                    vLivres_[i] = vLivres_[i+1];
                }
                else if(objetEnleve && i == vLivres_.size() - 1){
                    vLivres_.pop_back();
                }
            }
        }
    }
    return objetEnleve;			//Retourne true si l'objet est enleve du vecteur
}

void Bibliotheque::rechercher(const string &mot) const {		//Recherche un livre ou un DVD avec un mot, dans les deux vecteurs.
    bool objetTrouve = false;
    cout << "Recherche pour le mot : " << mot << endl;
    for(unsigned int i = 0; i < vLivres_.size(); i++){
        if(vLivres_[i]->rechercher(mot)){
            cout << *vLivres_[i];
            if(!objetTrouve){
                objetTrouve = true;
            }
        }
    }
    for(unsigned int i = 0; i < vDvd_.size(); i++){
        if(vDvd_[i]->rechercher(mot)){
            cout << *vDvd_[i];
            if(!objetTrouve){
                objetTrouve = true;
            }
        }
    }
    if(!objetTrouve){
        cout << "Aucun resultat trouve pour le mot : " << mot << endl;
    }
}

bool Bibliotheque::estEmpruntable(const string &matricule, const ObjetEmpruntable &objetEmpruntable) const {
    Abonne *abonne = trouverAbonne(matricule);
    return (
            (objetEmpruntable.obtenirNbDisponibles() >= 1) &&					//Verifier qu'un abonne peut emprunter un objet,
            (abonne->obtenirAge() >= objetEmpruntable.obtenirAgeMinimal()) &&	//en regardant les infos de l'abonne, le nombre d'emprunts 
            (!(abonne->estEmprunte(objetEmpruntable.obtenirCote())))&&			//deja faits et le nombre d'exemplaires disponibles
            (abonne->obtenirNombreEmprunte() < abonne->obtenirLimiteEmprunts()));
}

bool Bibliotheque::emprunter(const string &matricule, const string &cote, unsigned int retour) {
    ObjetEmpruntable* objetEmpruntable = trouverObjetEmpruntable(cote);
    Abonne* abonne = trouverAbonne(matricule);
    bool empruntFait = false;
    if(estEmpruntable(matricule, *objetEmpruntable)){   	//verification si livre empruntable
        empruntFait = true;
        objetEmpruntable->modifierNbDisponibles(objetEmpruntable->obtenirNbDisponibles() - 1);			// reduire le nmobre d'exemplaires disponibles
        Emprunt* emprunt;
        if(objetEmpruntable->getType() == "DVD"){
            emprunt = new Emprunt(matricule, retour, (Dvd*)objetEmpruntable);
        }
        if(objetEmpruntable->getType() == "Livre"){
            emprunt = new Emprunt(matricule, retour, (Livre*)objetEmpruntable);
        }

        abonne->ajouterEmprunt(emprunt);
        vEmprunts_.push_back(emprunt);
    }
    return empruntFait;
}

bool Bibliotheque::retourner(const string &matricule, const string &cote) {
    Abonne* abonne = trouverAbonne(matricule);
    ObjetEmpruntable* objetEmpruntable = trouverObjetEmpruntable(cote);
    bool retourFait = false;

    for(unsigned int i = 0; i < vEmprunts_.size() && !retourFait && objetEmpruntable != nullptr; i++) {
        if(*vEmprunts_[i]->obtenirObjetEmpruntable() == *objetEmpruntable){				
            retourFait = true;
            objetEmpruntable->modifierNbDisponibles(objetEmpruntable->obtenirNbDisponibles() + 1); 		//augmente le nombre d'exemplaires disponibles de 1
            abonne->retirerEmprunt(*objetEmpruntable);
            delete vEmprunts_[i];						//Libere l'espace prealablement occupe par l'objet retourne.
            enleverEmprunt(i);
        }
    }
    return retourFait;			//Retourne true si le retour est bien fait.
}

void Bibliotheque::infoAbonne(const string &matricule) const {
    if(trouverAbonne(matricule) != nullptr) {
        cout << *trouverAbonne(matricule) << endl;
    }
}

istream& operator>>(istream& i, const Bibliotheque& bibliotheque) {
    string mot;
    cin >> mot;
    bibliotheque.rechercher(mot);
    return i;

}

void Bibliotheque::operator+=(Abonne &abonne) {
    ajouterAbonne(&abonne);
}

void Bibliotheque::operator+=(Livre &livre) {
    ajouterLivre(&livre);
}

void Bibliotheque::operator+=(Dvd &dvd) {
    ajouterDVD(&dvd);
}

void Bibliotheque::operator-=(Abonne &abonne) {
    retirerAbonne(abonne.obtenirMatricule());
}

void Bibliotheque::operator-=(ObjetEmpruntable &objetEmpruntable) {
    retirerObjetEmpruntable(objetEmpruntable.obtenirCote());
}
/*
 * fonction non demandee qui ne fait que decaler tous les emprunts vers la droite une fois qu'on enleve
 * un emprunt qui n'est pas a la fin de la liste
 * on poourait la rendre plus generale (qui engloberait les listes d'abonnes et les livres) si
 * on avait le droit d'utiliser les templates
 */
void Bibliotheque::enleverEmprunt(unsigned int pos){				// cette fonction est la meme que dans abonne mais on ne l'a pas rendu un fonction globale
    for(unsigned int i = pos; i < vEmprunts_.size() - 1; i++){		// afin de preserver le principe d'encapsulaion
        vEmprunts_[i] = vEmprunts_[i+1];
    }
    vEmprunts_.pop_back();
}
