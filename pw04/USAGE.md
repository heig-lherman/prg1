# Instructions d'utilisation

### Compilation de l'exécutable

Dans CLion, le plus simple est de charger le CMakeLists.txt dans le dossier all en faisant
clic droit -> Load CMake project. Cela va charger toutes les targets présentes dans le projet.

Pour compiler seulement l'exécutable final, les commandes suivantes peuvent être effectuées
à la racine du repo:

```shell
cmake -Sstandalone -Bbuild  -DCMAKE_BUILD_TYPE=Release 
cmake --build build
```

### Lancement de l'exécutable

Si vous avez choisi d'utiliser le CMakeLists.txt du dossier all dans CLion, la target InvestorStandalone
lance l'executable avec les options par défaut. Il faut néanmoins préciser le "working directory" en modifiant
la configuration de la target pour qu'elle pointe à la racine du repository (là ou les données GSPC sont placées).

Pour l'exécutable compilé avec cmake:

```
# détailler la liste des options
./build/Investor --help

# Lancer le traitement avec les paramètres par défaut
./build/Investor
```

### Fichier d'entrée

Par défaut, l'exécutable va chercher le fichier gspc.csv dans le current working directory, mais ce paramètre peut être
changé de deux manières:

##### Passage par cin

En utilisant le flag `-0`, le fichier va être récupéré de stdin, par exemple:

```shell 
cat ./gspc.csv | ./build/Investor -0
```

##### Passage par chemin d'accès

En utilisant le flag `-i`, le fichier va être récupéré par chemin d'accès, par exemple:

```shell 
./build/Investor -i /path/to/gspc.csv
```

### Paramètres

Nous avons ajouté à ce projet quelques paramètres qui peuvent être changés pour configurer
les options utlisées lors des calculs des stratégies.

Tous les paramètres sont décrits dans la commande avec le flag `--help` : `./build/Investor --help`.

Il est par exemple possible de calculer uniquement les stratégies HODL et EMA en utilisant les flags `-s HODL -s EMA` et
les stratégies dynamiques peuvent aussi avoir les périodes de calculs changées avec le flag `-t` (e.g. `-t 10,20`).

La période d'investissement, la quantité de cash initiale ou les frais d'achats et de vente peuvent aussi être configurés.

Les pourcentiles affichés peuvent aussi être changés en spécifiant le paramètre `-p` (e.g. `-p 0 -p 0.5 -p 1`).

### Fichier de sortie

Par défaut, les résultats sont affichés sous forme de CSV dans stdout. Ce comportement peut être changé en ajoutant le flag
`-o` qui permet de spécifier un chemin de sortie, par exmeple:

```shell 
./build/Investor -o /path/to/output.csv
```
