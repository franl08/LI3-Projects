#ifndef VARIABLE_H
#define VARIABLE_H

#include "table.h"

typedef struct variable *VAR;

VAR initVariable();

char* getVarName(VAR var);

TABLE getVarTable(VAR var);

void setVarName(VAR var, char* name);

void setVarTable(VAR var, TABLE t);

VAR cloneVariable(VAR var);

void destroyVariable(VAR var);

void destroyVariable(VAR var);

#endif