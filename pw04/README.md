# Investir 

Le but de ce laboratoire est d'analyser plusieurs stratégies d'investissement. Pour ce faire, 
vous disposez des données historiques de l'indice 
S&P 500 de la bourse américaine depuis février 1997 jusque novembre 2021. 

## Données à analyser

Observons le fichier [gspc.csv](./gspc.csv). Après le header (première ligne), 
chaque ligne de ce fichier regroupe les données suivantes 

~~~
date,close,open,high,low,volume
~~~

Les jours où la bourse est ouverte, la ligne correspondante ressemble à ceci 

~~~
03.11.21,4660.57,4630.65,4663.46,4621.19,3339440000
~~~

ce qui signifie que les 3 novembre 2021, la bourse à ouvert à 4630.65 points, qu'elle a varié 
entre 4621.19 et 4663.46 points, et qu'à la clotûre elle cotait 4660.57 points. Un total de
3339440000 titres ont été échangés. 

Le lendemain, on lit la ligne suivante : 

~~~
04.11.21,4680.06,4662.93,4683.00,4662.59,3332940000
~~~

On note que la cote d'ouverture de 4662.93 points est différente de celle de clôture de la veille, 
le cours des actions qui compose l'indice continuant de varier "hors marché".

Les jours où la bourse est fermée (week-ends et jours fériés US), la ligne 
correspondante ressemble à ceci : 

~~~
07.04.13,*,*,*,*,*
~~~

Dans le cadre de notre problème, seuls les jours ouvrables comptent. On 
peut entièrement ignorer les jours où la bourse est fermée. 

## Evaluation des stratégies d'investissement

On considèrera par la suite différentes stratégies d'investissement. Pour les évaluer, 
on mesurera leur retour sur investissement (ROI) pour un investissement 
de 100'000 USD sur une période de 1250 jours ouvrables de la bourse, 
ce qui correspond environ à 5 ans. 

Pour ce faire, on applique chacune des stratégies d'investissement à toutes les périodes de 
1250 jours ouvrables disponibles dans notre ensemble de données. La plus ancienne commencera 
201 jours ouvrables après le 10 février 1997, 200 jours étant nécessaires à 
certaines stratégies d'investissement pour calculer leurs paramètres. La plus récente 
ira approximativement de novembre 2016 à novembre 2021. Cela représente un peu moins de 
5000 périodes de 5 ans à tester, qui nous fournissent un peu moins de 5000 ROIs. 

Le but de l'évaluation est de produire 3 nombres qui correspondent au 10ème pourcentile, à la médiane
et au 90ème pourcentile de la distribution de ces ROIs. Par exemple, le 10ème pourcentile 
correspond à un ROI tel que 10% des ROIs sont plus petits que lui, et 90% sont plus grands.
Cela nous permet de comparer les stratégies en fonction du retour attendu (la médiane), et de choisir 
en fonction de notre espérance de gain mais aussi de notre tolérance au risque. 

## Stratégies considérées 

La première stratégie considérée se nomme HODL (Hold On for Dear Life). Elle consiste 
simplement à acheter un Exchange Traded Fund (ETF) qui tracke le S&P 500 au début de 
la période des 5 ans, et à le revendre le dernier jour. 

Le deuxième type de stratégie consiste a utiliser l'analyse technique pour acheter et 
vendre cet ETF en fonction de l'évolution des cours. Un des indicateurs techniques 
les plus simples consiste à comparer le cours actuel à la moyenne arithmétique 
mobile des cours de fermetures des N jours précédents. On désire être investi 
lorsque le cours est supérieur à cette moyenne mobile et se replier sur du 
cash lorsque le cours est inférieur à la moyenne mobile. Les durées N typiquement 
considérées sont N = 10, 20, 50, 100 et 200. On nommera les stratégies de ce type 
MA10, MA20, MA50, MA100 et MA200 (MA pour moving average)

La dernière stratégie est similaire à la précédente mais utilise la moyenne 
mobile exponentielle à la place de sa version arithmétique. Vous trouverez 
la définition de cette moyenne exponentielle sur
[investopedia.com](https://www.investopedia.com/terms/e/ema.asp). La moyenne 
mobile exponentielle au jour j se calcule à partir de la moyenne mobile exponentielle 
au jour j-1 et du cours de clotûre au jour j. 
On considèrera les mêmes N que précédemment. On nommera les stratégies de ce type
EMA10, EMA20, EMA50, EMA100 et EMA200 (EMA pour exponential moving average)

## Mise en oeuvre des stratégies actives

Pour les stratégies actives, leur mise en oeuvre consiste chaque soir après 
la clotûre du marché, à calculer la valeur de la moyenne mobile choisie et à passer
un [ordre stop](https://www.investopedia.com/terms/s/stoporder.asp) à ce niveau 
pour le jour suivant. 

Si l'on est actuellement pas investi (i.e. notre argent est en cash), on 
passe un ordre d'achat à la valeur choisie valable un jour. Son effet est le suivant: 
* si le cours d'ouverture est supérieur à cette valeur, l'argent est investi au cours 
d'ouverture. 
* sinon, si le cours du jour traverse la valeur choisie - i.e. elle se trouve entre les cours hauts et bas du jour - l'argent est investi au cours choisi.
* sinon, l'argent reste en cash. 

Symmétriquement, si l'on est actuellement investi dans le S&P 500, on passe un
ordre de vente à la valeur choisie valable un jour. Son effet est le suivant:
* si le cours d'ouverture est inférieur à cette valeur, l'indice est vendu à ce cours d'ouverture
* sinon, si le cours du jour traverse la valeur choisie - i.e. elle se trouve entre les cours hauts et bas du jour - l'indice est vendu au cours choisi.
* sinon, l'indice n'est pas vendu et on reste investi. 

Dans toutes ces stratégies actives, le premier jour on applique la stratégie des autres
jours, et donc on achète au cours d'ouverture si celui-ci est supérieur à la moyenne
mobile, au cours de la moyenne mobile si le cours d'ouverture est inférieur et que 
l'évolution du jour la traverse, et on reste en cash sinon. Le dernier jour - si l'on est 
investi à ce moment - on liquide notre position au cours de clotûre. 

Par ailleurs, chaque transaction d'achat ou de vente entraine des frais fixes 
de 10 USD et des frais variables de 0.02% du montant de la transaction.

## A rendre ... 

Pour ce laboratoire, vous devez rendre une table de 9 lignes et 3 colonnes
reprenant les 9 stratégies considérées ainsi que leurs ROIs attendus au 
10ème, 50ème et 90èmes pourcentiles, ainsi que le code C++ permettant de la
générer. 

Vous pouvez utiliser sans limite les outils disponibles dans les librairies
vector, array, algorithm, numeric, string, fstream, et sstream de la STL.
