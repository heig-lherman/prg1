# L5 - Fractions

<img align="right" src="pythagore.jpeg">
Récemment convertis au Pythagorisme, nous renonçons à utiliser les types réels 
fournis par le C++ et décidons de les remplacer par notre propre classe 
mettant en oeuvre les fractions, seuls nombres non-entiers respectant les 
besoins de notre phylosophie. 

Pour ce faire, vous travaillerez de manière progressive. Dans [l'étape 1](./Partie%201%20-%20Frac16), 
vous écrirez une classe `Frac16` qui stocke le nombre sous la forme de 2 entiers 
non-signés de 16 bits pour le numérateur et le dénominateur, et d'un booléen pour
le signe, i.e. 

```c++
class Frac16 {
public:
   using type = unsigned short;
private:
   bool isNegative;
   type numerator, denominator;
};
```

Par ailleurs, notre classe garantira en permanence que numérateur et dénominateur sont premiers
entre eux en utilisant si nécessaire [l'algorithme d'Euclide](https://fr.wikipedia.org/wiki/Algorithme_d%27Euclide) 
pour en calculer le plus grand diviseur commun. Ce PGCD des numérateurs et dénominateurs doit toujours être de 1
à la fin de toute opération. 

Le seul constructeur fournit permet de spécifier les numérateur et dénominateur, dont les valeurs par 
défaut sont 0 et 1 respectivement. Si l'on veut spécifier une fraction négative, il faut utiliser 
l'opérateur `-` unaire, i.e. on écrira `-Frac16(1,2)` pour `-0.5`. 

Elle met en oeuvre tous les opérateurs classiques sur un type réel: `+,-,*,/` ainsi que les opérateurs
d'incrémentation pré- et post-fixe `++,--` et ceux de comparaison `==,!=,<,>,<=,>=`. Par ailleurs, elle 
fournit une conversion vers le type `double` et un opérateur d'afficage `<<` qui respecte les mêmes
principes que celui de `double` pour `inf` et `nan`. 

Enfin, il faudra faire attention au débordement éventuel lors des calculs en `unsigned short`. Il 
convient de toujours effectuer les calculs avec toute la précision nécessaire, et si après simplification 
du PGCD les nombres sont plus longs que 16 bits, de ne garder que les 16 bits les plus significatifs. 

Un petit programme testant ces fonctionalités vous est fourni ainsi que la sortie attendue.

Dans les étapes [2](./Partie%202%20-%20Frac) et [3](./Partie%203%20-%20Frac(2)) décrites dans leurs
fichiers README.md respectifs, vous rendrez cette classe générique 
pour permettre d'utiliser d'autres types qu'unsigned short pour stocker les numérateur et dénominateur. 

