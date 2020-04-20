struct joueur {
    char nom[20]; /*Nom du joueur*/
    char quoi; /*Sur quoi le joueur mise d--> Don't pass et p--> Pass*/
    int mise; /*Combien le joueur mise*/
    int gain; /* Gain du jouer*/
   };

typedef struct joueur Joueur;

int lance();
/*Renvoie un entier au hasard entre 2 et 12 */
int nb_joueur(void);
/*Renvoie le nombre de joueurs qui a été indiqué sur stdin*/
int init_joueur(int nb_j, Joueur *j);
/* Initialise les attributs de chaque joueurs */
int print_name(Joueur *j, int i);
/* Affiche le nom du ième Joueur*/
char *get_name(Joueur *j, int i);
/* Renvoie le nom du ième Joueur*/
int parie_quoi(Joueur *j, int i);
/* Mets dans l'attribut quoi du ième Joueur p ou d (Pass et don't pass)*/
char get_quoi(Joueur *j, int i);
/* Renvoie ce sur quoi le ième Joueur a parié*/
int parie_cb(Joueur *j, int i);
/* Mets dans l'attribut mise du ieme Joueur l'entier lu sur stdin*/
int get_mise(Joueur *j, int i);
/* Renvoie le montant de la mise du ième Joueur*/
int Gain(Joueur *j, int i, int g);
/* Mets g dans l'attribut gain du ième Joueur et le Renvoie*/
Joueur *joueur_gain_max(Joueur *j, int n);
/* Renvoie un pointeur vers le Joueur de plus haut score (Gain)*/
void flush(FILE* f);
/* Vide le tampon du fichier f*/
int change_mise(Joueur *j, int n ,short suspend);
/* Change (ou pas) la mise des joueurs*/
void welcome(void);
/* Affiche sur stdin des salutations*/
void play(void);
/* Fonction principale*/
int high_score(FILE *fd, char *nom, int a);
/*Ecrit dans le fichier le nom de la persone avec plus haut score et son score*/
