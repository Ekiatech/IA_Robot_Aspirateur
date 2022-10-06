# IA_Robot_Aspirateur

Pour compiler le projet faire :
```make```

Pour exécuter le projet faire :
```./main```

Plusieurs options sont disponibles :
- -a : pour choisir l'algorithme utiliser pour le nettoyage. $0$ pour l'algorithme informée, $1$ pour l'algorithme non informée. Par défaut, c'est l'algorithme informée qui est exécutée.
- -d : pour modifier la profondeur d'exploration de l'algorithme informée. Par défaut, cette valeur est fixée à 8.
- -e : pour modifier l'énergie initiale du robot. Par défaut, cette valeur est fixée à $2000$.
- -n : pour modifier la taille du côté du plateau. Par défaut, cette valeur est fixée à $5$.

Exemple de commandes :
```./main -n 8 -d 4```

## Explication de la vidéo sur l'algorithme BFS

### Découpage de la vidéo

* Phase d'**apprentissage** **n°1** : ** 0:0 - 3:45 **
    * Nombre d'action du robot avant recalcul de la case avec objet la plus proche = **1** : ** 0:0 - 0:32 **
    * Nombre d'action du robot avant recalcul de la case avec objet la plus proche = **2** : ** 0:32 - 0:45 **
    * Nombre d'action du robot avant recalcul de la case avec objet la plus proche = **3** : ** 0:45 - 1:30 **
    * Nombre d'action du robot avant recalcul de la case avec objet la plus proche = **4** : ** 1:30 - 1:53 **
    * Nombre d'action du robot avant recalcul de la case avec objet la plus proche = **5** : ** 1:53 - 2:07 **
    * Nombre d'action du robot avant recalcul de la case avec objet la plus proche = **6** : ** 2:07 - 2:44 **
    * Nombre d'action du robot avant recalcul de la case avec objet la plus proche = **7** : ** 2:44 - 3:13 **
    * Nombre d'action du robot avant recalcul de la case avec objet la plus proche = **8** : ** 3:13 - 3:45 **
* Phase normale **n°1** : ** 3:45 - 4:19 **
* Phase d'**apprentissage** **n°2** : ** 4:19 - 9:45 **

### Légende de l'affichage

Une représentation de la *map* est affichée lors de la recherche.

On peut observer quelles cases sont visitées et dans quel ordre à l'aide du code couleur suivant :
* case blanche = la case n'a pas encore été visitée, la node correspondant à cette case n'est donc pas dans la file
* case rouge = la case a été visitée et la node correspondante est dans la file
* case violette = la case a été visitée et la node correspondante était dans la file mais en a été retirée

Ainsi, au fur et à mesure des changements de couleurs des case, on peut voir le déroulement de la recherche **BFS**.

*Remarque : le temps de phase est très cours ainsi que le nombre d'actions en phase d'apprentissage pour les besoins de la vidéo.*