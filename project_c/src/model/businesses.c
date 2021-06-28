#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <glib.h>
#include <ctype.h>
#include "../../includes/model/business.h"
#include "../../includes/model/businesses.h"
#include "../../includes/model/table.h"
#include "../../includes/model/utils.h"

/**
 \brief Businesses struct
 Struct that stores several business through an hash table
*/
struct businesses
{
    GHashTable* hashT;
};

/**
 \brief initializes businesses
*/
Businesses initBusinesses()
{
    Businesses busis = malloc(sizeof(struct businesses));

    busis->hashT = g_hash_table_new_full(g_str_hash, g_str_equal, free, destroyBusiness);
    
    return busis;
}

/**
 \brief adds a business to the hash table businesses
 @param busis Businesses hash table
 @param bus Business to be added
*/
void addBus(Businesses busis, Business bus)
{
    char* id = getBusinessID(bus);

    g_hash_table_insert(busis->hashT, id, bus);

}

/**
 \brief searches if a business is on the hash table
 @param busis Businesses hash table
 @param id Business id
*/
bool existsBusiness(Businesses busis, char* id)
{
    return (bool)g_hash_table_contains(busis->hashT, id);
}

/**
 \brief Duplicate a business from a given id
 @param busis Businesses hash table
 @param id Business id
*/
Business getBusiness(Businesses busis, char* id){
    return cloneBusiness((Business)g_hash_table_lookup(busis->hashT, id));
}

/**
 \brief Gets all of the business started by a letter
 @param busis Business hash table
 @param letter Letter
 @param tble TABLE
*/
void getBusinessesByLetter(Businesses busis, char letter, TABLE tble)
{
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init (&iter, busis->hashT);

    while(g_hash_table_iter_next (&iter, &key, &value))
    {
        Business bus = (Business) value;

        char* name = getBusinessName(bus);
        char* id = getBusinessID(bus);

        if(toupper(letter) == toupper(name[0]))
        {
            addToTable(tble, id);
            addToTable(tble, name);
            incrementData(tble);
        }
        else{
            free(name);
            free(id);
        }
    }

}

/**
 \brief Gets all of the business from a city
 @param busis Business hash table
 @param city City
*/
GPtrArray* getIdsInCity(Businesses busis, char* city){
    GPtrArray* ans = g_ptr_array_new_full(0, g_free);
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init (&iter, busis->hashT);

    char* cit = strdup(city);
    tolowerSTR(cit);

    while(g_hash_table_iter_next (&iter, &key, &value))
    {
        Business bus = (Business) value;
        char* busCity = getBusinessCity(bus);
        tolowerSTR(busCity);
        char* id = strdup((char*) key);

        if(!strcasecmp(busCity, cit)) g_ptr_array_add(ans, id);
        else free(id);
        free(busCity);
    }
    free(cit);
    if(ans->len > 0) return ans;
    return NULL;
}

/**
 \brief Gets all of the business ids and the cities that they belong to
 @param busis Business hash table
*/
GHashTable* getCitiesAndIDs(Businesses busis){
    GHashTable* ans = g_hash_table_new(g_str_hash, g_str_equal);
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init (&iter, busis->hashT);

    while(g_hash_table_iter_next (&iter, &key, &value))
    {
        Business bus = (Business) value;
        char* busCity = getBusinessCity(bus);
        char* bCityNoSens = strdup(busCity);
        char* id = strdup((char*) key);
        tolowerSTR(bCityNoSens);
        free(busCity);
        if(g_hash_table_contains(ans, bCityNoSens)){
            GPtrArray* tmp = (GPtrArray*) g_hash_table_lookup(ans, bCityNoSens);
            g_ptr_array_add(tmp, id);
            free(bCityNoSens);
        }
        else{
            GPtrArray* new = g_ptr_array_new_full(0, g_free);
            g_ptr_array_add(new, id);
            g_hash_table_insert(ans, bCityNoSens, new);
        }
    }
    return ans;
}

