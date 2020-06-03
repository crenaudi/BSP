# BSP

Il s'agit ici de faire un bsp sur le model de celui mis au point par John Carmak pour DOOM. L'arbre binaire doit classer chaques segments de la map suivant ce model:

Node
{

  coordonnee segement;
  
  side[0] node svt devant
  
  side[1] node svt derriere
  
}

Une segment B devant/derriere un segment A est aussi le plus proche devant/derriere A.
Notons qu'un segment B traversant l'air d'un autre segment A sera decoupeé en deux autres segments distinct, l'un etant devant A, l'autre derriere A.
