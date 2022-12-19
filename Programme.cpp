#include <stdio.h>

#include "Chaine.hpp"




/*void affichage(Chaine s){
  Chaine &ref=s;
  printf("%d\n",ref.taille());
  return;
  }*///a commenter apres.

//mécanisme de gestion de mémoire
//utilisation des références
//ouverture aux opérateurs.

void annexe(const Chaine &s) {}

int main() {
  
  Chaine chaine("Une petite");//une seule.

  annexe(chaine);

  //copie par référence=>même adresse soir finalement une seule
  //instance créée.(réflexion par adresses)

  printf("=================================\n");

  //analysons ceci:
  Chaine chaine_2("un message grand");
  
  Chaine &ref=chaine_2;
  printf("%d\n",ref.taille());//c'est totalemeent réglé.(dans le main,
  //on copie PAR REFERENCE VIA chaine &ref=s puis affichage normal avec cstdio
  //via printf de %d(spécificateur).


  
  //affichage(chaine_2);//celui-là plûtôt.
  
  //fin de lanalyse.

  //séparateur de produits d'execution.
  


  //correction globale après l'ajout du constructeur par recopie:
  //revient à reprendre les besoins de l'exo4 et les demandes de l'exo5 voire le 6.
  
  /*Chaine s1("une chaine");
  Chaine s2(s1);//doit afficher la même chose que Chaine.cpp(16): Chaine.
  Chaine s3=s1;*/
  
  //les instances faites en ligne 3 et 4 sont de nouvelles différentes en terme
  //d'adressages.


  /*
  printf("%d\n",s3.taille());
  printf("%d\n",s2.taille());
  printf("%d\n",s1.taille());

  int taille1=s1.taille();
  int* p1=&taille1;
  printf("%p\n",p1);
  int taille2=s2.taille();
  int* p2=&taille2;
  printf("%p\n",p2);
  int taille3=s3.taille();
  int* p3=&taille3;
  printf("%p\n",p3);*/

  /*printf("*****************************************************\n");
  
  s1.debug();//contrairement à ce niveau où on a :
  //chaine 4 fois ce qui est conforme à ce qu'on attendait. 
  s2.debug();
  s3.debug();


  *  /






  printf("*********************************************************************\n\n\n");



  
  //puis erreur: incompatibilitée.
  //pour réussir le coup de Chaine s2=Chaine(s1), il faut avoir un constructeur de recopie de prototype:
  //Chaine(Chaine& cs); d'après le cours


  /*Analysons la situation:
il y a un free après un free déclenche une erreur disons que c'est déjà 2 fois free (tcache 2) Abondon (core dumped) cela signifie que les instances les 3 ont été créées bien sûr, cela se voie via l'affichage de chaine 3 fois mais à la fin il faut libérer les ressources l'appel au destructeur vu que tout est lié détruit l'unique adresse qui les lient, le programme continue, il détruit une chose déja détruite: error:: double free detected in tcache2. c'est clair avec valgrind, 2 free de +. (de meme avec = au lieu d'instanciation direct Point{} pour structure de tout public par exemple..)
  */

  //ils appelent le même destructeur.(qui opère sur les mêmes données)
  

  return 0;
}


//les 2 affichages de chaine viennent de la fonction debug.
//les pseudo-instanciations ne font rien à priori.
//les tailles sont les mêmes, les adresses différentes
//le contenu de _données est le même après vidage de la pile
//appel au destructeur qui sera le même pour toutes les instances.. C'est là le problème.

//les instances de plus (s2) =s1 créée de nouvelles instances d'adresses différentes mais de copies identidiques ainsi la libération appelle ~Chaine depuis l'instance s1 qui vide les ressources allouées à toute chaîne ressemblant à données ou à taille en cast<int> puis les autres appels génèrent 2 erreurs(voir valgrind). 


//avec gdb, s1 et s2 et s3 ont toutes une adresse ###.
//avec cet outil, tous les attributs ont des adresses différentes.
//résumé: adresses différents, allocation puis désallouage via la table
//des chaînes puis suppression de ce qu'il y avait dans les cases: error même si
//cela ne correspond pas à la même adresse(pour vérification globale && SURTOUT:
//comprendre le comportement du destructeur).
