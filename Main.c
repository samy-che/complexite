#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define CP 75 // colonne de PROF -1
#define CA 5  // colonne de AGED -1
#define CS 84 // colonne de SURF -1
#define LIGNES 2000
typedef char string[1000];
string ligne_fichier;
int AGED[LIGNES];
char PROF[LIGNES][5];
char SURF[LIGNES][2];

typedef struct personne // definition de structure personne
{
    int age;
    char prof[5];
    char surf[2];

} personne;

void echange(int tab[], int index1, int index2)
{
    int tmp;
    tmp = tab[index1];
    tab[index1] = tab[index2];
    tab[index2] = tmp;
}

void melange(int tab[LIGNES])
{
    srand(time(NULL));
    int rd;
    for (int i = 0; i < LIGNES; i++)
    {
        rd = rand() % LIGNES;
        echange(tab, i, rd);
    }
}

void triInsertion(int tab[LIGNES])
{
    int i, j, val;
    for (i = 1; i < LIGNES; i++)
    {
        val = tab[i];
        j = i;
        while ((j > 0) && (tab[j - 1] > val))
        {
            tab[j] = tab[j - 1];
            j = j - 1;
        }
        tab[j] = val;
    }
}

void triSelection(int tab[LIGNES])
{
    int i, j, temp, pg;
    i = LIGNES - 1;
    while (i > 0)
    {
        pg = 0;
        for (j = 0; j <= i; j++)
        {
            if (tab[j] > tab[pg])
                pg = j;
        }
        temp = tab[pg];
        tab[pg] = tab[i];
        tab[i] = temp;
        i = i - 1;
    }
}

void triBulle(int tab[LIGNES])
{
    int i, j, temp, trie;
    trie = 0;
    i = LIGNES - 2;
    while (!(trie) || i > 0)
    {
        trie = 1;
        for (j = 0; j <= i; j++)
        {
            if (tab[j] > tab[j + 1])
            {
                temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
                trie = 0;
            }
        }
        i = i - 1;
    }
}

int recherche_seq(int tab[LIGNES], int nb)
{
    int i, trouve;
    i = 0;
    trouve = 0;
    while (trouve == 0 && i < LIGNES)
    {
        if (tab[i] == nb)
            trouve = 1;
        else
            i++;
    }
    return trouve;
}

int recherche_dichotomique(int tab[LIGNES], int nb)
{
    int debut, fin, mil;

    debut = 0;
    fin = LIGNES - 1;
    mil = (debut + fin) / 2;
    while (tab[mil] != nb && fin > debut)
    {
        if (tab[mil] > nb)
            fin = mil - 1;
        else
            debut = mil + 1;
        mil = (debut + fin) / 2;
    }
    if (tab[mil] == nb)
        return 1;
    return 0;
}
char *strsep(char **stringp, const char *delim)
{
    char *begin, *end;
    begin = *stringp;
    if (begin == NULL)
        return NULL;
    end = begin + strcspn(begin, delim);
    if (*end)
    {
        *end++ = '\0';
        *stringp = end;
    }
    else
        *stringp = NULL;
    return begin;
}

