#include <stdio.h>

#include "Chaine.hpp"

//1.en resume comme une injection de nouveau donnees
//invalid free leak summary&definitly lost pour le valgrind ./prog2
//et puis de même double free pour ./prog2 tout simplement.



int main()
{
  Chaine s1("une chaine");
  Chaine s2("coucou");//2 instances d'adresses ###, pas d'appel à la recopie
  //explicite en type typedef<TYPE<///>> args[][].
  
  //s2.operator=(s1);(celle-ci marche aussi)
  s2=s1;
  
  //printf("%p;%p\n",&s1,&s2);(pas besoin d'adresses;aucun rapport)
  //on assigne des adresses a d'autres, cela cree un bordel au niveau
  //d'une affectation classique.
  s2.debug();
  printf("%d\n\n",s2.taille());
  //avec valgrind, on a une erreur: invalid free et erreur dans la LEAK SUMMARY
  //cad. fuite mémoire mais le heap est OK, ce qui est logique ici, mais
  //l'affectation rend les adresses "un peu reliées" ce qui fait tomber
  //le contenu de s2 totalement et crée le problème du double free et au passage
  //la leak summary en definitely lost car 2 adresses reliees et on y accède
  //pas à une adresse dans la pile depuis la dernière des deux (selon le sens).

  //opérateur[].(operator[])

  Chaine s("une chaine");
  for(unsigned int i=0;i<s.taille();i++)
    printf("%c\n",s[i]);

  printf("%s\n\n",(const char*)s);

  Chaine ss(" et la deuxième.\n");
  (s+ss).debug();
}

