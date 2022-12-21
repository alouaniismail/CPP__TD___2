#include<cstdio>

#include "Chaine.hpp"

/*
static char* copie(const char* src, int len){
  char* dst = new char[len];
  std::strcpy(dst,src);
  return dst;
}


Chaine::Chaine(const Chaine &c):_taille(c._taille){
  if (c._donnees == NULL)
    _donnees = NULL;
  else{
    _donnees = copie(c._donnees,_taille+1);
  }
}
*/

Chaine::Chaine():_taille(0) {
  _donnees=NULL;
}

Chaine::Chaine(const Chaine& c):_taille(c._taille){
  if(c._donnees==NULL)
    _donnees=NULL;
  else{
    _donnees=new char[c._taille+1];
    std::strcpy(_donnees,c._donnees);//si on inclut seulement cstdio.
    //new est universel en c++.
  }
}

Chaine::Chaine(const char *s) {
  // Cas s==NULL a gerer plus tard.
  _taille = std::strlen(s);

  _donnees = new char[_taille + 1];
  std::strcpy(_donnees, s);
  
  std::printf("%s(%d): %s\n", __FILE__, __LINE__, __func__);
}

Chaine::~Chaine() {
  if (_donnees != NULL)
    delete[] _donnees;
  _donnees=NULL;
  std::printf("%s(%d): %s\n", __FILE__, __LINE__, __func__);
}

unsigned int Chaine::taille() const {
    return _taille;
}

char Chaine::get(unsigned int i){
  if (_donnees==NULL) return '\0';
  if (i>_taille) return '\0';
  return _donnees[i];
}

void Chaine::debug(){
  printf("%s\n",_donnees);
}

//pour faire s2=s1 il faut définir un opérateur d'affectation
//en c++ de signature const Chaine& Chaine::operator=(cont Chaine&);


const Chaine& Chaine::operator=(const Chaine& c){
  //on doit faire s2=s1 soit s2.operator=(s1)
  //on doit ré-affecter les données de s1 à s2
  //on vérifie tjrs si c'est la même instance par adresse!
  if(this == &c){
    return *this;
  }
  //maintenant c'est différent on commence l'affectation
  //le problème de l'adresse de _donnees si !=NULL(double free, error
  //valgrind autre que double free detected).
  if(NULL!=_donnees){
    delete[] _donnees;
  }
  _taille=c._taille;
  _donnees=new char[_taille+1];
  std::strcpy(_donnees,c._donnees);
  
  //pour le invalid read of size 1.
  //on ajoute les 2 derniers(le dernier) delemiteur a chaque copie.
  std::strcpy(this->_donnees,c._donnees);
  return *this;//on retourne l'instance.
  //maintenant si on fait l'affectation le double free s'envole
  //et on dispose d'une nouvelle instance copie conforme a 99% donc pas de
  //double free ni d'erreurs de valgrind.
}

static char VIDE='\0';

const char& Chaine::operator[](unsigned int indice) const{
  if(_donnees==NULL) return VIDE;//comme une macro.
  if(indice>_taille) return VIDE;
  return _donnees[indice];
}

//la signature comme toujours le retour char soit const char& car const
//appel aux attributs possible pas de modif. => argument const Chaine& s
//et nom de la fonction en extern: Chaine::operator[].

//nous voulons pouvoir ecrire: (const char*)s soit s.operator__de_conversion
//a priori sans parametres .
//c'est un opérateur qui est: (const char*) appliqué à une instance
//le prototype dans le Chaine.hpp sera: ... operator const char* ...
//dans ce cas le prototype est le suivant:
//operator const char*() const; (les Chaines sont constantes, on s'assure
//bien que celle-ci ne modifie rien).

Chaine::operator const char*() const{
  return _donnees;
}

Chaine& Chaine::operator+(const Chaine& s1){
  char* data=new char(_taille+s1._taille);
  strcpy(data,_donnees);//pas besoin en c++11.(std::strcpy)
  strcat(data,s1._donnees);
  if(NULL==_donnees){//construction par defaut
    //pas de error de valgrind
    _donnees=data;//a controler ulterieurement.
    _taille=_taille+s1._taille;
    return *this;//eviter de meme le
    //double free(nouvelle data en terme d'adresse # de $1)./ ///
  }
  else{
    delete[] _donnees;//eviter le invalid dans les erros de valgrind.
    _donnees=data;
    _taille=_taille+s1._taille;
    return *this;//recopie et this contient un data différent
    //=>éviter le double free detected in tcache 2()..
  }
}
  
//on a fait de notre mieux: les fuites sont resolues
//mais le make memcheck direct pose tjrs probleme...(a revoir)
//on modifie s en entrée pour inclure les donnees de ss.
//et envoir le nouveau s avec de nouvelles informations.(les delete sur
//les profonds pointeurs sont faits explicitement ici)
//c'est comme un =operator plus performant...
//...
