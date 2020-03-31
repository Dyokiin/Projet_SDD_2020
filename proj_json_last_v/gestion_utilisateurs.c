#ifndef __USER_H__
#define __USER_H__

typedef struct s_user *User;

struct s_user {
    char *id;
    char *password;
    enum statut s;
};
