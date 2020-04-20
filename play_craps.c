#include "craps.c"
int main(){
    srand(time(NULL));

    char commence = '\0';
    system("clear");
    printf("Voulez-vous jouer au craps ? (o/n) : ");
    while( (scanf(" %c", &commence) == 1) && (commence != 'o') && (commence != 'n') ) {
        printf("o pour Oui, n pour Non : ");
    }

    if (commence == 'o'){
        printf("\n------------------------------------C'est parti------------------------------------------\n");
        flush(stdin);
        play();
    }
    if (commence == 'n'){
        printf("\nCiao !");
    }

    return 0;
}

