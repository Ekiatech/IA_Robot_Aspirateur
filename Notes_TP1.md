# Notes TP1

.Structures :
1. carte
2. robot
3. capteurs
4. effecteurs
5. object

## Carte

Damier carré de 25 pièces minimum (doit pouvoir être variable).

Contient : une liste d'objets sur chaque case.

Pour chaque case de la carte, on peut avoir :
1. rien
2. 1 bijou
3. 1 poussière
4. 1 bijou & 1 poussière

Des objets sont générés aléatoirements sur la carte (avec des probabilités choisies).

## Environnement

Boucle infinie.

Possède une mesure de performance.

## Robot

Déplacement (coûte 1) : gauche - droite - bas - haut.

Action (coûte 1) : aspirer poussière & bijou - ramasser bijou

Le robot voit toute la carte.

Possède des capteurs et des effecteurs.

Algorithme : basé sur les buts.

Possède un état mental : BDI (Beliefs - Desires - Intentions).

A chaque boucle, le robot :
1. observe l'environnement avec ses capteurs
2. update son état
3. choisit une action
4. fait l'action

Possède 2 algorithms génériques (sauf heuristique) : informé - non-informé.

Début : exécution à partir des intentions.

Après X itérations (apprentissage) : exécution + exploration. (Le robot doit tenter d'optimiser la fréquence d'exploration).

## Contraintes

1. Robot : 1 thread / Environnement : 1 thread.
2. Poussière / Bijoux : générés sporadiquement par l'environnement.
3. Système de points dans la mesure de performance pour la poussière et les bijoux ramassés.
4. Utiliser les modèles vues en cours.