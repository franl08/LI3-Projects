#ifndef REVIEWS_H
#define REVIEWS_H

#include "review.h"

typedef struct reviews* Reviews;

Reviews initReviews();

void addReview(Reviews revs, const Review rev);

void getTotRevsAndStarsOfBus(Reviews revs, char* bus_id, float* stars, int* totRevs);

GPtrArray* getInCityWithStars(Reviews rev, float stars, GPtrArray* idsInCity);

GHashTable* getBusInCityWithRevsAndStars(Reviews revs, GHashTable* citiesAndIDs);

GHashTable* createHashForBus(Reviews revs);

GPtrArray* getRevsWithUsID(Reviews revs, char* user_id);

GHashTable* createHashForBusWithAverage(Reviews revs);

GHashTable* createHashForUsWithBusID(Reviews revs);

GPtrArray* getIdsWithWord(Reviews revs, char* word);

void freeReviews(Reviews r);

#endif