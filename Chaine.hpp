#ifndef CHAINE_HPP
#define CHAINE_HPP

#include <cstring>

class Chaine {
 private:
  char* _donnees;
  unsigned int _taille;

 public:
  Chaine();
  Chaine(const char*);
  explicit Chaine(const Chaine& c);//signature d'un constructeur par recopie.
  //passage par référence constante(voir raison exo2.).///////
  ~Chaine();

  const Chaine& operator=(const Chaine&);//opérateur d'affectation.(redéfinition~~~)./////////(on choisit pas Chaine operator=(const Chaine&);)
  //les mêmes raisons qu'on a précisé en global
  /*dans la première partie
du 
td2.
  */

  //now: opérateur[]. s.operator[unsigned int index]
  const char& operator[](unsigned int indice) const;

  //dernièrement(enfin presque): opérateurs de conversion
  operator const char*() const;


  //reste: l'opérateur de concaténation(l'exo9).(difficile)
  Chaine& operator+(const Chaine& s1);
  //c'est facile si on respecte bien les regles : premierement,
  //les operateurs en tant que methodes particuliers ont un zero argument
  //comme l'opérateur de conversion operator const char*() const
  //ou bien comme l'opérateur s[i]: const char& operator[](const Chaine&);
  //donc celui-là va en avoir un : const Chaine& s1 et va renvoyer
  //tjrs:& viadonc:: un:->Chaine& .(pas de const ici)



  //le prototype a l'air bon.
  //on peut le surcharger pour ajouter un entier avec un buffer en statique(fichier) => solution risquée(valgrind toujours) avec une grosse macro de conversion vers un char(code ascii simple ecriture puis allocation puis ajustement(suivant le dernier operator defini jusqu'à là.
  
  unsigned int taille() const;
  char get(unsigned int i);
  void debug();
};

#endif
