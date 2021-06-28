#include <stdlib.h>
#include <string.h>
#include "../../includes/model/table.h"
#include "../../includes/model/variable.h"

/**
 \brief Variable struct
*/
struct variable
{
	char* varName;
	TABLE tbl;
};

/**
 \brief Initializes a variable
*/
VAR initVariable()
{
	VAR var = malloc(sizeof(struct variable));

	var->varName = NULL;

	var->tbl = initTable();

	return var;
}

/**
 \brief Get a variable name
 @param var Variable
*/
char* getVarName(VAR var)
{
	return strdup(var->varName);
}

/**
 \brief Gets the table from a var
*/
TABLE getVarTable(VAR var)
{
	return var->tbl;
}

/**
 \brief Sets a variable name
 @param var Variable
 @param name Name to the variable
*/
void setVarName(VAR var, char* name)
{
	var->varName = strdup(name);
}

/**
 \brief Sets a Variable Table
 @param var Variable
 @param t Table
*/
void setVarTable(VAR var, TABLE t)
{
	destroyTable(var->tbl);

	var->tbl = t;
}

/**
 \brief Clones a Variable
 @param var Variable to clone
*/
VAR cloneVariable(VAR var)
{
	VAR res = initVariable();

	setVarName(res, getVarName(var));

	setVarTable(res, getVarTable(var));

	return res;
}

/**
 \brief Destroys a Variable
 @param var Variable to Destroy
*/
void destroyVariable(VAR var)
{
	free(var->varName);

	destroyTable(var->tbl);

	free(var);
}