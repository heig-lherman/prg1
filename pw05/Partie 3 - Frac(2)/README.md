# L5c - Généricité ... moins simple

Enfin, dans cette dernière partie, vous devez modifier la classe 
`Frac<T>` de la partie 2 pour permettre d'écrire 

````c++
   auto fraction = Frac<unsigned char>(1,2) + Frac<unsigned short>(2,3);
````

en permettant donc de convertir et mélanger différents types de `Frac<T>`
dans toutes les opérations pour lesquelles c'est pertinent. 

Pour cela, il faudra écrire un constructeur de copie et 
un opérateur d'affectation effectuant la conversion. Ces conversions
doivent être faites au mieux, i.e. en perdant le moins de précision
possible quand on passe d'un type long à un type plus court. 

Ensuite, il faudra  rendre les méthodes de `Frac<T>` génériques (`template <typename U>`)
pour qu'elles puissent accepter des arguments de type `Frac<U>` avec `T` et `U` pas 
forcément identiques. 

De même il faudra rendre les fonctions non membres génériques avec `template <typename T, typename U>` 
quand elles doivent accepter 2 paramètres de type `Frac<T>` et `Frac<U>`. 

Pour les opérateurs binaires telle que l'addition ci-dessus, le type
de retour doit être le plus grand des 2. Par exemple, le type de 
la variable `fraction` ci-dessus est `Frac<unsigned short>` parce
que `unsigned short` est stocké sur 16 bits, alors que `unsigned char` 
n'en utilise que 8. Si les 2 types ont la même longueur, c'est celui
du premier argument qui est utilisé. 

Pour mettre en oeuvre ceci, l'approche la plus simple consiste à 
* écrire une classe ou struct générique `TypeChooser` avec 3 arguments génériques : les types T et U et un booléen
* spécialiser cette classe pour `true` et `false`, ces deux spécialisations définisant un type avec `using` 
* écrire une classe ou struct générique `LargerType` avec 2 arguments génériques `T` et `U` définissant un type avec `using` comme synonyme d'un type défini par `TypeChooser` 
* le but final étant de pouvoir utiliser `LargerType<T,U>::type` comme un type. 

Vous pouvez tester votre classe avec le programme [`main.cpp`](main.cpp) fourni. 
Il doit générer la sortie [`output.txt`](output.txt) à la sortie standard.  