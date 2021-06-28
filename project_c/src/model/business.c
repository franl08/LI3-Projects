#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/model/business.h"
#include "../../includes/config.h"

/**
 Business struct
*/
struct business
{
	char* business_id;
	char* name;
	char* city;
	char* state;
	GPtrArray* categories;
};
/**
 \brief checks if the argument it's a business
 @param line Content to check if it is a review
*/
int validBus(char *line){
	int j, dotCommas = 0, idSize = 0, commas = 0;

	for (j = 0; line[j]; j++){
		if(line[j] == ';') dotCommas++;
		if(!dotCommas) idSize++;
		if(dotCommas == BUSSEPS && line[j] == ',') commas++;
	}
	if(dotCommas != BUSSEPS || idSize != IDSIZE) return -1;

	return (commas + 1);
}
/**
 \brief initializes a business
 @param line Content to check if it is a review
*/
Business init_business(char *line){

	int cats = validBus(line), j;

	if(cats != -1){
		Business business = malloc(sizeof(struct business));
		business->business_id = strdup(strsep(&line, ";"));
		business->name = strdup(strsep(&line, ";"));
		business->city = strdup(strsep(&line, ";"));
		business->state = strdup(strsep(&line, ";"));
		business->categories = g_ptr_array_new_full(cats, free);
		for(j = 0; j < cats; j++)
			g_ptr_array_add(business->categories, strdup(strsep(&line, ",")));
		return business;
	}
	return NULL;
}


/**
 \brief Duplicates a business_id
 @param b Business
*/
char * getBusinessID(Business b){
	return(strdup(b->business_id));
}

/**
 \brief Duplicates the business name
 @param b Business
*/
char * getBusinessName(Business b){
	return(strdup(b->name));
}

/**
 \brief Duplicates the business name
 @param b Business
*/
char * getBusinessCity(Business b){
	return(strdup(b->city));
}

/**
 \brief Duplicates the business state
 @param b Business
*/
char * getBusinessState(Business b){
	return(strdup(b->state));
}

/**
 \brief Duplicates the business categories
 @param b Business
*/
GPtrArray* getBusinessCategories(Business b){
	GPtrArray* ans = g_ptr_array_new_full(b->categories->len, free);
	for(guint i = 0; i < b->categories->len; i++)
		g_ptr_array_add(ans, strdup((char*) g_ptr_array_index(b->categories, i)));

	return ans;
}

/**
 \brief Clones a business
 @param b Business
*/
Business cloneBusiness(Business b){
	int size;

	Business newBus = (Business) malloc(sizeof(struct business));
	newBus->business_id = strdup(b->business_id);
	newBus->name = strdup(b->name);
	newBus->city = strdup(b->city);
	newBus->state = strdup(b->state);
	newBus->categories = getBusinessCategories(b);

	return newBus;
}

/**
 \brief Deletes a business
 @param b Business
*/
void destroyBusiness(void* bus){
	Business b = (Business) bus;

	free(b->business_id);
	free(b->name);
	free(b->city);
	free(b->state);
	g_ptr_array_free(b->categories, TRUE);
	free(b);
}
