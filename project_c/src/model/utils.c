#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../includes/model/table.h"
#include "../../includes/model/utils.h"

/**
 \brief version of tolower but to strings
*/
void tolowerSTR(char *str){
  for( ; *str; str++)
      *str = tolower(*str);
}

/**
 \brief creates a table to help the user with the commands
*/
TABLE createHelpTable(){
  TABLE t = initTable();
	setNQuery(t, 10);
	setNCols(t, 1);

  char* command1 = "businesses_started_by_letter(sgr, letter);";
	char* command2 = "business_info(sgr, Business_id);";
	char* command3 = "businesses_reviewed(sgr, User_id);";
	char* command4 = "businesses_with_stars_and_city(sgr, stars, Business_city);";
	char* command5 = "top_businesses_by_city(sgr, n);";
	char* command6 = "international_users(sgr);";
	char* command7 = "top_businesses_with_category(sgr, n, Business_category);";
	char* command8 = "reviews_with_word(sgr, n, word);";
	char* command9 = "show(var);";
	char* command10 = "toCSV(var, delim, filepath);";
	char* command11 = "fromCSV(filepath, delim);";
	char* command12 = "filter(var, colunm_name, value, oper);";
	char* command13 = "proj(var, cols);";
	char* command14 = "x[i][j];";
	char* command15 = "quit;";	

	addToTable(t, command1);
	addToTable(t, command2);
	addToTable(t, command3);
	addToTable(t, command4);
	addToTable(t, command5);
	addToTable(t, command6);
	addToTable(t, command7);
	addToTable(t, command8);
	addToTable(t, command9);
	addToTable(t, command10);
	addToTable(t, command11);
	addToTable(t, command12);
	addToTable(t, command13);
	addToTable(t, command14);
	addToTable(t, command15);

  return t;
}

/**
 \brief auxiliar function to free a GPtrArray*
*/
void freeArr(void* g){
	GPtrArray* gp = (GPtrArray*) g;
    g_ptr_array_free(gp, TRUE);
}