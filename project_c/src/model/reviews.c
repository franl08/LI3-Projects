#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <glib.h>
#include <ctype.h>
#include "../../includes/model/review.h"
#include "../../includes/model/reviews.h"
#include "../../includes/model/table.h"
#include "../../includes/model/utils.h"

/**
 \brief reviews struct
*/
struct reviews
{
    GHashTable* hashT;
};

/**
 \brief Initializes a Reviews hash table
*/
Reviews initReviews()
{
    Reviews revs = malloc(sizeof(struct reviews));

    revs->hashT = g_hash_table_new_full(g_str_hash, g_str_equal, free, destroyReview);
    
    return revs;
}

/**
 \brief Gets the total number of reviews and stars of a business
 @param revs Reviews
 @param bus_id Business id
 @param stars Stars
 @param totRevs Total number of reviews
*/
void getTotRevsAndStarsOfBus(Reviews revs, char* bus_id, float* stars, int* totRevs){
    char* id;
    GHashTableIter iter;
	gpointer key, value;
    g_hash_table_iter_init(&iter, revs->hashT);

	while(g_hash_table_iter_next(&iter, &key, &value)){
		Review rev = (Review) value;
        id = getReviewBusinessID(rev);
		if(!strcmp(id, bus_id)){
			*stars += getReviewStars(rev);
			(*totRevs)++;
	    }
        free(id);
	}
}

/**
 \brief Gets the reviews associated to a user id
 @param revs Reviews
 @param user_id User id
*/
GPtrArray* getRevsWithUsID(Reviews revs, char* user_id){
    GPtrArray* ans = g_ptr_array_new_full(0, free);
    GHashTableIter iter;
	gpointer key, value;
    g_hash_table_iter_init(&iter, revs->hashT);

	while(g_hash_table_iter_next(&iter, &key, &value)){
		Review rev = (Review) value;
        char* id = getReviewUserID(rev);
		if(!strcmp(id, user_id)){
            char* bID = getReviewBusinessID(rev);
            g_ptr_array_add(ans, bID);
        }
        free(id);
    
	}

    return ans;
}

/**
 \brief Gets the business list with the top rated business from a city
 @param revs Reviews
 @param stars Stars
 @param idsInCity Business id from a city
*/
GPtrArray* getInCityWithStars(Reviews rev, float stars, GPtrArray* idsInCity){
    GPtrArray* ans = g_ptr_array_new_full(0, free);
    GHashTable* busStars = createHashForBus(rev);
    float st;


    for(int i = 0; i < idsInCity->len; i++){
        char* id = strdup(((char*) g_ptr_array_index(idsInCity, i)));
        if(g_hash_table_contains(busStars, id)){
            st = *((float*)g_hash_table_lookup(busStars, id));
            if(st >= stars) g_ptr_array_add(ans, id);
            else free(id);
        }
        else free(id);
    }
    g_hash_table_destroy(busStars);
    return ans;
}

/**
 \brief Creates a Hash table for business id and review stars
 @param revs Reviews
*/
GHashTable* createHashForBus(Reviews revs){
    GHashTable* ans = g_hash_table_new_full(g_str_hash, g_str_equal, free, free);
    GHashTableIter iter;
	gpointer key, value;
    g_hash_table_iter_init(&iter, revs->hashT);

	while(g_hash_table_iter_next(&iter, &key, &value)){
        Review r = (Review) value;
        char *bID = getReviewBusinessID(r);
        float* s = malloc(sizeof(float));
        *s = getReviewStars(r);
        if(g_hash_table_contains(ans, bID)){
            float* st = (float*) g_hash_table_lookup(ans, bID);
            *st += *s;
            free(bID);
            free(s);
        }
        else g_hash_table_insert(ans, bID, s);
    }
    return ans;
}

/**
 \brief Creates a Hash table for business total reviews
 @param revs Reviews
*/
GHashTable* createHashForBusWithTotRevs(Reviews revs){
    GHashTable* ans = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, freeArr);
    GHashTableIter iter;
	gpointer key, value;
    g_hash_table_iter_init(&iter, revs->hashT);

	while(g_hash_table_iter_next(&iter, &key, &value)){
        Review r = (Review) value;
        char *bID = getReviewBusinessID(r);
        float* s = malloc(sizeof(float));
        *s = getReviewStars(r);
        
        if(g_hash_table_contains(ans, bID)){
            GPtrArray* tmp = (GPtrArray*) g_hash_table_lookup(ans, bID);
            float* st = (float*) g_ptr_array_index(tmp, 0);
            int* tR = (int*) g_ptr_array_index(tmp, 1);
            *st += *s;
            *tR += 1;
            free(bID);
            free(s);
        }
        else{
            GPtrArray* new = g_ptr_array_new_full(0, g_free);
            g_ptr_array_add(new, s);
            int* t = malloc(sizeof(int));
            *t = 1;
            g_ptr_array_add(new, t);
            g_hash_table_insert(ans, bID, new);
        }
    }
    return ans;
}

