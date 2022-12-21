#include "Chaine.hpp"
#include<cstdio>
#include<cstdlib>
#include<cstring>

Chaine::Chaine():_taille(0),_donnees(NULL){
  printf("%s(%d): %s\n",__FILE__,__LINE__,__func__);
}

Chaine::~Chaine(){
  if(_donnees!=NULL)
    delete[] _donnees;
  printf("appel au destructeur\n");
}

unsigned int Chaine::taille(){
  return this->_taille;
}

Chaine::Chaine(const char* data){
  //strcpy il faut un nombre exact d'allocations de type char(s).voilà.
  _taille=strlen(data);//savoir la taille.d'abord.///
  _donnees=new char[_taille+1];//allocation d'un tableau de char avec '\0' vide.
  strcpy(_donnees,data);
}

char Chaine::get(unsigned int i){
  if(i<_taille && i>=0 && _donnees!=NULL)
    return _donnees[i];
  else
    return '\0';
}
