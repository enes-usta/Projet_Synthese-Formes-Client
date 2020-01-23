#include "Erreur.h"
#include <Windows.h>
#include "Sauvegarde.h"
#include <fstream>
#include "io.h"

Sauvegarde::Sauvegarde() : VisiteurSauvegarde() {
	_fichier << DOSSIER;
}

void Sauvegarde::Ecriture(ostringstream &nomFichier,ostringstream &texte){

	ostringstream tempfichier;
	tempfichier << _fichier.str();
	_fichier << nomFichier.str();

	if (!fexists(_fichier.str().c_str())) {
		ofstream file(_fichier.str());
	
		if (file.is_open()) file << texte.str();
		else throw Erreur("Impossible d'ouvrir le fichier");
	
	file.close();
	}

	_fichier.str("");
	_fichier.clear();
	_fichier << tempfichier.str();
}

bool fexists(const char* filename){
	ifstream ifile(filename);
	return (bool) ifile;
}

int Sauvegarde::getFileNum(string str) {

	fstream file;
	ostringstream temps;
	string num;
	temps << _fichier.str() << "Num.txt";

	if(fexists(temps.str().c_str())){
		file.open(temps.str().c_str(), fstream::in | fstream::out);
		file >> num;

		//str2 = str + to_string(i);
	}
	else {

		return 0;
	}
}

bool dirExists(const char* const path)
{
	struct stat info;

	int statRC = stat(path, &info);
	if (statRC != 0)
	{
		if (errno == ENOENT) { return false; } // something along the path does not exist
		if (errno == ENOTDIR) { return false; } // something in path prefix is not a dir
		return false;
	}

	return (info.st_mode & S_IFDIR) ? true : false;
}

void Sauvegarde::visite(const FormeComposee *forme) {

	ostringstream tempDossier, texte;

	vector<Forme*> vecteurs = forme->getGroupe();
	vector<Forme*>::iterator iter;

	tempDossier << _fichier.str();
	_fichier << "FormeComposee," << forme->getCouleur() << "_" << _num << "/";

	if (CreateDirectory(_fichier.str().c_str(), NULL)) {
		for (unsigned int i = 0; i < vecteurs.size(); i++) vecteurs.at(i)->sauvegarder(this);
	}

	_fichier.str("");
	_fichier.clear();
	_fichier << tempDossier.str();
}

void Sauvegarde::visite(const Segment *forme) {

	ostringstream nomFichier, contenu;

	nomFichier << "Segment" << getFileNum("Segment") << ".txt";
	contenu << "Segment," << forme->getCouleur() << "," << forme->getA().x << "," << forme->getA().y << "," << forme->getB().x << "," << forme->getB().y;

	Sauvegarde::Ecriture(nomFichier, contenu);
}

void Sauvegarde::visite(const Cercle* forme) {
	ostringstream nomFichier, contenu;

	nomFichier << "Cercle" << getFileNum("Cercle") << ".txt";
	contenu << "Cercle," << forme->getCouleur() << "," << forme->getCentre().x << "," << forme->getCentre().y << "," << forme->getRayon();

	Sauvegarde::Ecriture(nomFichier, contenu);
}

void Sauvegarde::visite(const Triangle* forme) {
	ostringstream nomFichier, contenu;

	nomFichier << "Triangle" << getFileNum("Triangle") << ".txt";
	contenu << "Triangle," << forme->getCouleur() << "," << forme->getA().x << "," << forme->getA().y << "," << forme->getB().x << "," << forme->getB().y << "," << forme->getC().x << "," << forme->getC().y;

	Sauvegarde::Ecriture(nomFichier, contenu);
}

void Sauvegarde::visite(const Polygone* forme) {
	ostringstream nomFichier, contenu;

	nomFichier << "Polygone" << getFileNum("Polygone") << ".txt";
	contenu << "Polygone," << forme->getCouleur();

	for (unsigned int i = 0; i < forme->getVecteurs().size(); i++) {
		contenu << "," << forme->getVecteurs().at(i).x << "," << forme->getVecteurs().at(i).y;
	}
	Sauvegarde::Ecriture(nomFichier, contenu);
}