#ifndef CHAINE_HPP
#define CHAINE_HPP

#include <cstring>

class Chaine {
 private:
  char* _donnees;
  unsigned int _taille;

 public:
  Chaine();
  explicit Chaine(const Chaine& c);//constructeur par recopie
  //pour éviter les problèmes soucieux de l'exo3.(élargissement par rapport au compilateur (système de typage dynamique~##~).
  Chaine(const char*);
  ~Chaine();

  unsigned int taille() const; //cela indique que cette méthode de va pas modifier les attributs de this.
  char get(unsigned int i);
  void debug();
  //Chaine print(const Chaine& s);
};

#endif
