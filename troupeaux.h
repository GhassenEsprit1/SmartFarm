#include<gtk/gtk.h>

typedef struct troup
{
char id[100];
char date[100];
char poids[100];
char ref[100];
char type[100];
char sexe[100];
}troup;

void ajouter(troup t);
void afficher(GtkWidget *liste);
void supprimer(troup t);
void modifier(troup ta);
void chercher ( char *idchercher,GtkWidget *liste );
int calcul(char *types);

