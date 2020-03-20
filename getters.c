#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "getters.h"
#define MAX 20
#define MDP 10

char* getchars() {
    	int err = 0 ;
    	char *chaine = malloc(MAX * sizeof(char));
    	char *n;
    	fgets(chaine, MAX, stdin) ;
    	if ((n=strchr(chaine, '\n'))){
		*n='\0';
	    }

    	for(int i=0; i<=MAX; i++){
        	if (isdigit(chaine[i])) {
            	err = 1 ;
        	}
    	}
    	if (err == 0) {
		return chaine ;
    	}
    	return NULL ;
}


int getints() {
	
	char chaine[100] ;
	int nbr = 0 ;
	fgets(chaine, 100, stdin);
	if (sscanf(chaine, "%d", &nbr) == 1){
		return nbr ;
	}
	
	return nbr ;
}



