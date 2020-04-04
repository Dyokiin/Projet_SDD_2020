/*int compteur_guillemet=0;
char password[100];
//printf("%s\n",ligne );
// { "login": "azerazer", "password": "908082667021279402771107911182891852034", "statut": "0", "nom": "", "prenom": "", "email": "" }
int i=0;
while(compteur_guillemet!=7){
    if(ligne[i]=='"'){
        compteur_guillemet++;
    }
    //printf("%c\n",ligne[i]);
    i++;

}
int j=0;
//printf("%c\n",ligne[i] );
while (ligne[i+j]!='"') {
    password[j]=ligne[i+j];
    j++;
}
compteur_guillemet++;
password[j]='\0';
printf("MDP :%s\n",password );
i=i+j+1;
//printf("%c\n",ligne[i] );

while(compteur_guillemet!=11){
    if (ligne[i]=='"'){
        compteur_guillemet++;
    }
    i++;
}
char statut[3];
j=0;
while (ligne[i+j]!='"') {
    statut[j]=ligne[i+j];
    j++;
}
compteur_guillemet++;
statut[j]='\0';
printf("STATUT :%s\n",statut );
i=i+j+1;
while(compteur_guillemet!=15){
    if (ligne[i]=='"'){
        compteur_guillemet++;
    }
    i++;
}
char nom[100];
j=0;
while(ligne[i+j]!='"'){
    nom[j]=ligne[i+j];
    j++;
}
compteur_guillemet++;
nom[j]='\0';
printf("NOM :%s\n",nom );
i=i+j+1;
while(compteur_guillemet!=19){
    if (ligne[i]=='"'){
        compteur_guillemet++;
    }
    i++;
}
char prenom[100];
j=0;
while(ligne[i+j]!='"'){
    prenom[j]=ligne[i+j];
    j++;
}
compteur_guillemet++;
prenom[j]='\0';
printf("PRENOM :%s\n",prenom );
i=i+j+1;
while(compteur_guillemet!=23){
    if (ligne[i]=='"'){
        compteur_guillemet++;
    }
    i++;
}
char email[100];
j=0;
while(ligne[i+j]!='"'){
    email[j]=ligne[i+j];
    j++;
}
compteur_guillemet++;
email[j]='\0';
printf("EMAIL :%s\n",email );
i=i+j+1;
*/
