#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include "../../includes/model/businesses.h"
#include "../../includes/model/reviews.h"
#include "../../includes/model/users.h"
#include "../../includes/model/utils.h"
#include "../../includes/model/dataCross.h"

/**
 \brief gets a business list with stars+ stars from a city
 @param busis Businesses hash table
 @param revs Reviews
 @param stars Reviews rating
 @param city City
*/
GPtrArray* getQ5Content(Businesses busis, Reviews revs, float stars, char* city){
    GPtrArray* idsInCity = getIdsInCity(busis, city);
    if(idsInCity){
        GPtrArray* inCityWithStars = getInCityWithStars(revs, stars, idsInCity);
        g_ptr_array_free(idsInCity, TRUE);
        GPtrArray* nameAndIDs = g_ptr_array_new_full(0, free);
        if(inCityWithStars){
            for(int i = 0; i < inCityWithStars->len; i++){
                char* id = strdup(((char*) g_ptr_array_index(inCityWithStars, i)));
                char* name = getBusinessNameWithID(busis, id);
                g_ptr_array_add(nameAndIDs, id);
                g_ptr_array_add(nameAndIDs, name);
            }
            g_ptr_array_free(inCityWithStars, TRUE);
            return nameAndIDs;
        }
    }
    return NULL;
}

/**
 \brief gets a business list with the top rated business
 @param busis Businesses hash table
 @param revs Reviews
 @param n Number wanted from top rated business
*/
GPtrArray* getQ6Content(Businesses busis, Reviews revs, int n){
    GHashTable* tmp = createHashForBusWithAverage(revs);
    GPtrArray* topNInCities = getTopNIDSinCities(busis, tmp, n);
    g_hash_table_destroy(tmp);
    GPtrArray* ans = g_ptr_array_new_full(0, g_free);
    for(int i = 0; i < topNInCities->len; ){
        char* id = strdup((char*) g_ptr_array_index(topNInCities, i++));
        char* name = getBusinessNameWithID(busis, id);
        char* city = strdup((char*) g_ptr_array_index(topNInCities, i++));
        float* s = malloc(sizeof(float));
        *s = *((float*)g_ptr_array_index(topNInCities, i++));
        g_ptr_array_add(ans, id);
        g_ptr_array_add(ans, name);
        g_ptr_array_add(ans, s);
        g_ptr_array_add(ans, city);
    }
    g_ptr_array_free(topNInCities, TRUE);
    return ans;
}

/**
 \brief gets a users list with users that visited more than one state
 @param busis Businesses hash table
 @param revs Reviews
*/
GPtrArray* getQ7content(Businesses busis, Reviews revs){
    GHashTable* usWithBusID = createHashForUsWithBusID(revs);
    GPtrArray* ans = createInterUsers(busis, usWithBusID);
    
    return ans;
}

/**
 \brief gets a business list with the top rated business with a category
 @param busis Businesses hash table
 @param revs Reviews
 @param category Business category
 @param n Number wanted from top rated business
*/
GPtrArray* getQ8content(Businesses busis, Reviews revs, char* category, int n){
    GHashTable* tmp = createHashForBusWithAverage(revs);
    GPtrArray* topNWithCategory = getTopNWithCategory(busis, tmp, category, n);
    g_hash_table_destroy(tmp);
    GPtrArray* ans = g_ptr_array_new_full(0, g_free);
    if(topNWithCategory){
        for(guint i = 0; i < topNWithCategory->len; i++){
            char* id = strdup((char*) g_ptr_array_index(topNWithCategory, i++));
            char* name = getBusinessNameWithID(busis, id);
            float* s = malloc(sizeof(float));
            *s = *((float*) g_ptr_array_index(topNWithCategory, i));
            //printf("%f\n", *s);
            g_ptr_array_add(ans, id);
            g_ptr_array_add(ans, name);
            g_ptr_array_add(ans, s);
        }
        g_ptr_array_free(topNWithCategory, TRUE);
    }
    return ans;
}

/**
 \brief Gets reviews id, from reviews that contains a word
 @param revs Reviews
 @param word Word
*/
GPtrArray* getQ9content(Reviews revs, char* word){
    GPtrArray* aux = getIdsWithWord(revs, word);
    return aux;
}