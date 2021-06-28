#include <glib.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../../includes/model/users.h"
#include "../../includes/model/businesses.h"
#include "../../includes/model/reviews.h"
#include "../../includes/model/dataCross.h"
#include "../../includes/model/table.h"
#include "../../includes/model/utils.h"
#include "../../includes/config.h"
#include "../../includes/view/ui.h"
#include "../../includes/model/sgr.h"


/**
 \brief Struct of "Sistema de gestão de recomendações"
*/
struct sgr
{
	Users users;
	int users_valid;
	int users_read;

	Businesses businesses;
	int businesses_valid;
	int businesses_read;

	Reviews reviews;
	int reviews_valid; 
	int reviews_read;
};

/**
 \brief Initializes a sgr
*/
SGR init_sgr()
{
	SGR data               = malloc(sizeof (struct sgr));

	data->users            = initUsers();
	data->users_read       = 0;
	data->users_valid      = 0;
 
	data->businesses       = initBusinesses();
	data->businesses_read  = 0;
	data->businesses_valid = 0;

	data->reviews          = initReviews();
	data->reviews_read     = 0;
	data->reviews_valid    = 0;

	return data;
}

/**
 \brief Deletes a sgr
 @param data Sgr
*/
void free_sgr(SGR data)
{
	freeUsers(data->users);
	freeBusinesses(data->businesses);
	freeReviews(data->reviews);
	free(data);
}

/**
 \brief Query 1
*/

/**
 \brief loads a user to the sgr
 @param filepath Filepath that contains the user
 @param data Sgr
*/
static void load_user(char* filepath, SGR data)
{
	FILE* file;

	char *buff = malloc(sizeof(char) * BUFFERSIZE);

	if((file = fopen(filepath, "r"))){
		while(fgets(buff, BUFFERSIZE, file))
		{
			User insert = initUser(buff);
		
			if(insert)
			{
				addUser(data->users, insert); 
				data->users_valid++;
			}
			else free(insert);
			data->users_read++;
		}
		fclose(file);
	}

	free(buff);
}

/**
 \brief loads a business to the sgr
 @param filepath Filepath that contains the business
 @param data Sgr
*/
static void load_business(char* filepath, SGR data)
{
	FILE* file;

	char *buff = malloc(sizeof(char) * BUFFERSIZE);

	if((file = fopen(filepath, "r"))){
		while(fgets(buff, BUFFERSIZE, file))
		{
			Business insert = init_business(buff);

			if(insert)
			{
				addBus(data->businesses, insert);
				data->businesses_valid++;
			}
			else free(insert);
			data->businesses_read++;
		}
		fclose(file);
	}

	free(buff);

}

/**
 \brief loads a review to the sgr
 @param filepath Filepath that contains the review
 @param data Sgr
*/
static void load_review(char* filepath, SGR data)
{
	FILE* file;
	int i = 0;

	char *buff = malloc(sizeof(char) * BUFFERSIZE);

	if((file = fopen(filepath, "r"))){
		while(fgets(buff, BUFFERSIZE, file))
		{
			data->reviews_read++;

			Review insert = init_review(buff);

			if(insert){
				char* uId = getReviewUserID(insert);
				char* bId = getReviewBusinessID(insert);
				if(existsUser(data->users, uId) && existsBusiness(data->businesses, bId)){
					addReview(data->reviews, insert);
					data->reviews_valid++;
				}
				else destroyReview(insert);
				free(uId);
				free(bId);
			}	
			else free(insert);
		
		}
		fclose(file);
	}

	free(buff);
}

/**
 \brief Query 1 main function
 @param users Users to be added to the sgr
 @param businesses Business to be added to the sgr
 @param reviews Reviews to be added to the sgr
*/
SGR load_sgr(char* users, char* businesses, char* reviews)
{
	SGR data = init_sgr();

	load_user(users, data);

	load_business(businesses, data);

	load_review(reviews, data);

	return data;
}

/**
 \brief Query 2
 @param data Sgr
 @param letter First letter of a business
 This query gets the business started by a letter
*/
TABLE businesses_started_by_letter(SGR data, char letter)
{
	TABLE newTable = initTable();

	setNCols(newTable, 2);
	setNQuery(newTable, 2);

	getBusinessesByLetter(data->businesses, letter, newTable);

	return newTable;
}

/**
 \brief Query 3
 @param data Sgr
 @param business_id Business id
 This query gets the name, city, state, stars, and the total number of reviews from a given business
*/
TABLE business_info(SGR data, char* business_id){
	TABLE newTable = NULL;

	if(existsBusiness(data->businesses, business_id)){
		newTable = initTable();
		float* stars = malloc(sizeof(float));
		*stars = 0;
		int* totRevs = malloc(sizeof(int));
		*totRevs = 0;

		setNCols(newTable, 5);
		setNQuery(newTable, 3);

		Business b = getBusiness(data->businesses, business_id);
		char* id = getBusinessID(b);
		char *name = getBusinessName(b);
		char *city = getBusinessCity(b);
		char *state = getBusinessState(b);
		getTotRevsAndStarsOfBus(data->reviews, id, stars, totRevs);		

		addToTable(newTable, name);
		addToTable(newTable, city);
		addToTable(newTable, state);
		addToTable(newTable, stars);
		addToTable(newTable, totRevs);
		incrementData(newTable);
		destroyBusiness(b);
	}

	return newTable;
}

