# Contexte

Le but du projet est de manipuler des données de grande taille pour étudier expérimentalement la complexité des algorithmes Les données sont celles du recensement réalisé en France en 2018, 
qui concerne 19 millions de personnes1 : https://www.insee.fr/fr/statistiques/5395740?sommaire=5395764. 
Il faut récupérer un des fichiers CSV2 par zone, d’environ 100Mo3. La première ligne du fichier ne contient pas de données mais les noms des 97 colonnes. 

## Objectif 

* le but est d’écrire un programme pour charger les données et évaluer expérimentalement le temps de chargement.
Il faut récupérer pour chaque ligne au moins les valeurs suivantes : l’âge (AGED, 6e colonne), la profession (PROF, 76e colonne) et la superficie du logement (SURF, 85e colonne).
 Pour charger ces valeurs, il faut créer des enregistrements et des tableaux selon les besoins.
* Écrire deux fonctions qui trient les données (par exemple par âge), selon deux des méthodes de tri.
 Mesurez les temps de calcul des tris en fonction du nombre d’éléments triés, stockez ces temps dans un fichier CSV et utilisez un tableur pour tracer les courbes expérimentales de complexité des tris.
* écrire du code qui mélange les données, afin de pouvoir les re-trier sans avoir besoin de les recharger à partir du fichier. Mélanger les données dans un tableau peut se faire en parcourant le tableau et en échangeant le contenu de la case courante avec celui d’une autre case tirée au hasard parmi les cases non encore mélangées.  
