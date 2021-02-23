# BSP
*ATTENTION*

Ce travaille est pensee pour fonctionner avec la LIBGFX.
Lien : .https://github.com/crenaudi/Libgfx

Il s'agit ici d'un generateur d'arbre binaire suivant le travail de John Carmack (avec un tri limitant le nombre de coupe). Il s'agit ici de trier et decouper une map afin de la rendre plus rapide a lire. Attention le render n'est pas au point.
Structure des noeux :

Node {

  struct segement;
  
  side[0] *FRONT*
  
  side[1] *BACK*
  
  
}

source de travail:

- Black Book : http://orangeti.de/OLD/graphics_programming_black_book/html/index.html
- http://deptinfo.unice.fr/twiki/bin/view/Minfo03/RapportMedioniXavier#Initialisation_de_la_bounding_bo
- http://deptinfo.unice.fr/twiki/bin/view/Minfo03/AlgosJeux3DRapport#Ray_Casting_impl_mentation
