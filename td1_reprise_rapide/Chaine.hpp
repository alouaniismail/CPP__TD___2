#ifndef __CHAINE__HPP
#define __CHAINE__HPP

class Chaine{
private:
  unsigned int _taille;
  char* _donnees;
public:
  Chaine();
  ~Chaine();
  Chaine(const char*);
  unsigned int taille();
  char get(unsigned int);
};

#endif
