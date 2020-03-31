#include <stdio.h>
#include <json-c/json.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    char buffer[1024];

    struct json_object *parsed_json;
	//struct json_object *tableau;
	struct json_object *valeur_tableau;

    fp=fopen("test.json","r");
    fread(buffer,1024,1,fp);
    fclose(fp);

    parsed_json = json_tokener_parse(buffer);

    //json_object_object_get_ex(parsed_json,"tableau" , &tableau);

    long  unsigned int longueur= json_object_array_length(parsed_json);
    printf("taille= %lu \n",longueur);

    for(long unsigned int i=0;i<longueur;i++) {
		valeur_tableau = json_object_array_get_idx(parsed_json, i);
		printf("%lu. %s\n",i+1,json_object_get_string(valeur_tableau));
	}

}
