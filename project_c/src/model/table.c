#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../includes/model/table.h"

/**
 \brief table struct
*/
struct table {
	GPtrArray* lines;
	int insertedData; // aka nº de dados inseridos no total
	int nCols; // aka nº parametros da query
	int nQuery; // aka query da table (useful for print)
};

/**
 \brief Initializes a table
*/
TABLE initTable(){
	TABLE t = malloc(sizeof(struct table));
	t->lines = g_ptr_array_new_full(0, g_free);
	t->nCols = 0;
	t->insertedData = 0;
	t->nQuery = 0;
	return t;
}

/**
 \brief Adds data to a table
 @param t Table
 @param data Data to be added
*/
void addToTable(TABLE t, gpointer data)
{
	g_ptr_array_add(t->lines, data);
}

/**
 \brief Increases the parameter insertData
 @param t Table
 This is used to know the amount of data that a table containsg_ptr_array_index
*/
void incrementData(TABLE t){
	t->insertedData++;
}

/**
 \brief Gets the data that the table contains
 @param t Table
*/
void getArr245(TABLE t, GPtrArray* ans){
	for(guint i = 0; i < t->lines->len; ){
		char* id = strdup((char*) g_ptr_array_index(t->lines, i++));
		char* name = strdup((char*) g_ptr_array_index(t->lines, i++));
		g_ptr_array_add(ans, id);
		g_ptr_array_add(ans, name);
	}
}

void getArr79(TABLE t, GPtrArray* ans){
	for(guint i = 0; i < t->lines->len; ){
		char* id = strdup((char*) g_ptr_array_index(t->lines, i++));
		g_ptr_array_add(ans, id);
	}
}

/**
 \brief Gets the data that the table contains
 @param t Table
*/
GPtrArray* getGPtrArray(TABLE t)
{
	GPtrArray* ans = g_ptr_array_new_full(t->lines->len, free);
	switch(getNQuery(t)){
		case 2:
			getArr245(t, ans);
			break;
		case 3:
			for(guint i = 0; i < t->lines->len; ){
				char* name = strdup((char*) g_ptr_array_index(t->lines, i++));
				char* city = strdup((char*) g_ptr_array_index(t->lines, i++));
				char* state = strdup((char*) g_ptr_array_index(t->lines, i++));
				float* st = malloc(sizeof(float));
				*st = *((float*) g_ptr_array_index(t->lines, i++));
				int* r = malloc(sizeof(int));
				*r = *((int*) g_ptr_array_index(t->lines, i++));
				g_ptr_array_add(ans, name);
				g_ptr_array_add(ans, city);
				g_ptr_array_add(ans, state);
				g_ptr_array_add(ans, st);
				g_ptr_array_add(ans, r);
			}
			break;
		case 4:
			getArr245(t, ans);
			break;
		case 5:
			getArr245(t, ans);
			break;
		case 6:
			for(guint i = 0; i < t->lines->len; ){
				char* id = strdup((char*) g_ptr_array_index(t->lines, i++));
				char* name = strdup((char*) g_ptr_array_index(t->lines, i++));
				char* city = strdup((char*) g_ptr_array_index(t->lines, i++));
				float* st = malloc(sizeof(float));
				*st = *((float*) g_ptr_array_index(t->lines, i++));
				g_ptr_array_add(ans, id);
				g_ptr_array_add(ans, name);
				g_ptr_array_add(ans, city);
				g_ptr_array_add(ans, st);
			}
			break;
		case 7:
			getArr79(t, ans);
			break;
		case 8:
			for(guint i = 0; i < t->lines->len; ){
				char* id = strdup((char*) g_ptr_array_index(t->lines, i++));
				char* name = strdup((char*) g_ptr_array_index(t->lines, i++));
				float* st = malloc(sizeof(float));
				*st = *((float*) g_ptr_array_index(t->lines, i++));
				g_ptr_array_add(ans, id);
				g_ptr_array_add(ans, name);
				g_ptr_array_add(ans, st);
			}
			break;
		case 9:
			getArr79(t, ans);
			break;
		default:
			for(guint i = 0; i < t->lines->len; i++){
				char* toAdd = strdup((char*) g_ptr_array_index(t->lines, i));
				g_ptr_array_add(ans, toAdd);
			}
			break;

	}
	return ans;
}

/**
 \brief Gets the number of parameters of the query
 @param t Table
*/
int getNCols(TABLE t){
	return t->nCols;
}

/**
 \brief Gets the amount of data that the table contains
 @param t Table
*/
int getInsertedData(TABLE t){
	return t->insertedData;
}

/**
 \brief Insert the number of parameters of the query
 @param t Table
 @param n Number of parameters
*/
void setNCols(TABLE t, int n){
	t->nCols = n;
}

/**
 \brief Insert the amount of data of the query
 @param t Table
 @param n Amount of data
*/
void setInsertedData(TABLE t, int n)
{
	t->insertedData = n;
}

/**
 \brief Insert the query number
 @param t Table
 @param n Query number
*/
void setNQuery(TABLE t, int n){
	t->nQuery = n;
}

/**
 \brief Gets the query number
 @param t Table
*/
int getNQuery(TABLE t){
	return (t->nQuery);
}

/**
 \brief Clones a table
 @param t Table
*/
TABLE cloneTable(TABLE t){
	TABLE copy = initTable();
	copy->lines = getGPtrArray(t);
	copy->nCols = getNCols(t);
	copy->insertedData = getInsertedData(t);
	return t;
}

/**
 \brief Deletes a table
 @param t Table
*/
void destroyTable(TABLE t){
	g_ptr_array_free(t->lines, TRUE);
	free(t);
}