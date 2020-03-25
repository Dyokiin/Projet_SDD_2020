#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
    char login[]="rtcfrea";
    char password[]="1217626519234264774124021682371916328828231750103353992";
    FILE* stream=fopen("save.txt", "a");

    if (stream!= NULL){
        fprintf(stream," %s %s \n",login,password);
        fclose(stream);  //erreur pour les mots de passe un peu lpn (environ +10characteres)

        return 1;
    }
    else{
        return 0;
    }
}