/**
 \brief Query 4
 @param data Sgr
 @param user_id User id
 This query gets a list of business that a user made a review of
*/
TABLE businesses_reviewed(SGR data, char* user_id){
	TABLE newTable = NULL;

	if(existsUser(data->users, user_id)){
		newTable = initTable();
	
		setNCols(newTable, 2);
		setNQuery(newTable, 4);

		GPtrArray* revsIDs = getRevsWithUsID(data->reviews, user_id);
		if(revsIDs){
			GHashTable* busis = g_hash_table_new_full(g_str_hash, g_str_equal, free, destroyBusiness);
			for(guint i = 0; i < revsIDs->len; i++){
				Business b = getBusiness(data->businesses, (char*) g_ptr_array_index(revsIDs, i));
				g_hash_table_insert(busis, getBusinessID(b), b);
			}

			GHashTableIter iter;
			gpointer key, value;
    		g_hash_table_iter_init(&iter, busis);

			while(g_hash_table_iter_next(&iter, &key, &value)){
				Business bus = (Business) value;
				char* name = getBusinessName(bus);
				char* id = getBusinessID(bus);
				addToTable(newTable, id);
				addToTable(newTable, name);
				incrementData(newTable);
	    	}

			g_hash_table_destroy(busis);
			g_ptr_array_free(revsIDs, TRUE);
		}
	}

	return newTable;
}

/**
 \brief Query 5
 @param data Sgr
 @param stars Minimum stars wanted
 @param city City
 This query takes stars and a city and returns all of business with more stars that the given ones, and from that city
*/
TABLE businesses_with_stars_and_city(SGR data, float stars, char* city){
	TABLE newTable = NULL;
	GPtrArray* ans = getQ5Content(data->businesses, data->reviews, stars, city);
	if(ans){
		newTable = initTable(); 
		setNCols(newTable, 2);
		setNQuery(newTable, 5);
		for(guint i = 0; i < ans->len; i++){
			char* id = strdup((char*) g_ptr_array_index(ans,i++));
			char* name = strdup((char*) g_ptr_array_index(ans, i));
			addToTable(newTable, id);
			addToTable(newTable, name);
			incrementData(newTable);
		}
		g_ptr_array_free(ans, TRUE);
	}
	return newTable;
}

/**
 \brief Query 6
 @param data Sgr
 @param top Number of top rated business wanted
 This query gets a list of the top rated business from each city
*/
TABLE top_businesses_by_city(SGR data, int top){
	TABLE newTable = NULL;
	GPtrArray* ans = getQ6Content(data->businesses, data->reviews, top);
	if(ans){
		newTable = initTable();
		setNCols(newTable, 4);
		setNQuery(newTable, 6);
		for(guint i = 0; i < ans->len; i++){
			char* id = strdup((char*) g_ptr_array_index(ans, i++));
			char* name = strdup((char*) g_ptr_array_index(ans, i++));
			float* s = malloc(sizeof(float));
			*s = *((float*) g_ptr_array_index(ans, i++));
			char* city = strdup((char*) g_ptr_array_index(ans, i));
			addToTable(newTable, id);
			addToTable(newTable, name);
			addToTable(newTable, city);
			addToTable(newTable, s);
			incrementData(newTable);
		}
		g_ptr_array_free(ans, TRUE);
	}
	return newTable;
}

/**
 \brief Query 7
 @param data Sgr
 This query gets a list of all useres that have reviews on more that one state
*/
TABLE international_users(SGR data){
	TABLE newTable = NULL;
	GPtrArray* aux = getQ7content(data->businesses, data->reviews);
	if(aux){
		newTable = initTable();
		setNCols(newTable, 1);
		setNQuery(newTable, 7);
		for(guint i = 0; i < aux->len; i++){
			char* usID = strdup((char*) g_ptr_array_index(aux, i));
			addToTable(newTable, usID);
			incrementData(newTable);
		}
		g_ptr_array_free(aux, TRUE);
	}
	return newTable;
}

/**
 \brief Query 8
 @param data Sgr
 @param top Number of top rated business wanted
 @param category Business category
 This query gets a list of the top rated business with a given category
*/
TABLE top_businesses_with_category(SGR data, int top, char* category){
	TABLE newTable = NULL;
	GPtrArray* aux = getQ8content(data->businesses, data->reviews, category, top);
	if(aux){
		newTable = initTable();
		setNCols(newTable, 3);
		setNQuery(newTable, 8);
		for(guint i = 0; i < aux->len; i++){
			char* id = strdup((char*) g_ptr_array_index(aux, i++));
			char* name = strdup((char*) g_ptr_array_index(aux, i++));
			float* s = malloc(sizeof(float));
			*s = *((float*) g_ptr_array_index(aux, i));
			addToTable(newTable, id);
			addToTable(newTable, name);
			addToTable(newTable, s);
			incrementData(newTable);
		}
		g_ptr_array_free(aux, TRUE);
	}
	return newTable;
}

/**
 \brief Query 9
 @param data Sgr
 @param word Word that we want reviews with
 This query returns the reviews that contains a word
*/
TABLE reviews_with_word(SGR data, char* word){
	TABLE newTable = NULL;
	GPtrArray* aux = getQ9content(data->reviews, word);
	if(aux){
		newTable = initTable();
		setNCols(newTable, 1);
		setNQuery(newTable, 9);
		for(guint i = 0; i < aux->len; i++){
			char* id = strdup((char*) g_ptr_array_index(aux, i));
			addToTable(newTable, id);
			incrementData(newTable);
		}
		g_ptr_array_free(aux, TRUE);
	}
	return newTable;
}
