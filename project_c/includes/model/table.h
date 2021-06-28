#ifndef TABLE_H
#define TABLE_H

#include <glib.h>

typedef struct table *TABLE;

TABLE initTable();

GPtrArray* getGPtrArray(TABLE t);

int getNCols(TABLE t);

int getInsertedData(TABLE t);

void setNCols(TABLE t, int n);

void setNQuery(TABLE t, int n);

void setInsertedData(TABLE t, int n);

int getNQuery(TABLE t);

void incrementData(TABLE t);

void addToTable(TABLE t, gpointer data);

TABLE cloneTable(TABLE t);

void destroyTable(TABLE t);

#endif