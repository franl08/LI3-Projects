#ifndef UI_H
#define UI_H

#include "../model/table.h"

void printTableLine(GPtrArray* content, int nPars, int max);

void printTable(TABLE t);

void show(TABLE t);

void initShow();

void showFilePath();

void showMessage(char* message);

void printPageNum(int cur, int max);

void printSize(int elems);

void printOptions(int aux, int min);

void printOnlyPage();

void printLastPage();

void printHelpTop();

void printHelpLine(char* comm);

void printHelp(TABLE t);

void printQ3(TABLE t);

void printQ2Q4Q5Line(char* id, char* name, int max);

void printQ2Q4Q5Top(int max);

void printQ2Q4Q5(TABLE t);

void printQ6Top(int max);

void printQ6Line(char* id, char* name, char* city, float av, int max);

void printQ6(TABLE t);

void printQ7Top();

void printQ7Line(char* id);

void printQ7(TABLE t);

void printQ8Line(char* id, char* name, float av, int max);

void printQ8Top(int max);

void printQ8(TABLE t);

void printQ9Top();

void printQ9Line(char* id);

void printQ9(TABLE t);

#endif 