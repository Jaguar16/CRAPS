#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "craps.h"
/* Vide le buffer*/
void flush(FILE* f){
	int c;
	while((c=fgetc(f)) != '\n' && c != EOF);
}

int lance(){
    return ((rand() % 6) + 1) + ((rand() % 6) + 1);     
}

int nb_joueur(){
    int a;
    printf("Vous êtes combien ? : ");
    scanf("%d", &a);
    return a;
}

void welcome(){
    int a;
    a = rand() % 4;
    if (a==0){
        printf("Salut !");
    }
    else if (a==1){
        printf("Bonne chance :)");
    }
    else if (a==2){
        printf("Je sens que tu vas gagner beaucoup de sous toi.");
    }
    else{
        printf("Ya mara7ba");
    }
}

int init_joueur(int nb_j, Joueur *j){
    int i;
    for (i = 0; i < nb_j; i++){
        printf("\nEntrez votre nom joueur %d : ", i+1);
        scanf("%s",(j+i)->nom);
        (j+i)->gain = 0;
        (j+i)->mise=0;
        welcome();
    }
    return 0;
}

int print_name(Joueur *j, int i){
    printf("\nNom: %s\t\n", (j+i)->nom);
    return 0;
}

char *get_name(Joueur *j, int i){
    return (j+i)->nom;
}

int parie_quoi(Joueur *j, int i){
    printf("\n%s, vous misez sur quoi ? (p pour Pass/ d pour Don't pass) : ", (j+i)->nom);
    /*scanf("%s", &(j+i)->quoi);*/
    while( (scanf(" %c", &(j+i)->quoi) == 1) && ((j+i)->quoi != 'p') && ((j+i)->quoi != 'd') ) {
        printf("p pour Pass, d pour Don't pass : ");
    }
    printf("Vous avez misez sur %c\n", (j+i)->quoi);
    return 0;
}


char get_quoi(Joueur *j, int i){
    return (j+i)->quoi;
}

int parie_cb(Joueur *j, int i){
    printf("\n%s, vous misez combien ? : ", (j+i)->nom);
    scanf(" %d", &(j+i)->mise);
    flush(stdin);
    printf("Vous avez misez %d euros\n", (j+i)->mise);
    return 0;
}

int get_mise(Joueur *j, int i){
    return (j+i)->mise;
}



int Gain(Joueur *j, int i, int g){
    (j+i)->gain += g;
    return (j+i)->gain;
}

Joueur *joueur_gain_max(Joueur *j, int n){
    int max;
    int i;
    Joueur *ptrj;
    ptrj = j;
    i = 0;
    max = j->gain;
    for (i = 1 ; i < n; i++){
        if ((j+i)->gain > max){
            max = (j+i)->gain;
            ptrj = (j+i);
        }
    }
    return ptrj;
}

/*Change mise, 1 est la première suspension 2 sont les autre suspensions*/

