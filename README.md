# BSP

Il s'agit ici de faire un bsp sur le model de celui mis au point par John Carmak pour DOOM. L'arbre binaire doit classer chaque segment de la map de maniaire obtimal suivant le model suivant :

Node
{

  coordonnee segement;
  
  side[0] segment suivant devant celui ci
  
  side[0] segement suivant derriere celui ci
  
}


Notons qu'un segment B traversant l'air d'un autre segment A sera decouper en deux autres segments distinct, l'un etant devant A, l'autre derriere A.
