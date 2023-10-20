# L5b - Généricité simple

Dans cette deuxième partie du laboratoire, vous devez transformer 
votre classe `Frac16` en une classe générique `Frac<T>` où 
l'argument générique `T` spécifie le type utilisé pour stocker
les numérateur et dénominateur. Les données sont donc stockées
sous la forme 

```c++
template<typename T>
class Frac {
public:

private:
   bool isNegative;
   T numerator, denominator;
};
```

Cette classe ne doit accepter de compiler qu'avec en argument
générique un type entier non signé dont le nombre de bits ne dépasse 
pas 32, de sorte que les calculs avec débordement puissent utiliser
le type `unsigned long long` pour les résultats intermédiaires.  
Cette contrainte doit être mise en oeuvre via `static_assert` et
éventuellements des fonctionalités offertes par les librairies 
[`<limits>`](https://www.cplusplus.com/reference/limits/) et
[`<type_traits>`](https://www.cplusplus.com/reference/type_traits/).

Les opérateurs unaires `-, ++, --, ++(int), --(int)` et binaires `+=, -=, *=, /=, +, -, *, /, ==, !=, <, >, <=, >=, <<` doivent être fournis, ainsi que le constructeur
a partir de zéro, un ou deux arguments de type `T`. 

Vous pouvez tester votre classe avec le programme [`main.cpp`](main.cpp) fourni. 
Il doit générer la sortie [`output.txt`](output.txt) à la sortie standard.  