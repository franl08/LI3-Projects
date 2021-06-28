#ifndef VARIABLELIST_H
#define VARIABLELIST_H

typedef struct variableList* VList;

VList initVList();

int containsElem(VList v, VAR var);

void addElem(VList v, VAR var);

VAR getVariable(VList v, int index);

VAR removeElem(VList v, VAR var);

void setVarTable(VAR var, TABLE t);

TABLE getTableFromList(VList v, VAR var);

void destroyVList(VList v);

#endif