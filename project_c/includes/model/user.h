#ifndef USER_H
#define USER_H

#include <glib.h>

typedef struct user *User;

User initUser(char*);

char* getUserId(User);

char* getUserName(User);

char** getFriends(User);

User cloneUser(User);

void destroyUser(void* u);

#endif