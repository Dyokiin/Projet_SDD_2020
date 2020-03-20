#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *fichier=NULL;
    fichier=fopen("./save.txt", "a");
    if (fichier!= NULL){
        printf("YES\n");
        fputs("5678908765467897654356789876543\n",fichier);
        fclose(fichier);
    }
    else{
        printf("NO\n");
    }
    fichier=fopen("./save.txt", "r");
    char ligne[255];
    fgets(ligne, 200,fichier);
    printf("%s\n",ligne );
    fclose(fichier);
    return 0;
}
