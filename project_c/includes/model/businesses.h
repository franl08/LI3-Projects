#ifndef BUSINESSES_H
#define BUSINESSES_H

#include "business.h"
#include "table.h"
#include <stdbool.h>

typedef struct businesses* Businesses;

Businesses initBusinesses();

void addBus(Businesses busis, const Business bus);

bool existsBusiness(Businesses busis, char* id);

Business getBusiness(Businesses busis, char* id);

void getBusinessesByLetter(Businesses busis, char letter, TABLE tble);

GPtrArray* getIdsInCity(Businesses busis, char* city);

GPtrArray* getTopNIDSinCities(Businesses busis, GHashTable* hT, int n);

GPtrArray* getTopNWithCategory(Businesses busis, GHashTable* hT, char* category, int n);

GPtrArray* createInterUsers(Businesses busis, GHashTable* usWithBusID);

char* getBusinessNameWithID(Businesses busis, char* id);

void freeBusinesses(Businesses busis);

#endif