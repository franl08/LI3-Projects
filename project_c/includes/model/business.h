#ifndef BUSINESS_H
#define BUSINESS_H

#include <glib.h>

typedef struct business *Business;

int validBus(char *line);

Business init_business(char *line);

char * getBusinessID(Business b);

char * getBusinessName(Business b);

char * getBusinessCity(Business b);

char * getBusinessState(Business b);

GPtrArray* getBusinessCategories(Business b);

Business cloneBusiness(Business b);

void destroyBusiness(void* b);

#endif