int change_mise(Joueur *j, int n ,short suspend){ /*n nombre de joueurs */
    char rep;
    int nm;
    int i;

    if (suspend==0){ /*Change de mise avant la 2eme phase*/
        for (i=0; i<n; i++){

            if (get_quoi(j,i)=='p'){
                printf("\n%s, souhaitez-vous augmenter votre mise ?  (o/n) : ", get_name(j,i));
                scanf(" %c",  &rep);
                if (rep=='o'){
                    do 
                    {
                    printf("Indiquez votre nouvelle mise (plus grande que votre mise initiale : %d) :", get_mise(j,i));
                    scanf("%d", &nm);
                    flush(stdin);
                    }
                    while (nm<get_mise(j,i) || nm < 1);
                    (j+i)->mise = nm;
                }
            }
            else {
                printf("\n%s, souhaitez-vous diminuer votre mise ?  (o/n) : ", get_name(j,i));
                scanf(" %c",  &rep);
                if (rep=='o'){
                    do 
                    {
                    printf("Indiquez votre nouvelle mise (plus petite que votre mise initiale : %d) :", get_mise(j,i));
                    scanf("%d", &nm);
                    flush(stdin);
                    }
                    while (nm>get_mise(j,i) || nm < 1);
                    (j+i)->mise = nm;
                }
                
            }
        }
    return 0;
    }

    else if (suspend==1) { /*Change de mise apres la 1ere suspension*/
        for (i = 0; i<n; i++){
            printf("\n%s, souhaitez-vous doubler votre mise ?  (o/n) : ", get_name(j,i));
            scanf(" %c",  &rep);
            if (rep == 'o'){
                (j+i)->mise *= 2;
            }
        }
        return 0;
    }

    else { /*Change de mise apres les autres suspensions*/
        for (i = 0; i<n; i++){
            printf("\n%s, souhaitez-vous diminuer par un facteur de 2 votre mise ?  (o/n) : ", get_name(j,i));
            scanf(" %c",  &rep);
            if (rep == 'o'){
                printf("Indiquez par quelle facteur de 2 souhaitez-vous diminuer votre mise : %d) :", get_mise(j,i));
                scanf("%d",&nm);
                (j+i)->mise /= 2*nm;
            }
            flush(stdin);
        }    
    return 0;
    }
}


int high_score(FILE *fd,char *nom, int a){
    //FILE *fd;
    //if( access( "score.csv", F_OK ) != -1 ) {
    // file exists
    //} else {
    // file doesn't exist
    //}
    fd = fopen("score.csv","w+");
    if (fd) {
        fprintf(fd, "%s %d", nom, a);
        fclose(fd);
        return 0;
        }
    else {
        return 1;
    }
}




