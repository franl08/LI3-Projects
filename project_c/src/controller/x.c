#include <glib.h>
#include "../../includes/model/table.h"
#include "../../includes/model/variable.h"
#include "../../includes/controller/x.h"

/**
 \brief Implementation of [x][y] command
 @param var Variable to find the value
 @param first Number of the table line
 @param second Number of the table column
*/
TABLE x(VAR var, int first, int second)
{
	TABLE new_table = initTable();

	TABLE original_table = getVarTable(var);

	int original_query = getNQuery(original_table);

	int cols = getNCols(original_table);

	int line = first * getInsertedData(original_table);

	if(line > getInsertedData(original_table) || second > cols)
	{
		free(original_table);
		destroyTable(new_table);

		return NULL;
	}

	GPtrArray* data = getGPtrArray(original_table);

	free(original_table);

	setNCols(new_table, 1);
	
	if(original_query == 3 && second == 4 || original_query == 6 && second == 4 || original_query == 8 && second == 3)
	{

		setNQuery(new_table, 11);

		for (guint i = 0; i < data->len; i++)
		{
			for(int j = 0; j < cols; j++)
			{
				if((int) i == (line - 1) && j == (second - 1))
				{
					float* toAdd = malloc(sizeof(float));

					*toAdd = *((float*) g_ptr_array_index(data, i));

					addToTable(new_table, toAdd);

					incrementData(new_table);

					g_ptr_array_free(data, TRUE);

					return new_table;
				}
			}
		}
	}

	else if (original_query == 3 && second == 5)
	{

		setNQuery(new_table, 12);

		for (guint i = 0; i < data->len; i++)
		{
			for(int j = 0; j < cols; j++)
			{
				if((int) i == (line - 1) && j == (second - 1))
				{
					int* toAdd = malloc(sizeof(int));

					*toAdd = *((int*) g_ptr_array_index(data, i));

					addToTable(new_table, toAdd);

					incrementData(new_table);

					g_ptr_array_free(data, TRUE);

					return new_table;
				}
			}
		}

	}

	else
	{
		
		setNQuery(new_table, 0);

		for (guint i = 0; i < data->len; i++)
		{
			for(int j = 0; j < cols; j++)
			{
				if((int) i == (line - 1) && j == (second - 1))
				{

					char* toAdd = strdup((char*) g_ptr_array_index(data, i));

					addToTable(new_table, toAdd);

					incrementData(new_table);

					g_ptr_array_free(data, TRUE);

					return new_table;
				}
			}
		}

	}

	

	g_ptr_array_free(data, TRUE);

	return NULL;
}