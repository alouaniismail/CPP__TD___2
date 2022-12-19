#include<cstdio>

#include "Chaine.hpp"

Chaine::Chaine():_taille(0) {
  _donnees=NULL;
}

Chaine::Chaine(const char *s) {
  // Cas s==NULL a gerer plus tard.
  _taille = std::strlen(s);

  _donnees = new char[_taille + 1];
  std::strcpy(_donnees, s);
  
  std::printf("%s(%d): %s\n", __FILE__, __LINE__, __func__);
  //d'où vient le chaine16:cpp....
}

Chaine::~Chaine() {
  if (_donnees != NULL)
    delete[] _donnees;
  _donnees=NULL;
  //std::printf("%s(%d): %s\n", __FILE__, __LINE__, __func__);
  }

unsigned int Chaine::taille() const {
    return _taille;
}

char Chaine::get(unsigned int i){
  if (_donnees==NULL) return '\0';
  if (i>_taille) return '\0';
  return _donnees[i];
}




//regles de programmation: tjrs mettre le const sur la methode et les references. vais-je modifier l'objet? voilà la question qu'on doit se poser avant de faire une quelconque action.

//les args d'une func sont soient des types primitifs soit des pointeurs soit des références.

void Chaine::debug(){//le nom! pas niveau constructeur reflechir.
  printf("%s\n",_donnees);
}//sans argument!!



static char* copie(const char* src, int len){
  char* dst=new char[len];
  std::strcpy(dst,src);//#include<cstring>=>namespace: std::strcpy pour etre carre.(le contraire)=<=>classe dans classe depuis cstdio.///
  return dst;
}//propre à ce fichier

Chaine::Chaine(const Chaine& c):_taille(c._taille){
  if(c._donnees==NULL)
    _donnees=NULL;
  else{
    _donnees=copie(c._donnees,_taille+1);
  }//voilà.
}//constructeur de recopie en explicit(conversion implicite=>explicit seulement en Chaine.hpp pour bien la désigner.)

//au lieu de faire n'importe quoi: Chaine print(const Chaine& c) dans Chaine.hpp:  procédons étapes par étapes..///////