void play(){

    int nb_2joueur;
    int start;
    int relance;
    int suivant; /* dernier pointeur vers pj*/
    int le_point;
    int i;
    int hgs;
    int fhs;
    char *nom_hgs;
    char fnom_hs[20];
    int suspendu; /* 1 --> 1ere suspension, 2 autres suspensions*/
    char c;
    char touche;
    FILE *h_score;
    Joueur *pj; 
    Joueur *lanceur; /*Pointeur vers le joueur qui va lance les dés*/
    Joueur *pjmax; /* Pointeur vers le jour de Gain max*/


    
    nb_2joueur = nb_joueur();
    pj = (Joueur*) malloc(nb_2joueur * sizeof(Joueur));
    pjmax = (Joueur *) malloc(sizeof(Joueur));
    lanceur = pj;
    init_joueur(nb_2joueur, pj);
    start = 2;
    suivant = 0;

    while (start){
        printf("\n\n---------------------------------------------------------------------------");
        printf("\n---------------------------------------------------------------------------");
        pjmax = joueur_gain_max(pj, nb_2joueur);
        hgs = pjmax->gain;
        nom_hgs = get_name(pjmax,0);
        h_score = fopen("score.csv", "r");
        if (h_score){
            fscanf(h_score,"%s %d", fnom_hs, &fhs);
            if (fhs>hgs){
                printf("\n\nHigh Score %d by %s.\n",fhs , fnom_hs);
            }
            else {
                printf("\n\nHigh Score %d by %s.\n",hgs , nom_hgs);
                high_score(h_score, nom_hgs, hgs);
            }
        }
        else {
        printf("\n\nHigh Score %d by %s.\n",hgs , nom_hgs);
        high_score(h_score, nom_hgs, hgs);}
        /*On demande aux joueur ils misent sur quoi Pass ou Don't pass et quoi*/
        for(i = 0; i < nb_2joueur; i++){
            parie_quoi(pj,i);
            parie_cb(pj,i);
        }
        printf("\n%s, Tape entrée pour lancer les dés : ",lanceur->nom);
        if ((touche = getc(stdin)) || (touche ==EOF)){
            le_point = lance();
        }
        
        /* 2 ou 12, le lanceur ne passe pas (Toujours le même lanceur après ce tour)*/

        if (le_point == 2 || le_point == 12) {
            printf("--------Craps !--------");
            printf("\nQuel dommage, ma7laha fik hawena tu as obtenu %d\nDonnez moi vos sous ceux qui ont misé pass", le_point);
            for (i = 0; i<nb_2joueur; i++){
                c = get_quoi(pj,i);
                if (c == 'p'){
                    printf("\n%s, passe moi tes %d euros", get_name(pj,i), get_mise(pj,i));
                    Gain(pj,i,-((pj+i)->mise));
                    (pj+i)->mise = 0;
                }
                
                if (c == 'd' && le_point == 2){
                    printf("\n%s, Bien vu tu gagnes %d euros et tu les reprends.", get_name(pj,i), get_mise(pj,i));
                    Gain(pj,i,(pj+i)->mise);
                    (pj+i)->mise = 0;
                }

            }
            
        }


        else if (le_point == 7){
            printf("\nTu as obtenu : 7");
            printf("\nTous ceux qui ont joué sur pass ont gagné."); 
            for (i = 0; i<nb_2joueur; i++){
                c = get_quoi(pj,i);
                if (c == 'p'){
                    printf("\n%s, Bien vu tu gagnes %d euros", get_name(pj,i), get_mise(pj,i));
                    Gain(pj,i,(pj+i)->mise);
                    (pj+i)->mise = 0;
                }
                
                if (c == 'd'){
                    printf("\n%s, tu perds tes %d euros.", get_name(pj,i), get_mise(pj,i));
                    Gain(pj,i,-((pj+i)->mise));
                    (pj+i)->mise = 0;
                }

            }
        }

        /* On entre dans la 2ème phase*/
        else {
            system("clear");
            printf("\nLe Point est %d ", le_point);
            change_mise(pj, nb_2joueur,0);
            printf("\n--------------------------------Phase 2 -----------------------------------");
            relance = 1;
            suspendu = 1;
            flush(stdin);
            while(1){
                printf("\n%s, Tape entrée pour lancer les dés : ",lanceur->nom);
                if (getc(stdin)=='\n'){
                    relance = lance();
                    }
                printf("\nTu as obtenu : %d", relance);

                if (relance==le_point){
                    for (i = 0; i<nb_2joueur; i++){
                        c = get_quoi(pj,i);
                        if (c == 'p'){
                            printf("\n%s, tu gagnes %d euros", get_name(pj,i), get_mise(pj,i));
                            Gain(pj,i,(pj+i)->mise);
                            (pj+i)->mise = 0;
                        }
                
                        if (c == 'd'){
                            printf("\n%s, tu perds tes %d euros.", get_name(pj,i), get_mise(pj,i));
                            Gain(pj,i,-((pj+i)->mise));
                            (pj+i)->mise = 0;
                        }

                    }
                    break;
                }

                if (relance==7){
                    suivant += 1;
                    for (i = 0; i<nb_2joueur; i++){
                        c = get_quoi(pj,i);
                        if (c == 'p'){
                            printf("\n%s, tu perds tes %d euros", get_name(pj,i), get_mise(pj,i));
                            Gain(pj,i,-((pj+i)->mise));
                            (pj+i)->mise = 0;
                        }
                
                        if (c == 'd'){
                            printf("\n%s, tu gagnes %d euros.", get_name(pj,i), get_mise(pj,i));
                            Gain(pj,i,(pj+i)->mise);
                            (pj+i)->mise = 0;
                        }
                    }
                    if (suivant >= nb_2joueur){
                            lanceur = pj;
                            start--;
                            suivant=0;
                    }
                    else {
                        lanceur +=1;
                        suivant++;
                    }
                    break;
                }
                else {
                    if (suspendu==1){
                        change_mise(pj, nb_2joueur,1);
                        suspendu = 2;
                    }
                    else {
                        change_mise(pj, nb_2joueur, 2);
                    }
                }
            }
                
        }
    }
    free(pj);
}
