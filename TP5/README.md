# Séances 6 et 7


## Filtre médian

On considère une image en niveaux de gris $`f`$ et une fenêtre $`M`$ de taille $`(n\times n)`$, où $`n`$ est un entier impair. Le résultat du filtre médian  de $`f`$ par $`M`$ est obtenu par la procédure suivante :

Pour tous les points p de l'image $`f`$ : 
- on considère la liste des valeurs des points contenus dans la fenêtre M centrée en p ;
- on trie cette liste et on en détermine la valeur *médiane* (valeur en position centrale de la liste triée) ;
- on écrit cette valeur médiane au point p de l'image résultante.
       
### Travail à réaliser

Implanter l'opérateur de filtre médian et écrire un programme de test qui prend en paramètre : le nom d'une image d'entrée, le nom d'une image de sortie, et la taille du filtre.

Quelques conseils :

- Vous pourrez vous appuyer sur la classe `std::vector` pour gérer la liste des valeurs voisines.
- La méthode `std::vector::push_back` permet d'insérer un élément en queue de liste.
- On considère que les points voisins situés en dehors de l'image n'ont pas d'influence sur le résultat. On ajoutera dans la liste uniquement les voisins situés à *l'intérieur* de l'image. La taille de la liste variera donc en fonction de la position du point considéré.
- Afin de trier la liste, on pourra utiliser la méthode `std::sort`. 
  Voir : [http://www.cplusplus.com/reference/algorithm/sort/](http://www.cplusplus.com/reference/algorithm/sort/)


## Modélisation du bruit

### Bruit impulsionnel

Écrire une fonction permettant d'ajouter du bruit impulsionnel (ou *poivre et sel*) à une image. La probabilité $`p`$ qu'un pixel
de l'image soit corrompu, avec $`0\leq p \leq 1`$, sera passée en paramètre. 
Chaque pixel corrompu peut être blanc (valeur 255) ou noir (valeur 0) avec une probabilité 0.5 (une chance sur deux).
Vous pourrez vous appuyer sur la fonction `rand()`  ou utiliser la classe `std::uniform_int_distribution`.
Voir : [http://www.cplusplus.com/reference/random/uniform_int_distribution/](http://www.cplusplus.com/reference/random/uniform_int_distribution/)

### Bruit gaussien

Écrire une fonction permettant d'additionner à une image un bruit gaussien de  moyenne $`\mu`$ et d'écart-type $`\sigma`$.
Dans ce modèle de bruit, tous les pixels de l'image sont corrompus : la nouvelle valeur d'un pixel est calculée en ajoutant à la valeur d'origine une valeur aléatoire suivant la loi de probabilité gaussienne $`\mathcal{N}(\mu,\sigma^2)`$. On effectue une troncature sur l'image bruitée : si un pixel a une valeur négative, on la ramène à 0 ; si un pixel a une valeur qui dépasse 255, on la ramène à 255.
Vous pourrez utiliser la classe *std::normal\_distribution* du C++ 11.
Voir : [http://www.cplusplus.com/reference/random/normal_distribution/](http://www.cplusplus.com/reference/random/normal_distribution/)



## Mean Square Error

On introduit une mesure notée MSE, de la dissimilarité entre deux images I et I' de mêmes dimensions $`N\times M`$, définie par :  

```math
MSE(f,f')=\frac{\sum_{x=0}^{N-1} \sum_{y=0}^{M-1} (f(x,y)-f'(x,y))^2}{NM}
```

Cette grandeur permet en particulier de mesurer l'écart entre une image $`f`$ et une version bruitée $`f'`$ de I, ce qui justifie la terminologie d'erreur quadratique moyenne, ou *mean square error*, et l'acronyme MSE.


- Écrire une fonction *computeMSE* qui  retourne la valeur de MSE entre deux images.
 
 
## Tests

Générer les images suivantes à partir de l'image *grumpy.pgm* : 

- Bruit impulsionnel de 15% ;
- Bruit impulsionnel de 40% ;
- Bruit gaussien de moyenne $`\mu=0`$ et d'écart-type $`\sigma=15`$ ;
- Bruit gaussien de moyenne $`\mu=0`$ et d'écart-type $`\sigma=30`$.

Calculer ensuite le MSE entre l'image bruitée et l'image de référence puis entre l'image débruitée et l'image de référence en utilisant les filtres suivants :

- Filtre médian de taille 3 ;
- Filtre médian de taille 7 ;
- Filtre moyenneur de taille 2N+1=3 ; 2N+1=7 ;
- Filtre gaussien avec $`\sigma=1`$ ; $`\sigma=2`$.

Faire un tableau résumant les résultats obtenus ; le meilleur résultat pour chaque type d'image sera mis en valeur (par exemple fonte grasse ou colorée).