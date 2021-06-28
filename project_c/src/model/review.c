#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/model/review.h"
#include "../../includes/config.h"

/**
 \brief Review date struct
*/
struct date
{
	int year;
	short month;
	short day;
	short hour;
	short minute;
	short second;
};

/**
 \brief Review struct
*/
struct review
{
	char* review_id;
	char* user_id;
	char* business_id;
	float stars;
	int useful;
	int funny;
	int cool;
	Date date;
	char* text;
};

/**
 \brief verifies if it is a valid review
 @param line Content to check if it is a review
*/
int validRev(char *line){
	int j, dotCommas = 0, revIDSize = 0, usIDSize = 0, busIDSize = 0, flag = 1;
	for (j = 0; line[j] && flag; j++){
		if(line[j] == ';') dotCommas++;
		else if(dotCommas == 0) revIDSize++;
		else if(dotCommas == 1) usIDSize++;
		else if(dotCommas == 2) busIDSize++;
		if(dotCommas == REVIEWSEPS) flag = 0;
	}
	if(dotCommas != REVIEWSEPS || revIDSize != IDSIZE|| usIDSize != IDSIZE || busIDSize != IDSIZE) return 0;
	return 1; 
}

/**
 \brief Initializes a Review
 @param line Content to check if it is a review
*/
Review init_review(char *line){
	if (validRev(line)){
		Review review = malloc(sizeof(struct review));
		review->review_id = strdup(strsep(&line, ";"));
		review->user_id = strdup(strsep(&line, ";"));
		review->business_id = strdup(strsep(&line, ";"));
		review->stars = atof(strsep(&line, ";"));
		review->useful = atoi(strsep(&line, ";"));
		review->funny = atoi(strsep(&line, ";"));
		review->cool = atoi(strsep(&line, ";"));
		review->date = malloc(sizeof(Date));
		review->date->year = atoi(strsep(&line, "-"));
		review->date->month = (short) atoi(strsep(&line, "-"));
		review->date->day = (short) atoi(strsep(&line, " "));
		review->date->hour = (short) atoi(strsep(&line, ":"));
		review->date->minute = (short) atoi(strsep(&line, ":"));
		review->date->second = (short) atoi(strsep(&line, ";"));
		review->text = strdup(strsep(&line, "\n"));
		return review;
	}
	return NULL;
}

/**
 \brief clones a review
 @param r Review
*/
Review cloneReview(Review r){
	Review newRev = malloc(sizeof(struct review));
	newRev->review_id = strdup(r->review_id);
	newRev->user_id = strdup(r->user_id);
	newRev->business_id = strdup(r->business_id);
	newRev->stars = r->stars;
	newRev->useful = r->useful;
	newRev->funny = r->funny;
	newRev->cool = r->cool;
	newRev->date =  malloc(sizeof(struct date));
	newRev->date->year = r->date->year;
	newRev->date->month = r->date->month;
	newRev->date->day = r->date->day;
	newRev->date->hour = r->date->hour;
	newRev->date->minute = r->date->minute;
	newRev->date->second = r->date->second;
	newRev->text = strdup(r->text);
	return newRev;
}

/**
 \brief Gets the review id
 @param r Review
*/
char * getReviewID(Review r){
	return(strdup(r->review_id));
}

/**
 \brief Gets the user id from the review
 @param r Review
*/
char * getReviewUserID(Review r){
	return(strdup(r->user_id));
}

/**
 \brief Gets the business id from the review
 @param r Review
*/
char * getReviewBusinessID(Review r){
	return(strdup(r->business_id));
}

/**
 \brief Gets the review stars
 @param r Review
*/
float getReviewStars(Review r){
	return r->stars;
}

/**
 \brief Gets the review useful rating
 @param r Review
*/
int getReviewUseful(Review r){
	return r->useful;
}

/**
 \brief Gets the review funny rating
 @param r Review
*/
int getReviewFunny(Review r){
	return r->funny;
}

/**
 \brief Gets the review cool rating
 @param r Review
*/
int getReviewCool(Review r){
	return r->cool;
}

/**
 \brief Gets the review text
 @param r Review
*/
char * getReviewText(Review r){
	return (strdup(r->text));
}

/**
 \brief Deletes a review
 @param r Review
*/
void destroyReview(void* rev){
	Review r = (Review) rev;
	free(r->review_id);
	free(r->user_id);
	free(r->business_id);
	free(r->date);
	free(r->text);
	free(r);
}