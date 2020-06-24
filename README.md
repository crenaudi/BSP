# BSP
*WARNING*
Ce travaille est pensee pour fonctionner avec la LIBGFX, production de Pascal Ddelord, et moi meme Camille Renaudin.
Lien : .https://github.com/crenaudi/Libgfx

Arbre binaire suivant le travail de John Carmack avec un tri limitant les coupes, et fonction de rendu ecrite pour un ray casting (impose dans le sujet).
Model de noeux suivant :

Node
{

  coordonnee segement;
  
  side[0] node suivant dont le segment est devant celui ci
  
  side[1] node suivant dont le segment est derriere celui ci
  
}


Notons qu'un segment B traversant l'air d'un autre segment A sera decouper en deux autres segments distinct, l'un etant devant A, l'autre derriere A.
