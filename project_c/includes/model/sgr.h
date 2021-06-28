#ifndef SGR_H
#define SGR_H

#include "table.h"

typedef struct sgr* SGR;

SGR init_sgr();

SGR load_sgr(char* users, char* businesses, char* reviews);

void free_sgr(SGR data);

TABLE businesses_started_by_letter(SGR data, char letter);

TABLE business_info(SGR data, char* business_id);

TABLE businesses_reviewed(SGR data, char* user_id);

TABLE businesses_with_stars_and_city(SGR data, float stars, char* city);

TABLE top_businesses_by_city(SGR data, int top);

TABLE international_users(SGR data);

TABLE top_businesses_with_category(SGR data, int top, char* category);

TABLE reviews_with_word(SGR data, char* word);

#endif