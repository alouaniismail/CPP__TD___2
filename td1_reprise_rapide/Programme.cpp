#include<cstdio>
#include<cstdlib>
#include "Chaine.hpp"

//en resume, si on passe pas en reference, la fonction va faire une copie
//complete donc le delete classique sur un element copie sur la pile
//entrainerait la destruction de _donnees d'ou le double free mais en reference
//ca va pas faire une copie mais a la fin le delete va etre ignore car le
//passage considere l'argument comme un alias pas de droits de supprimer les
//donnees d'ou un nombre correct de destructions par rapport aux instanciations.

void annexe(Chaine &s){}
//en resume:
//si on passe une chaine en pile ou en tas
//et construite par défaut, elle contient pas de pointeurs
//donc l'appel au delete va rien faire en terme de contenu
//mais via l'appel au constructeur qui prend un const char*
//ca va libérer via delete implicitement à la sortie de l'appel
//_donnees (destructeur appele automatiquement et défini ici)
//ce qui va faire une erreur double free.

//si on passe l'argument par référence cela ferait un alias, le compilateur
//va faire agir l'argument direct sans copie et va savoir que c'est qu'une
//étiquette donc pas de destruction(inutile).
//CELA DONNERAIT 4 APPELS AUX destructeur, et non pas le nombre qu'on avait
//après avoir fixé partiellement'' le probleme.///

int main(){
  Chaine chaine1("premiere");
  Chaine* chaine2;
  chaine2=new Chaine("deuxieme");
  //Les 2 char* passes en arguments sont de types: const char*
  //c'est pour cela C++ ce râle pas ici.
  chaine1.taille();
  chaine2->taille();

  annexe(chaine1);//dans les constructeurs par défaut, on a un appel
  //au destructeur de la copie puis la fin se gère tout seule. Ici, cela
  //se passe différemment, on a 2 appels au destructeurs, c'est comme si
  //la fonction détruisait chaine1 aussi ce que traduit l'appel: double free etc
  //... la seule différence c'est que ici on appelle pas le constructeur par
  //défaut, la fonction fera une copie conforme avec les mêmes adresses pointantes sur la pile puis à la fin va libérer tout le contenu de la chaine avec delete soit delete1 implicitement d'où la faute. Par rapport à ce qui suit(ce qui précède plûtôt), on avait pas des pointeurs implicitement dans le tas --adresses donc le delete ne faisait rien en terme de ce que contenait en extèrieur la classe mais ici ce qu'elle contient vient d'être supprimé, le ré-supprimer cause le problème qu'on a vu.

  annexe(*chaine2);//2 appels au destructeur puis le delete suivant libère une ressource déjà libéré à la sortie de l'appel précédent(celui-là), d'où l'erreur.
  
  delete chaine2;
  //le destructeur est là, delete inclus une phase d'appel en premier
  //qui désalloue le _donnees[strlen(data)+1] de type new char[]
  //qu'on alloué pour exactement cette taille(const char*|data|):strcpy.
  //rq: strncpy size_t nbytesdéfinit le nombre d'octets(ascii codage).
  printf("********************\n");
  
  Chaine chaine11;
  Chaine* chaine22;
  chaine22=new Chaine();
  /*printf("%d\n",chaine11.taille());*/
  chaine11.taille();//appels seulement pour ne pas embrouiller le programme.
  //l'execution en fait sur stdin.
  chaine22->taille();
  annexe(*chaine22);
  //il faut le mettre ici, pas de probleme à ce niveau (memcheck)

  /*
on a appel au destructeur pour chaine2 puis les * puis les constructeurs par défaut puis l'appel au destructeur apres l'instruction delete chaine22, puis annexe(chaine11) declenche un destructeur aussi, reste chaine1 et chaine11 soit 5 apppels ecrits dans le terminal.voilà!
  */



  delete chaine22;
  //appel au destructeur relatif a chaine1.
  //avoir 3 apres les * c'est complétement correct.(persistance avant le block
  //du MAIN()c++)./////

  annexe(chaine11);
  /*
ici, on fait pas une copie, on réalloue un espace mémoire pour un type Chaine d'où un appel au destructeur à la fin de l'exécution de annexe, mais aucune fuite mémoire ici.(copie via réallocation de même block ; pas d'instanciation 
au niveau de la pile nouvelle mais recopiage des adresses mémoires référentes)
  */

  //annexe(*chaine22);/*ajoute un appel au destructeur mais valgrind n'est pas content, en fait, les 2 erreurs de invalid read of size 8 vient des adresses en polymorphisme C. la chaine22 en * se met en copie traditionnelle pas d'instance d'où 5 "appel au destructeur" ecrites sur le terminal, cela est déjà dit. reste les errors valgrind de make; make memcheck.(on a fait un delete avant, l'adresse n'est plus reconnaissable en cascade void*(char*) conversion implicite aussi (type de _donnees en mémoire ecrite)) */ 

  //votons voir le comportement avec chaine1 et chaine2 construites avec
  //le constructeur qui pose le plus probleme:

  
  return 0;
}
