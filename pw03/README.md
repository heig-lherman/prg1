# Arithmétique

Le but de ce laboratoire est de mettre en oeuvre les opérations arithmétiques d'addition et multiplication
sur un type de données nous permettant de stocker des entiers non-signés au format décimal (base 10).

Le format de donnée choisi est un tableau brut de __unsigned char__, avec 2 entiers non signés de type __size_t__ pour la 
taille et la capacité. Chaque __unsigned char__ stocke un nombre décimal entre 0 et 9. Dans le tableau, l'élément d'indice 
0 correspond aux unités, celui d'indice 1 aux dizaines, celui d'indice 2 aux centaines, ... Les chiffres d'indice >= taille 
sont ignorés. 

Pour rendre les choses plus claires, on définit le type __longMath::DigitType__ comme un alias de __unsigned char__

~~~
namespace longMath {
    using DigitType = unsigned char;
    
    std::string to_string(DigitType const tab[], size_t n);
    bool from_string(...); // prototype à compléter
    void add(...);  // prototype à compléter
    void multiply(...);  // prototype à compléter
}
~~~

A la fin de ce laboratoire, nous serons capables de calculer des additions et des multiplication avec des nombres de 
100 chiffres décimaux. 

## Objectifs pédagogiques

* Mise en oeuvre de divers algorithmes de parcours et manipulation de tableaux de type C. 
* Déclaration et définition de fonctions avec passage de tableaux variables ou constants, et d'entiers par valeur ou par référence
* Découverte de la librairie de tests en C++ [catch2](https://github.com/catchorg/Catch2)

## Le code fournit

Le projet qui vous est fourni génère 2 cibles. 

* L3-LongMath est générée à partir du fichier main.cpp et fournit une calculatrice élémentaire capable d'effectuer 
des calculs modulo 10^100.  
* L3-TestLongMath est générée à partir des fichiers situés dans le répertoire Test qui utilisent catch2. 
Ils permettent de tester le bon fonctionnement de vos fonctions via 30 tests indépendants. 

Je vous fournit également les fichiers longmath.h et lm_*.cpp à compléter par vos
soins pour que les 2 cibles compilent et que tous les tests passent au vert. 
La fonction to_string est fournie. 

## Vos tâches

Votre travail consiste à déclarer et définir les 3 fonctions suivantes
* __from_string__ : écrit le nombre fourni sous forme de chaine de caractère dans un tableau 
de longMath::DigitType passé en paramètre, dont la capacité est également passée en paramètre. Elle modifie 
la taille de ce tableau passé en paramètre et retourne un booléen qui vaut __true__ si la conversion s'est 
bien déroulée et __false__ sinon. 
* __add__ : additionne les nombres représentés par 2 tableaux passés en paramètres et stocke le résultat dans 
un troisième. Les tailles et capacité pertinentes sont également passées en paramètres. 
* __multiply__ : multiplie les nombres représentés par 2 tableaux passés en paramètres et stocke le résultat dans 
                 un troisième. Les tailles et capacité pertinentes sont également passées en paramètres.  

Le fichier d'en-tête ne doit déclarer que ces fonctions et aucune autre, 
mais vous pouvez évidemment définir d'autres fonctions que celles-là dans les fichiers .cpp si cela permet de rendre
votre code plus simple / clair / élégant. 

Le prototype exact des fonctions ci-dessous à écrire devrait être clair à la lecture des appels effectués depuis le 
fichier __Test/longmathTest.cpp__

## A rendre 

Faites un fork de ce repository, cachez le aux autres groupes mais laissez
le accessibles aux membres de votre groupe et aux professeur et assistant

Soumettez l'URL de votre repository dans le devoir sur cyberlearn