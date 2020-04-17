#include <sting.h>

int test_connexion(char *login,char *password){
    if(strcomp(login,"test")==0 && strcomp(password,"test")==0){
      // 1 si normal 2 si admin
        return 1;
    }
// 0 si utilisateur inexistant ou mot de passe eronne
    return 0;
}


int test_creation_compte(char *login,char *password){
    if (recherche_occurence_login(login)){
        //erreur login
        return 1;
    }
    if (!mdp_correct(password)){
        //erreur mot de passe
        return 2;
    }
    save_user(login,password);
    return 0;

}
