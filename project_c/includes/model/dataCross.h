#ifndef DATACROSS_H
#define DATACROSS_H

GPtrArray* getQ5Content(Businesses b, Reviews rev, float stars, char* city);

GPtrArray* getQ6Content(Businesses busis, Reviews revs, int n);

GPtrArray* getQ7content(Businesses busis, Reviews revs);

GPtrArray* getQ8content(Businesses busis, Reviews revs, char* category, int n);

GPtrArray* getQ9content(Reviews revs, char* word);

#endif