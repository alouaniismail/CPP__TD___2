#include <stdio.h>

#include "Chaine.hpp"

void annexe(const Chaine &s) {
  printf("%d\n",s.taille());
}

Chaine& print(Chaine& s){
  s.debug();
  return s;
}


int main() {
  /*
  Chaine chaine("Une petite");
  //Une seule instance
  //avant la reference 2 dont la liberation de "Une petite"(pas passage reference)
  //enclanchait l'erreur via ./prog: double free Abondon(core dumped).
  //voila.

  annexe(chaine);
  */
  
  printf("==========================\n");
  //Chaine s1="une chaine";
  Chaine s1("une chaine");
  printf("==========================\n");
  Chaine s2(s1);
  Chaine s3(s1);

  //Chaine s3=s1 ne marche pas car la déclaration doit être explicite
  //soit Chaine ??(args[]) dont args en global est de type Chaine.

  //avec explicit, aucun problème au niveau de double free
  //car appel à la même méthode de construction.
  
  printf("%p;%p;%p==========================\n\n\n\n",&s1,&s2,&s3);
  //les 3 adresses sont ### <=> 3 instanciations ''² à part.
  //le constructeur par copie dans s2 et Chaine s3 allocation automatique
  //qui vaudra s1 tout différent à part les adresses soit _donnees dedans.
  s1.debug();
  s2.debug();
  s3.debug();
  //appel aux delete en premier
  //au final: la 1ere instruction a la sortie entraine la destruction de
  //la liaison de l'emplacement memoire de _donnees[] dans le tas
  //la deuxieme la même chose d'où erreur de double free la meme qu'on avait
  //dans l'exo5 du td precedent.(instances par recopie(attributs adresses et non
  //pas l'adresse de l'instance elle-même))

  //la solution: ajouter un constructeur par recopie qui va au lieu de recopier
  //le même truc qui est dedans faire une initialisation pareille en copiant
  //tous les donnees profondes d'attributs (ce que contient _donnees en tant
  //qu'adresse) ainsi l'appel aux destructeurs à la fin va désallouer pas le même espace mémoire.(5allocations la derniere est une copie d'adresse de pile à l'intèrieur de cette dernière(ce qui compte comme allocation dans la mémoire de la pile))

  Chaine c("message");
  print(c);

  Chaine chaine1("Antenne0");
  Chaine& ref=chaine1;//même chose référence pas pointeur!!!!
  Chaine chaine2(ref);//on passe la ||référence|| soit ref et pas &ref.
  //2 allocations de plus ; c'est logique.
  //par rapport au explicit ; ceci.

  //et si on redéfinissait l'opérateur = pour le TODO= de *.hpp?
  //cela viendrait après.
  
}
