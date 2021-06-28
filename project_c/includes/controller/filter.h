#ifndef FILTER_H
#define FILTER_H

#include "../model/table.h"
#include "../model/variable.h"

TABLE filter(int colunm, char* value, char* operator, VAR var);

#endif