int main()
{
    FILE *fichier = fopen("FD_INDREG_2018.csv", "r");               // création d’un flux sur le fichier pour le lire
    FILE *tmp_char_fichier = fopen("temps_chargement.csv", "a+");   // creation du fichier de temps de calcul pour le chargement
    FILE *tmp_tri_selec = fopen("tri_selection.csv", "a+");         // creation du fichier de temps de calcul pour tri_selection
    FILE *tmp_tri_inser = fopen("tri_insertion.csv", "a+");         // creation du fichier de temps de calcul pour tri_insertion
    FILE *tmp_tri_bulle = fopen("tri_bulle.csv", "a+");             // creation du fichier de temps de calcul pour tri_bulle
    FILE *tmp_recherche_dicho = fopen("recherche_dicho.csv", "a+"); // creation du fichier de temps de calcul pour recherche dichotomique
    FILE *tmp_recherche_seq = fopen("recherche_seq.csv", "a+");     // creation du fichier de temps de calcul pour recherche sequentielle

    // chargement
    clock_t debut = clock();             // debut de chronometre
    fgets(ligne_fichier, 1000, fichier); // on saute une ligne avant de rentrer dans la boucle car la premiere ligne represente les titres
    for (int i = 0; i < LIGNES; i++)
    {
        fgets(ligne_fichier, 1000, fichier); // on recupere la chaine à decouper qui represente une ligne
        char *s = strdup(ligne_fichier);     // on récupère un pointeur sur la chaîne ligne_fichier
        char *token = strsep(&s, ";");       // recuperer le premier token de la ligne avant de rentrer dans la boucle
        for (int j = 0; j < CA; j++)
        {                            // boucle pour recuperer le token d'age qui se trouve à la 6 eme colonne
            token = strsep(&s, ";"); // passer au prochain token
        }
        AGED[i] = atoi(token); // transformer la chaine de charactere age en int pour le stocker dans le tableau AGED de type int

        for (int j = 0; j < CP - CA; j++)
        { // boucle pour recuperer le token de prof qui se trouve à la 76 eme colonne
            token = strsep(&s, ";");
        }
        strcpy(PROF[i], token);
        for (int j = 0; j < CS - CP; j++)
        { // boucle pour recuperer le token de surf qui se trouve à la 85 eme colonne
            token = strsep(&s, ";");
        }
        strcpy(SURF[i], token);
    }
    clock_t fin = clock(); // fin de chronometre

    fclose(fichier);                                     // fermer le flux
    int duree = ((fin - debut) * 1000) / CLOCKS_PER_SEC; // calcul de temps entre debut et fin
    fprintf(tmp_char_fichier, "%d,%d\n", LIGNES, duree); // ecrire sur le fichier csv les nombres de lignes,le temps
    fclose(tmp_char_fichier);                            // fermer le flux

    // on va travailler sur le tableau d'age

    // TRI :

    // tri_selection
    debut = clock();
    triSelection(AGED);
    fin = clock();
    duree = ((fin - debut) * 1000) / CLOCKS_PER_SEC;
    fprintf(tmp_tri_selec, "%d,%d\n", LIGNES, duree);
    fclose(tmp_tri_selec);

    melange(AGED); // on melange le tableau afin d'eviter de charger à partir du fichier csv
    // tri_insertion
    debut = clock();
    triInsertion(AGED);
    fin = clock();
    duree = ((fin - debut) * 1000) / CLOCKS_PER_SEC;
    fprintf(tmp_tri_inser, "%d,%d\n", LIGNES, duree);
    fclose(tmp_tri_inser);

    melange(AGED);
    // tri bulle
    debut = clock();
    triBulle(AGED);
    fin = clock();
    duree = ((fin - debut) * 1000) / CLOCKS_PER_SEC;
    fprintf(tmp_tri_bulle, "%d,%d\n", LIGNES, duree);
    fclose(tmp_tri_bulle);

    // RECHERCHE
    personne john;
    john.age = 200;
    strcpy(john.prof, "aaaa");
    strcpy(john.surf, "a");
    personne doe;
    doe.age = 20;
    strcpy(doe.prof, "bbbb");
    strcpy(doe.surf, "b");

    // tester les deux algo de recherche dans le cas au pire pour le tableau age sur un tableau trié
    // recherche dichotomique
    debut = clock();
    if (recherche_dichotomique(AGED, doe.age) == 1)
        printf("\nl'age %d trouvé avec recherche dichotomique ", doe.age);
    else
        printf("\nl'age %d non trouvé avec recherche dichotomique", doe.age);
    // for(int i =0;i<100000;i++)printf(".");
    fin = clock();
    duree = ((fin - debut) * 1000) / CLOCKS_PER_SEC;
    fprintf(tmp_recherche_dicho, "%d,%d\n", LIGNES, duree);
    fclose(tmp_recherche_dicho);
    // recherche sequentielle
    debut = clock();
    if (recherche_seq(AGED, john.age) == 1)
        printf("\nl'age %d trouvé avec recherche sequentielle", john.age);
    else
        printf("\nl'age %d non trouvé avec recherche sequentielle", john.age);
    // for(int i =0;i<100000;i++)printf(".");
    fin = clock();
    duree = ((fin - debut) * 1000) / CLOCKS_PER_SEC;
    fprintf(tmp_recherche_seq, "%d,%d\n", LIGNES, duree);
    fclose(tmp_recherche_seq);
    // affichage de 20 lignes de chaque tableau
    printf("\n AGED trié :");
    for (int i = 0; i < 20; i++)
        printf("[%d]", AGED[i]);
    printf("\n PROF :");
    for (int i = 0; i < 20; i++)
        printf("[%s]", PROF[i]);
    printf("\n SURF :");
    for (int i = 0; i < 20; i++)
        printf("[%s]", SURF[i]);
}
