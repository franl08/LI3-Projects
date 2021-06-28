#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include "../../includes/model/table.h"
#include "../../includes/controller/csv.h"
#include "../../includes/errors.h"
#include "../../includes/config.h"

/**
 \brief Implementation of toCSV command
 @param t TABLE to pass to CSV
 @param delim String of delimiter
 @param filepath Path to the generated file
*/
ERROR toCSV(TABLE t, char* delim, char* filepath)
{
	if(delim[0] != ';' && delim[0] != ',') 
		return INVALID_DELIM;

	FILE* f;

	strcat(filepath, ".csv");

	f = fopen(filepath, "w+");

	int cols = getNCols(t);

	int inserted_data = getInsertedData(t);

	int nQuery = getNQuery(t);

	char param1[20], param2[20], param3[20];

	sprintf(param1, "%d", cols);

	sprintf(param2, "%d", inserted_data);

	sprintf(param3, "%d", nQuery);

	char* aux = strdup(param1);

	strcat(aux, delim);
	strcat(aux, param2);
	strcat(aux, delim);
	strcat(aux, param3);

	fprintf(f, "%s\n", aux);

	free(aux);

	GPtrArray* data = getGPtrArray(t);

	for(guint i = 0; i < data->len;)
	{
		char** to_write = malloc(sizeof(char*) * cols);

		for(int j = 0; j < cols; j++)
		{
			to_write[j] = strdup((char*) g_ptr_array_index(data, i++));
		}

		for(int j = 0; j < cols-1; j++)
		{
			fprintf(f, "%s;", to_write[j]);
			free(to_write[j]);
		}

		fprintf(f, "%s\n", to_write[cols-1]);
		free(to_write[cols-1]);

		free(to_write);
	}

	fclose(f);

	g_ptr_array_free(data, TRUE);

	return SUCCESS;
}

/**
 \brief Implementation of fromCSV command
 @param filepath Path to the file to read
 @param delim String of delimiter
*/
TABLE fromCSV(char* filepath, char* delim)
{
	if(delim[0] != ';' && delim[0] != ',') 
		return NULL;


	strcat(filepath, ".csv");

	char del[1] = {delim};

	TABLE ans = initTable();

	FILE* f = fopen(filepath, "r");

	char* to_read = malloc(sizeof(char) * BUFFERSIZE);

	if(fgets(to_read, BUFFERSIZE, f))
	{
		char* buff = strdup(to_read);

		char* ncols = strdup(strsep(&buff, ";"));
		int param1 = atoi(ncols);

		char* insertdata = strdup(strsep(&buff, ";"));
		int param2 = atoi(insertdata);

		char* query = strdup(strsep(&buff, ";"));
		int param3 = atoi(query);
	
		setNCols(ans, param1);
	
		setInsertedData(ans, param2);
					
		setNQuery(ans, param3);

		free(ncols);
		free(insertdata);
		free(query);
	}

	while(fgets(to_read, BUFFERSIZE, f))
	{
		char* buff = strdup(to_read);

		while(to_read[0] != '\0')
		{
			char* aux = strdup(strsep(&buff, ";"));
			
			addToTable(ans, aux);

			free(aux);
		}
	}

	return ans;
}