/**
 \brief Gets the top rated business from the same city
 @param busis Business hash table
 @param hT Business with average rating
 @param n Number of business top rated business
*/
GPtrArray* getTopNIDSinCities(Businesses busis, GHashTable* hT, int n){
    GHashTable* citiesAndIds = getCitiesAndIDs(busis);
    GPtrArray* ans = g_ptr_array_new_full(0, g_free);
    guint i;
    int j;
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init (&iter, citiesAndIds);
    

    while(g_hash_table_iter_next (&iter, &key, &value)){
        char* city = strdup((char*) key);
        *city = toupper(*city);
        GPtrArray* idsInCity = (GPtrArray*) value;
        int idx = 0;
        for(j = 0; j < n && idx != -1; j++){
            float max = -1;
            float* stars = malloc(sizeof(float));
            *stars = -1;
            idx = -1;
            for(i = 0; i < idsInCity->len; i++){
                if(g_hash_table_contains(hT, (char*) g_ptr_array_index(idsInCity, i))){
                    GPtrArray* tmp = (GPtrArray*) g_hash_table_lookup(hT, (char*) g_ptr_array_index(idsInCity, i));
                    float av = *((float*) g_ptr_array_index(tmp, 0));
                    if(av > max){
                        *stars = *((float*) g_ptr_array_index(tmp, 0));
                        max = av;
                        idx = i; 
                    }
                }
            }
            if(idx != -1){
                char* id = strdup(g_ptr_array_index(idsInCity, idx));
                g_ptr_array_remove_index(idsInCity, idx);
                char* ciToAdd = strdup(city);
                float* st = malloc(sizeof(stars));
                *st = *stars;
                g_ptr_array_add(ans, id);
                g_ptr_array_add(ans, ciToAdd);
                g_ptr_array_add(ans, st);
            }
            free(stars);
        }
        free(city);
        free(key);
        g_ptr_array_free(idsInCity, TRUE);
    }
    g_hash_table_destroy(citiesAndIds);
    return ans;
}
/**
 \brief Gets the business id with a category
 @param busis Business hash table
 @param category Business category
*/
GPtrArray* getIDSinCat(Businesses busis, char* category){
   GPtrArray* ans = g_ptr_array_new_full(0, g_free);
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init (&iter, busis->hashT);
    while(g_hash_table_iter_next (&iter, &key, &value)){
        Business b = (Business) value;
        GPtrArray* cats = getBusinessCategories(b);
        if(cats){
            int found = 0;
            for(guint i = 0; i < cats->len && !found; i++){
                char* cat = strdup((char*) g_ptr_array_index(cats, i));
                    if(!strcasecmp(cat, category)){
                        g_ptr_array_add(ans, strdup((char*) key));
                        found = 1;
                    }
                free(cat);
            }
        }
        g_ptr_array_free(cats, TRUE);
    }

    return ans;
}

/**
 \brief Gets the top rated business id with a category
 @param busis Business hash table
 @param hT Business with average rating
 @param category Business category
 @param n Number of business top rated business
*/
GPtrArray* getTopNWithCategory(Businesses busis, GHashTable* hT, char* category, int n){
    GPtrArray* idsInCat = getIDSinCat(busis, category);
    GPtrArray* ans = g_ptr_array_new_full(0, g_free);
    int idx = 0, j;
    guint i;

    for(j = 0; j < n && idx != -1; j++){
        float* stars = malloc(sizeof(float));
        float max = -1;
        *stars = -1;
        idx = -1;
        for(i = 0; i < idsInCat->len; i++){
            if(g_hash_table_contains(hT, (char*) g_ptr_array_index(idsInCat, i))){
                GPtrArray* tmp = (GPtrArray*) g_hash_table_lookup(hT, (char*) g_ptr_array_index(idsInCat, i));
                float av = *((float*) g_ptr_array_index(tmp, 0));
                if(av > max){
                    *stars = *((float*) g_ptr_array_index(tmp, 0));
                    max = av;
                    idx = i; 
                }
            }
        }
        if(idx != -1){
                char* id = strdup(g_ptr_array_index(idsInCat, idx));
                g_ptr_array_remove_index(idsInCat, idx);
                float* st = malloc(sizeof(stars));
                *st = *stars;
                g_ptr_array_add(ans, id);
                g_ptr_array_add(ans, st);
        }
        free(stars);
    }
    g_ptr_array_free(idsInCat, TRUE);
    return ans;
}

/**
 \brief Gets the business name with a given id
 @param busis Businesses hash table
 @param id Business id
*/
char* getBusinessNameWithID(Businesses busis, char* id){
    Business b = getBusiness(busis, id);
    char* name = getBusinessName(b);
    destroyBusiness(b);
    return name;
}

/**
 \brief Gets the business state with a given id
 @param busis Businesses hash table
 @param id Business id
*/
char* getBusinessStateWithID(Businesses busis, char* id){
    Business b = getBusiness(busis, id);
    char* state = getBusinessState(b);
    destroyBusiness(b);
    return state;
}

/**
 \brief Gets the international users
 @param busis Businesses hash table
 @param usWithBusID Pointer array with useres and their ids
*/
GPtrArray* createInterUsers(Businesses busis, GHashTable* usWithBusID){
    GHashTableIter iter;
    gpointer key, value;
    int flag;
    GPtrArray* ans = g_ptr_array_new_full(0, free);

    g_hash_table_iter_init (&iter, usWithBusID);

    while(g_hash_table_iter_next (&iter, &key, &value)){
        GPtrArray* ids = (GPtrArray*) value;
        char* usID = (char*) key;
        if(ids){
            flag = 1;
            char* bID = (char*)g_ptr_array_index(ids, 0);
            char* stToVer = getBusinessStateWithID(busis, bID);
            for(guint i = 1; i < ids->len && flag; i++){
                char* bID = (char*)g_ptr_array_index(ids, i);
                char* state = getBusinessStateWithID(busis, bID);
                if(strcmp(state, stToVer)){
                    char* userID = strdup(usID);
                    g_ptr_array_add(ans, userID);
                    flag = 0;
                }
                free(state);
            }
            free(stToVer);
        }
        free(key);
        g_ptr_array_free(ids, TRUE);
    }
    g_hash_table_destroy(usWithBusID);
    return ans;
}

/**
 \brief Deletes a Businesses hash table
 @param busis Businesses hash table to be deleted
*/
void freeBusinesses(Businesses busis)
{
    g_hash_table_destroy(busis->hashT);
    free(busis);
}