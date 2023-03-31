# Projet Complexité et Récursivité

Ce travail à été réalisé par Antoine Mathieu, Raphaël Sève et Nathan Odic.


## Définition du Problème

Pour ce problème nous disposons d’une grille avec dans les cases marquées les mois, les jour de la semaine, le numéro du jour ainsi que 10 pièces.
![Le Calendrier et les pièces](https://img.staticdj.com/fc961127b84d191174ff7c95ce8ecce8.jpg)
Le principe de ce puzzle est que chaque jour il faut remplir la grille avec 10 pièces pour ne laisser que 3 trous celui du mois du jour et du numéro de la journée. Par exemple si on est le lundi 18 mai alors il ne doit rester plus que les cases mai, 18 et lundi de visible.

Notre objectif est de réaliser un code en C permettant de compter le nombre de solutions différentes pour une journée choisie.

## Explication du Code
### Préparation
On commence tout d'abord par définir le calendrier et les pièces sous formes de tableaux de 0 et de 1. Pour le calendrier, les 1 représentent les cases remplies (donc inaccessibles) et pour les pièces ils représentent la forme de la pièce.
On appelle ensuite une fonction *indiquerJour* qui nous permet de choisir avec quel jour on veut travailler. Cette fonction ajoute des 1 aux cases du jour choisi, qui deviennent alors inaccessibles.
La fonction *completerPieces* s'occupe ensuite de créer un tableau des 10 pièces avec les rotations, soit 34 pièces, en enlevant les pièces symétriques.

### Solveur

On appelle ensuite notre solveur récursif *trouverSolutions*.
Cette fonction réalise plusieurs tâches :

 - La fonction prend deux paramètres, x et y, qui sont des coordonnées dans un calendrier, et elle renvoie un entier qui indique le nombre de solutions trouvées.
 - La première partie de la fonction vérifie si toutes les pièces ont été placées, auquel cas elle incrémente le compteur de solutions et renvoie 1.
 - Ensuite, la fonction vérifie si les coordonnées x et y sont valides. Si ce n'est pas le cas, elle renvoie 0.
 - La variable "resolu" est initialisée à 0 et elle est mise à 1 si la case (x, y) du calendrier est vide. Sinon, elle est mise à 0.
- La fonction boucle ensuite sur toutes les pièces possibles. Si une pièce n'a pas encore été utilisée, et si elle peut être placée dans le calendrier à la position (x, y), alors la fonction l'ajoute au calendrier, marque la pièce comme utilisée et stocke les informations de placement dans un tableau. Elle incrémente également le compteur de pièces placées.
- La fonction vérifie ensuite si la pièce actuellement placée est la première à être placée dans la case (x, y). Si c'est le cas, elle continue la recherche de solutions. Sinon, elle retire la pièce du calendrier et met à jour les variables pour indiquer qu'elle n'est plus utilisée, qu'elle n'est plus placée et que le nombre de pièces totales a diminué.
- Enfin, la fonction calcule les nouvelles coordonnées de la case suivante et appelle récursivement la fonction "trouverSolutions" avec ces nouvelles coordonnées.
- Si "resolu" est toujours à 0, cela signifie qu'aucune pièce n'a été placée dans la case (x, y), donc la fonction continue la recherche de solutions sans ajouter de pièce.
- Enfin, la fonction renvoie 0, dans le cas ou aucune solution n'a été trouvée.

## Résultats
Voici nos résultats pour 31 triplets. On précisera tout de même que dans notre code le jour est défini entre 1 et 7, avec 1 pour Lundi et 7 pour Dimanche.
Nous avons réalisé deux mesures de temps, une avec XCode (qui contient le temps de compilation), dont les résultats sont dans la colonne CPU, et une seconde mesure avec le programme déjà compilé avec la commande :
**gcc -o main main.c calendrier.c main.c -O3**


| Date                  | Mois | Quantième | Jour | Nombre de solutions | CPU (seconde) | CPU (seconde) (compilation O3) |
| --------------------- | ---- | --------- | ---- | ------------------- | ------------- | ------------------------------ |
| Samedi 1er janvier    | 1    | 1         | 6    | 54                  | 0,345         | 0,08                           |
| Jeudi 15 novembre     | 11   | 15        | 4    | 40                  | 0,553         | 0,11                           |
| Jeudi 11 juin         | 6    | 11        | 4    | 45                  | 0,379         | 0,087                          |
| Mercredi 13 décembre  | 12   | 13        | 3    | 23                  | 0,331         | 0,077                          |
| Vendredi 3 décembre   | 12   | 3         | 5    | 16                  | 0,267         | 0,068                          |
| Jeudi 12 octobre      | 10   | 12        | 4    | 18                  | 0,17          | 0,049                          |
| Samedi 27 avril       | 4    | 27        | 6    | 50                  | 0,427         | 0,081                          |
| Lundi 23 janvier      | 1    | 23        | 1    | 50                  | 0,591         | 0,113                          |
| Mardi 7 février       | 2    | 7         | 2    | 79                  | 0,515         | 0,094                          |
| Dimanche 12 mars      | 3    | 12        | 7    | 4                   | 0,134         | 0,042                          |
| Jeudi 27 avril        | 4    | 27        | 4    | 20                  | 0,422         | 0,09                           |
| Mardi 23 mai          | 5    | 23        | 2    | 78                  | 0,342         | 0,079                          |
| Mercredi 7 juin       | 6    | 7         | 6    | 85                  | 0,933         | 0,166                          |
| Vendredi 21 juillet   | 7    | 21        | 5    | 7                   | 0,332         | 0,077                          |
| Samedi 5 août         | 8    | 5         | 6    | 41                  | 0,315         | 0,076                          |
| Mercredi 20 septembre | 9    | 20        | 3    | 26                  | 0,352         | 0,08                           |
| Lundi 2 octobre       | 10   | 2         | 1    | 3                   | 0,168         | 0,047                          |
| Dimanche 12 novembre  | 11   | 12        | 7    | 16                  | 0,345         | 0,079                          |
| Dimanche 31 décembre  | 12   | 31        | 7    | 37                  | 0,575         | 0,103                          |
| Jeudi 11 janvier      | 1    | 11        | 4    | 25                  | 0,37          | 0,082                          |
| Lundi 12 février      | 2    | 12        | 1    | 4                   | 0,229         | 0,06                           |
| Vendredi 30 mars      | 3    | 30        | 5    | 16                  | 0,344         | 0,078                          |
| Mardi 10 avril        | 4    | 10        | 2    | 51                  | 0,231         | 0,06                           |
| Mercredi 23 mai       | 5    | 23        | 3    | 48                  | 0,355         | 0,071                          |
| Samedi 9 juin         | 6    | 9         | 6    | 46                  | 0,427         | 0,076                          |
| Vendredi 20 juillet   | 7    | 20        | 5    | 30                  | 0,329         | 0,067                          |
| Mercredi 15 août      | 8    | 15        | 3    | 37                  | 0,474         | 0,09                           |
| Samedi 1er septembre  | 9    | 1         | 6    | 52                  | 0,307         | 0,064                          |
| Mardi 23 octobre      | 10   | 23        | 2    | 46                  | 0,276         | 0,056                          |
| Dimanche 25 novembre  | 11   | 25        | 1    | 32                  | 0,656         | 0,116                          |
| Mercredi 27 décembre  | 12   | 27        | 3    | 0                   | 0,438         | 0,093                          |


On note que tous les mercredis 27 ne semblent pas fonctionner.
On obtient de très bons résultats (normal on est bons nous aussi) et il serait facile et rapide de vérifier toutes les dates possibles avec notre algorithme tant il est rapide.
