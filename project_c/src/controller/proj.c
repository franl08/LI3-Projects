#include <glib.h>
#include "../../includes/model/table.h"
#include "../../includes/model/variable.h"
#include "../../includes/controller/proj.h"

/**
 \brief Implementation of proj command
 @param colunm array of columns
 @param n Number of columns
*/
TABLE proj(VAR var, int* colunm, int n)
{
	TABLE new_table = initTable();

	TABLE original_table = getVarTable(var);

	int cols = getNCols(original_table);

	for(int i = 0; i < n; i++)
	{
		if((colunm[i] - 1) > cols)
		{
			free(original_table);
			destroyTable(new_table);

			return NULL;
		}
	}

	GPtrArray* data = getGPtrArray(original_table);

	free(original_table);

	setNCols(new_table, n);

	setNQuery(new_table, 0);

	int j = 0;

	int cols_it = 0;

	for (guint i = (colunm[j] - 1) + cols_it; i < data->len;)
	{
		addToTable(new_table, strdup((char*) g_ptr_array_index(data, i)));

		incrementData(new_table);

		if(j == n)
		{
			j = 0;

			cols_it += cols;
		}
		else j++;

		i = (colunm[j] - 1) + cols_it;
	}

	g_ptr_array_free(data, TRUE);

	return new_table;
}