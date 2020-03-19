#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "getters.h"
#define MAX 17
#define MDP 10

char* getchars() {
    int err = 0 ;
    char *chaine = malloc(MAX * sizeof(char));
    char *ret    = malloc(sizeof(char));
    fgets(chaine, MAX, stdin) ;
    for(int i=0; i<=MAX; i++){
        if (isdigit(chaine[i])) {
            err = 1 ;
        }
    }
    if (err == 0) {
	return chaine ;
    }
    return ret ;
}


int getints() {
	int err = 0 ;
	char chaine[MDP] ;
	int ret = 0 ;
	fgets(chaine, MAX, stdin);
	for(int i=0; i<=MDP; i++){
		if(!isdigit(chaine[i])){
			err = 1 ;
		}
	}
	if (err == 0){
		for(int i=0; i<=MDP;i++){
			ret = ret*10 + chaine[i] ;
		}
	}
	return ret ;
}


int main(int argc, char* argv[]){
	char* truc = getchars() ;
	fflush(stdin) ;
	int tric = getints() ;
	printf("%s \n", truc) ;
	printf("%i \n", tric) ;
}
