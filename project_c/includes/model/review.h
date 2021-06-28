#ifndef REVIEW_H
#define REVIEW_H

typedef struct date *Date;
typedef struct review *Review;

Review init_review(char *line);

Review cloneReview(Review r);

char * getReviewID(Review r);

char * getReviewUserID(Review r);

char * getReviewBusinessID(Review r);

float getReviewStars(Review r);

int getReviewUseful(Review r);

int getReviewFunny(Review r);

int getReviewCool(Review r);

char * getReviewText(Review r);

Date getReviewDate(Review r);

void destroyReview(void* r);

#endif