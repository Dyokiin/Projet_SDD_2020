#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

void test() {
	
	char chaine[MAX] = "";
	FILE* fichier = NULL;
	fichier = fopen("test.json", "r");

	if (fichier != NULL) {
		while (fgets(chaine, MAX, fichier) != NULL) {
			printf("%s", chaine);
		}
	} else {
		printf("Fichier inexistant ou déjà utilisé par un autre programme.");
	}
	
	fclose(fichier);
}

int main(int argc, char * argv[]){
	test() ;

	return 0;
}
