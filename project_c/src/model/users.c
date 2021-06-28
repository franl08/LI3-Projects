#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <glib.h>
#include "../../includes/model/user.h"
#include "../../includes/model/users.h"
#include "../../includes/model/table.h"

/**
 \brief Users struct
*/
struct users
{
    GHashTable* hashT;
};

/**
 \brief Initializes a Users hash table
*/
Users initUsers()
{
    Users usis = malloc(sizeof(struct users));

    usis->hashT = g_hash_table_new_full(g_str_hash, g_str_equal, free, destroyUser);
    
    return usis;
}

/**
 \brief Adds a user to a Users hash table
 @param usis Users hash table
 @param user User
*/
void addUser(Users usis, const User user)
{
    char* id = getUserId(user);

    g_hash_table_insert(usis->hashT, id, user);

}

/**
 \brief Verifies if exists a user in a Users hash table
 @param usis Users hash table
 @param id User id
*/
bool existsUser(Users usis, char* id)
{
    return (bool)g_hash_table_contains(usis->hashT, id);
}

/**
 \brief Deletes a Users hash table
 @param u Users hash table
*/
void freeUsers(Users u){
    g_hash_table_destroy(u->hashT);
    free(u);
}