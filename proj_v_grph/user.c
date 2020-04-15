#include <stdio.h>
#include <string.h>
#include "user.h"


int test_connexion(char *login, char *password){
	if(strcmp(login, "user")==0 && strcmp(password, "user") == 0){
		return 1;
	}
	if(strcmp(login, "admin")==0 && strcmp(password, "admin")==0){
		return 2;
	}
	return 0;
}

int test_creation_compte(char* login, char *password){
	if(strcmp(login,"user")==0){
		return 1;
	}
	if(strstr(password,"\"") !=NULL){
		return 2;
	}
	return 0;
}
