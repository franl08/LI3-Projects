#include <string.h>
#include <glib.h>
#include "../../includes/model/table.h"
#include "../../includes/model/variable.h"
#include "../../includes/controller/filter.h"

/**
 \brief GT command
*/
const char greater[] = "GT";
/**
 \brief EQ command
*/
const char equal[] = "EQ";
/**
 \brief LT command
*/
const char lesser[] = "LT";

/**
 \brief GT filter
 @param t TABLE table to read
 @param value Value from what we want to filter
 @param data GPtrArray* to add data
*/
static void filterGT(TABLE t, char* value, int colunm, GPtrArray* data)
{
	int cols = getNCols(t);

	for (guint i = colunm-1; i < data->len; i+=cols)
	{
		char* comp = strdup(g_ptr_array_index(data, i));

		if(strcmp(comp, value) > 0)
		{
			for(int j = i - (colunm -1); j < cols; j++)
			{
				addToTable(t, strdup(g_ptr_array_index(data, j)));
			}

			incrementData(t);
		}

		free(comp);
	}
}

/**
 \brief EQ filter
 @param t TABLE table to read
 @param value Value from what we want to filter
 @param data GPtrArray* to add data
*/
static void filterEQ(TABLE t, char* value, int colunm, GPtrArray* data)
{
	int cols = getNCols(t);

	int pos = colunm - 1;

	for(int i = pos; i < data->len; i += cols)
	{
		char* comp = strdup((char*) g_ptr_array_index(data, i));

		if(strcmp(comp, value) == 0)
		{
			for(int j = i - pos; j < cols;)
			{
				addToTable(t, (char*) strdup(g_ptr_array_index(data,j++)));
			}

			incrementData(t);
		}

		free(comp);
	}
}

/**
 \brief LT filter
 @param t TABLE table to read
 @param value Value from what we want to filter
 @param data GPtrArray* to add data
*/
static void filterLT(TABLE t, char* value, int colunm, GPtrArray* data)
{
	int cols = getNCols(t);

	for (guint i = colunm-1; i < data->len; i+=cols)
	{
		char* comp = strdup(g_ptr_array_index(data, i));

		if(strcmp(comp, value) < 0)
		{
			for(int j = i - (colunm -1); j < cols; j++)
			{
				if (i<10)
				{
					printf("%d\n", j);
				}

				addToTable(t, (char*) strdup(g_ptr_array_index(data,j)));
			}

			incrementData(t);
		}

		free(comp);
	}
}

/**
 \brief General function of filter
 @param colunm Number of the column 
 @param value Value from what we want to filter
 @param operator EQ/GT/LT
 @param var Variable to filter
*/
TABLE filter(int colunm, char* value, char* operator, VAR var)
{
	TABLE new_table = initTable();

	TABLE original_table = getVarTable(var);

	int cols = getNCols(original_table);

	if(colunm > cols)
	{
		free(original_table);
		destroyTable(new_table);

		return NULL;
	}

	setNCols(new_table, getNCols(original_table));

	setNQuery(new_table, getNQuery(original_table));

	GPtrArray* data = getGPtrArray(original_table);

	free(original_table);

	if(strcmp(operator, greater) == 0)
		filterGT(new_table, value, colunm, data);

	else if(strcmp(operator, equal) == 0)
		filterEQ(new_table, value, colunm, data);

	else if(strcmp(operator, lesser) == 0) 
		filterLT(new_table, value, colunm, data);

	else return NULL;
	
	g_ptr_array_free(data, TRUE);

	return new_table;
}