/**
 \brief Creates a Hash table for business average stars reviews
 @param revs Reviews
*/
GHashTable* createHashForBusWithAverage(Reviews revs){
    GHashTable* ans = createHashForBusWithTotRevs(revs);
    GHashTableIter iter;
	gpointer key, value;
    g_hash_table_iter_init(&iter, ans);

	while(g_hash_table_iter_next(&iter, &key, &value)){
        GPtrArray* tmp = (GPtrArray*) value;
        float* st = (float*) g_ptr_array_index(tmp, 0);
        int* t = (int*) g_ptr_array_index(tmp, 1);
        *st = (*st) / (*t);
    }
    
    return ans;
}

/**
 \brief Creates a Hash table with user id and business id
 @param revs Reviews
*/
GHashTable* createHashForUsWithBusID(Reviews revs){
    GHashTable* ans = g_hash_table_new(g_str_hash, g_str_equal);
    GHashTableIter iter;
	gpointer key, value;
    g_hash_table_iter_init(&iter, revs->hashT);

	while(g_hash_table_iter_next(&iter, &key, &value)){
        Review r = (Review) value;
        char* bID = getReviewBusinessID(r);
        char* uID = getReviewUserID(r);
        
        if(g_hash_table_contains(ans, uID)){
            GPtrArray* tmp = (GPtrArray*) g_hash_table_lookup(ans, uID);
            g_ptr_array_add(tmp, bID);
            free(uID);
        }
        else{
            GPtrArray* new = g_ptr_array_new_full(0, g_free);
            g_ptr_array_add(new, bID);
            g_hash_table_insert(ans, uID, new);
        }
    }
    return ans;
}

/**
 \brief Creates a Hash table for review id with a word
 @param revs Reviews
 @param word Word
*/
GPtrArray* getIdsWithWord(Reviews revs, char* word){
    GPtrArray* ans = g_ptr_array_new_full(0, g_free);
    int sizeWord = strlen(word);
    int i = 0;
    GHashTableIter iter;
	gpointer key, value;
    g_hash_table_iter_init(&iter, revs->hashT);

	while(g_hash_table_iter_next(&iter, &key, &value)){
        Review r = (Review) value;
        int flag = 1;
        char* text = getReviewText(r);
        char* rID = getReviewID(r);
        if(text){
            char* aux = strstr(text, word);
            while(aux && flag){
                char prev, after;
                if((aux + sizeWord) && *(aux + sizeWord) != '\0'){
                    after = *(aux + sizeWord);
                    if(ispunct(after) || isspace(after)){
                        if((aux - 1) && *(aux - 1) != '\0'){
                            prev = *(aux - 1);
                            if(ispunct(prev) || isspace(prev)){
                                g_ptr_array_add(ans, strdup(rID));
                                flag = 0;
                            }
                            else aux = strstr((aux + 1), word);
                        }
                        else{
                            g_ptr_array_add(ans, strdup(rID));
                            flag = 0;
                        }
                    }
                    else aux = strstr((aux + 1), word);
                }
                else if((aux - 1) && *(aux - 1) != '\0'){
                    prev = *(aux - 1);
                    if(ispunct(prev) || isspace(prev)){
                        g_ptr_array_add(ans, strdup(rID));
                    }
                    flag = 0;
                }
                else{
                    g_ptr_array_add(ans, strdup(rID));
                    flag = 0;
                }
            }
        }
        free(rID);
        free(text);
    }
    return ans;
}

/**
 \brief Adds a review to a Reviews hash table
 @param revs Reviews
 @param rev Review
*/
void addReview(Reviews revs, Review rev)
{
    char* id = getReviewID(rev);

    g_hash_table_insert(revs->hashT, id, rev);
    
}

/**
 \brief Deletes a Reviews hash table
 @param revs Reviews
*/
void freeReviews(Reviews r){
    g_hash_table_destroy(r->hashT);
    free(r);
}