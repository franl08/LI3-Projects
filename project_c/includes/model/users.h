#ifndef USERS_H
#define USERS

#include "user.h"
#include <stdbool.h>

typedef struct users* Users;

Users initUsers();

void addUser(Users usis, const User user);

bool existsUser(Users usis, char* id);

void freeUsers(Users u);

#endif
