#ifndef CSV_H
#define CSV_H

#include "../model/table.h"
#include "../errors.h"


ERROR toCSV(TABLE t, char* delim, char* filepath);

TABLE fromCSV(char* filepath, char* delim);

#endif