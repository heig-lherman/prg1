# Idée principale
CONSTANTE : Argent de départ = 100'000 (USD)
CONSTANTE : période = 1250
Nombre d'actions : double
- Récupération de l'ensemble des dates (jours ouvrés uniquement)
- Récupération du # de jours
- Pour chaque jour à partir du 200ème  
  - si J + période <= # jours
    - Mise en place des stratégies (HOLD, MA20, MA50, MA100, MA200, EMA20, EMA50, EMA100, EMA200)
    - Enregistrement du résultat dans une table prévue à cet effet
  - sinon fin de la boucle
- Pour chaque stratégie (dans le tableau de résultat), calculer les pourcentiles (10, 50, 90) et les écrire dans le CSV final

# Statégies 
## Stratégie statique - HOLD
Si jour 1 : achat à la valeur d'ouverture  
Si jour 1250 : vente à la valeur de fermeture  
Sinon : aucune action

## Stratégies dynamiques - MA et EMA
Pour chaque jour de l'échantillon (1 à 1250)
1. Calcul de l'indice (MA ou EMA) pour l'ordre STOP
2. Vérification si l'ordre STOP a lieu
3. Si achat ou vente effectuée, calcul des frais et du nouveau solde cash / actions

### Calcul des indices
#### MA - Calcul de la moyenne mobile (arithmétique)
- Prendra en paramètre le nombre de jours utilisés pour le calcul ( ex : MA20 -> 20 jours) et la dernière date de l'échantillon   
- Retourne la moyenne mobile : somme des cours de fermeture des x derniers jours / x

#### EMA - Calcul de la moyenne mobile exponentielle
/!\ Fonction récursive !    
Constante : SMOOTHING = 2 (Valeur la plus souvent utilisée)    
- Prendra en paramètre le nombre de jours utilisés pour le calcul ( ex : EMA20 -> 20 jours) et l'indice du jour actuel
- multiplier = smoothing / (# de jours d'observation + 1) (Aussi appellé Smoothing factor)
- Retourne la moyenne mobile exponentielle : prix de fermeture*multiplier+EMA(jour d'avant)*(1-multiplier)
Note : EMA(1er jour) = valeur de fermeture du 1er jour, EMA(2eme jour) selon la formule

# Autres fonctions nécessaires
- Calcul de la valeur moyenne pour une journée
  - @param : à discuter
    - HIGH, LOW
    - tableau la date [close,open,high,low]
  - return (HIGH + LOW )/ 2
  

- Ordre STOP -> bool function shouldTriggerStopOrder(......);
  - @param : indice, valeurs du jour, # d'actions (si 0 action -> on est en cash et on veut acheter), montant transaction
  - Si vente ET indice <= cours ouverture  OU achat ET indice >= cours ouverture : return true (ref=cours d'ouverture)
  - Si indice traversé : return true (ref=indice)
  - Sinon, return false

  
- Si un indice est traversé durant la journée
  - @param : à discuter indice
    - indice, HIGH, LOW
    - indice, tableau la date [date,close,open,high,low]
  - Si indice >= LOW ET indice <= HIGH : return true
  - Sinon : return false


- Calcul du nouveau solde
  - @param : montant total de la strat, montant de la transaction = 0
  - calcul des frais si montant de la transaction =/= 0
  - return montant total - frais


- Calcul des frais
  - @param : montant de la transaction
  - return 10 + 0.1% * montant de la transaction
    - 2 chiffres après la virgule sont suffisant puisqu'on travaille avec des USD


- Si un jour est ouvrable
  - Vérifie si une date du CSV est un jour ouvré ou non => jour où la bourse est fermée = [date,*,*,*,*,*]
  - retourne true ou false


- Calcul des pourcentiles
  - @param : liste de valeurs, pourcentile cherché (ex: 90% -> 0.9)
  - Trier les valeurs de la plus petite à la plus grande
  - rank = pourcentile * # de valeurs
  - Retourne la valeur à l'indice rank+1 si rank est un entier, rank arrondi à l'entier supp sinon  