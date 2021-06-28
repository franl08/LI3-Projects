#include <stdlib.h>
#include "../../includes/model/variable.h"
#include "../../includes/model/variable_list.h"

/**
 \brief Variable List struct
*/
struct variableList
{
	VAR* list;
	int numElem;
	int freeElem;
};

/**
 \brief Initializes a Variable List
*/
VList initVList()
{
	VList v = malloc(sizeof (struct variableList));

	v->list = NULL;

	v->numElem = 0;

	v->freeElem = 0;

	return v;
}

/**
 \brief Verifies if a VList contains an variable
 @param v Variable List
 @param var Variable
*/
int containsElem(VList v, VAR var)
{
	for (int i = 0; i < v->numElem; i++)
	{
		if(strcmp(getVarName(v->list[i]), getVarName(var)) == 0) return i;
	}

	return (-1);
}

/**
 \brief Adds an variable to a VList
 @param v Variable List
 @param var Variable
*/
void addElem(VList v, VAR var)
{
	if(containsElem(v, var) != -1) return;

	v->numElem++;

	if(v->freeElem == 0) 
	{
		v->list = realloc(v->list, sizeof(VAR) * v->numElem);
		v->list[v->numElem - 1] = var;
	}
	else
	{
		int i;

		for(i = 0; v->list[i] != NULL; i++);

		v->list[i] = var;

		v->freeElem--;
	}
}

/**
 \brief Gets a table from a Variable List
 @param v Variable List
 @param var Variable
*/
TABLE getTableFromList(VList v, VAR var)
{
	if(containsElem(v, var) == -1) return NULL;

	return getVarTable(v->list[containsElem(v, var)]); 
}

/**
 \brief Gets a Variable from a Variable List
 @param v Variable List
 @param index Index of the Variable
*/
VAR getVariable(VList v, int index)
{
	return v->list[index];
}

/**
 \brief Removes an element from a Variable List
 @param v Variable List
 @param var Variable
*/
VAR removeElem(VList v, VAR var)
{
	if(containsElem(v, var) == -1) return NULL;

	VAR aux = v->list[containsElem(v, var)];

	v->list[containsElem(v, var)] = NULL;

	v->freeElem++;

	return aux;
}

/**
 @param v Variable List
*/
void destroyVList(VList v)
{
	for(int i = 0; i < v->numElem; i++) destroyVariable(v->list[i]);

	free(v);
}