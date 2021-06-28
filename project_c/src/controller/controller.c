#include <stdbool.h>
#include <string.h>
#include <stdio.h> 
#include "../../includes/controller/csv.h"
#include "../../includes/controller/filter.h"
#include "../../includes/controller/proj.h"
#include "../../includes/controller/x.h"
#include "../../includes/controller/controller.h"
#include "../../includes/controller/comint.h"
#include "../../includes/model/variable.h"
#include "../../includes/model/variable_list.h"
#include "../../includes/model/sgr.h"
#include "../../includes/config.h"
#include "../../includes/errors.h"
#include "../../includes/view/ui.h"
#include "../../includes/model/utils.h"

VList list;

/**
 \brief Verifies if a string has a ';' as an element and adds it to the command.
 @param commands String that represents the command
*/

static char* sep_val(char* commands)
{
	char* res = strsep(&commands, ";");

	if(commands[0] == 34)
	{
		char* add = strsep(&commands, ";");
		strcat(res, ";");
		strcat(res, add);
	}

	return res;
}

/**
 \brief Iniciates the global variable list.
*/

static void initVariableList(){
	list = initVList();
}

/**
 \brief Links the controller with the SGR to execute the second query.
 @param sgr Struct SGR that holds all the information.
 @param command String that holds the command given and has all the parameters required to execute the query. 
*/

static ERROR businesses_started_by_letter_con(SGR sgr, char* command)
{
	VAR var = initVariable();

	char* buff = strdup(command);

	setVarName(var, strdup(strsep(&buff, "=")));

	if(containsElem(list, var) != -1) 
	{
		destroyVariable(var);

		return VARIABLE_NAME_ALREADY_IN_USE;
	}

	strsep(&buff, "'");

	char letter = buff[0];

	setVarTable(var, businesses_started_by_letter(sgr, letter));

	addElem(list, var);

	return SUCCESS;
}

/**
 \brief Links the controller with the SGR to execute the third query.
 @param sgr Struct SGR that holds all the information.
 @param command String that holds the command given and has all the parameters required to execute the query. 
*/

static ERROR business_info_con(SGR sgr, char* command)
{
	VAR var = initVariable();

	char* buff = strdup(command);

	setVarName(var, strdup(strsep(&buff, "=")));

	if(containsElem(list, var) != -1) 
	{
		destroyVariable(var);
		free(buff);

		return VARIABLE_NAME_ALREADY_IN_USE;
	}

	strsep(&buff, ",");

	char* bus_id = strdup(strsep(&buff, ")"));

	setVarTable(var, business_info(sgr, bus_id));

	addElem(list, var);

	free(bus_id);

	return SUCCESS;
}

/**
 \brief Links the controller with the SGR to execute the fourth query.
 @param sgr Struct SGR that holds all the information.
 @param command String that holds the command given and has all the parameters required to execute the query. 
*/

static ERROR businesses_reviewed_con(SGR sgr, char* command)
{
	VAR var = initVariable();

	char* buff = strdup(command);

	setVarName(var, strdup(strsep(&buff, "=")));

	if(containsElem(list, var) != -1) 
	{
		destroyVariable(var);

		return VARIABLE_NAME_ALREADY_IN_USE;
	}

	strsep(&buff, ",");

	char* user_id = strdup(strsep(&buff, ")"));

	setVarTable(var, businesses_reviewed(sgr, user_id));

	addElem(list, var);

	free(user_id);

	return SUCCESS;
}

/**
 \brief Links the controller with the SGR to execute the fifth query.
 @param sgr Struct SGR that holds all the information.
 @param command String that holds the command given and has all the parameters required to execute the query. 
*/

static ERROR businesses_with_stars_and_city_con(SGR sgr, char* command)
{
	VAR var = initVariable();

	char* buff = strdup(command);

	setVarName(var, strdup(strsep(&buff, "=")));

	if(containsElem(list, var) != -1) 
	{
		destroyVariable(var);

		return VARIABLE_NAME_ALREADY_IN_USE;
	}

	strsep(&buff, ",");

	char* float_char = strdup(strsep(&buff, ","));

	float float_arg = strtof(float_char, NULL);

	char* city = strdup(strsep(&buff, ")"));

	setVarTable(var, businesses_with_stars_and_city(sgr, float_arg, city));

	addElem(list, var);

	free(float_char);

	free(city);

	return SUCCESS;
}

/**
 \brief Links the controller with the SGR to execute the sixth query.
 @param sgr Struct SGR that holds all the information.
 @param command String that holds the command given and has all the parameters required to execute the query. 
*/

static ERROR top_businesses_by_city_con(SGR sgr, char* command)
{
	VAR var = initVariable();

	char* buff = strdup(command);

	setVarName(var, strdup(strsep(&buff, "=")));

	if(containsElem(list, var) != -1) 
	{
		destroyVariable(var);

		return VARIABLE_NAME_ALREADY_IN_USE;
	}

	strsep(&buff, ",");

	char* int_char = strdup(strsep(&buff, ")"));

	int top = atoi(int_char);

	setVarTable(var, top_businesses_by_city(sgr, top));

	addElem(list, var);

	free(int_char);

	return SUCCESS;
}

/**
 \brief Links the controller with the SGR to execute the seventh query.
 @param sgr Struct SGR that holds all the information.
 @param command String that holds the command given and has all the parameters required to execute the query. 
*/

static ERROR international_users_con(SGR sgr, char* command)
{
	VAR var = initVariable();

	char* buff = strdup(command);

	setVarName(var, strdup(strsep(&buff, "=")));

	if(containsElem(list, var) != -1) 
	{
		destroyVariable(var);

		return VARIABLE_NAME_ALREADY_IN_USE;
	}

	setVarTable(var, international_users(sgr));

	addElem(list, var);

	return SUCCESS;
}

/**
 \brief Links the controller with the SGR to execute the eighth query.
 @param sgr Struct SGR that holds all the information.
 @param command String that holds the command given and has all the parameters required to execute the query. 
*/

static ERROR top_businesses_with_category_con(SGR sgr, char* command)
{
	VAR var = initVariable();

	char* buff = strdup(command);

	setVarName(var, strdup(strsep(&buff, "=")));

	if(containsElem(list, var) != -1) 
	{
		destroyVariable(var);

		return VARIABLE_NAME_ALREADY_IN_USE;
	}

	strsep(&buff, ",");

	char* int_char = strdup(strsep(&buff, ","));

	int top = atoi(int_char);

	free(int_char);

	char* category = strdup(strsep(&buff, ")"));

	setVarTable(var, top_businesses_with_category(sgr, top, category));

	free(category);

	addElem(list, var);

	return SUCCESS;
}

/**
 \brief Links the controller with the SGR to execute the nineth query.
 @param sgr Struct SGR that holds all the information.
 @param command String that holds the command given and has all the parameters required to execute the query. 
*/

static ERROR reviews_with_word_con(SGR sgr, char* command)
{
	VAR var = initVariable();

	char* buff = strdup(command);

	setVarName(var, strdup(strsep(&buff, "=")));

	if(containsElem(list, var) != -1) 
	{
		destroyVariable(var);

		return VARIABLE_NAME_ALREADY_IN_USE;
	}

	strsep(&buff, ",");

	char* word = strdup(strsep(&buff, ")"));

	setVarTable(var, reviews_with_word(sgr, word));

	show(reviews_with_word(sgr, word));

	addElem(list, var);

	free(word);

	return SUCCESS;
}

/**
 \brief Links the controller with the view to execute the show command.
 @param command String that holds the command given and has all the parameters required to execute the query. 
*/

static ERROR show_con(char* command)
{

	VAR var = initVariable();

	char* buff = strdup(command);

	strsep(&buff, "(");

	setVarName(var, strdup(strsep(&buff, ")")));

	if(containsElem(list, var) == -1) 
	{

		destroyVariable(var);

		return VARIABLE_NOT_DEFINED;
	}

	show(getTableFromList(list, var));

	destroyVariable(var);

	return SUCCESS;
}

/**
 \brief Links the controller with the cvs to execute the toCVS command.
 @param command String that holds the command given and has all the parameters required to execute the query. 
*/

static ERROR toCSV_con(char* command)
{
	ERROR e;

	VAR var = initVariable();

	char* buff = strdup(command);

	strsep(&buff, "(");

	setVarName(var, strdup(strsep(&buff, ",")));

	if(containsElem(list, var) == -1) 
	{
		destroyVariable(var);

		return VARIABLE_NOT_DEFINED;
	}

	char aux[1] = {34};

	strsep(&buff, aux);

	char* delim = strdup(strsep(&buff, aux));

	if(delim[0] == ',')
	{
		strsep(&buff, ",");
	}

	strsep(&buff, ",");

	char* filepath = strdup(strsep(&buff, ")"));

	e = toCSV(getTableFromList(list, var), delim, filepath);

	destroyVariable(var);

	free(filepath);

	return e;
}

/**
 \brief Links the controller with the cvs to execute the fromCVS command.
 @param command String that holds the command given and has all the parameters required to execute the query. 
*/

static ERROR fromCSV_con(char* command)
{
	VAR var = initVariable();

	char* buff = strdup(command);

	strsep(&buff, "=");

	setVarName(var, strdup(strsep(&buff, ",")));

	if(containsElem(list, var) != -1) 
	{
		destroyVariable(var);

		return VARIABLE_NAME_ALREADY_IN_USE;
	}

	char* filepath = strdup(strsep(&buff, ","));

	char aux[1] = {34};

	strsep(&buff, aux);

	char* delim = strdup(strsep(&buff, aux));

	setVarTable(var, fromCSV(filepath, delim));

	addElem(list, var);

	free(filepath);

	return SUCCESS;
}

/**
 \brief Links the controller with the filter to execute the filter command.
 @param command String that holds the command given and has all the parameters required to execute the query. 
*/

static ERROR filter_con(char* command)
{
	VAR var = initVariable();

	int original;

	char* buff = strdup(command);

	setVarName(var, strdup(strsep(&buff, "=")));

	if(containsElem(list, var) != -1) 
	{
		destroyVariable(var);

		return VARIABLE_NAME_ALREADY_IN_USE;
	}

	strsep(&buff, "(");

	VAR aux = initVariable();

	setVarName(aux, strdup(strsep(&buff, ",")));

	if((original = containsElem(list, aux)) == -1)
	{
		destroyVariable(var);
		destroyVariable(aux);

		return VARIABLE_NOT_DEFINED;
	}

	destroyVariable(aux);

	VAR copy = getVariable(list, original);

	char* colunm_name = strdup(strsep(&buff, ","));

	int col = atoi(colunm_name);

	free(colunm_name);

	char* value = strdup(strsep(&buff, ","));

	char* op = strdup(strsep(&buff, ")"));

	TABLE t = filter(col, value, op, copy);

	if(t == NULL) 
	{
		destroyVariable(var);

		free(copy);

		destroyTable(t);

		free(value);

		free(op);

		return FILTER_ERROR;
	}

	setVarTable(var, t);

	addElem(list, var);

	free(copy);

	free(value);

	free(op);

	return SUCCESS;
}

/**
 \brief Links the controller with the proj to execute the proj command.
 @param command String that holds the command given and has all the parameters required to execute the query. 
*/

static ERROR proj_con(char* command)
{
	VAR var = initVariable();

	int original;

	char* buff = strdup(command);

	setVarName(var, strdup(strsep(&buff, "=")));

	if(containsElem(list, var) != -1) 
	{
		destroyVariable(var);

		return VARIABLE_NAME_ALREADY_IN_USE;
	}

	strsep(&buff, "(");

	VAR aux = initVariable();

	setVarName(aux, strdup(strsep(&buff, ",")));

	if((original = containsElem(list, aux)) == -1)
	{
		destroyVariable(var);
		destroyVariable(aux);

		return VARIABLE_NOT_DEFINED;
	}

	destroyVariable(aux);

	VAR copy = getVariable(list, original);

	int cols = contains(buff, ',');

	int cols_num[cols+1];

	for(int i = 0; i < cols; i++)
	{
		char* colunm_name = strdup(strsep(&buff, ","));

		int col = atoi(colunm_name);

		free(colunm_name);

		cols_num[i] = col;
	}

	char* colunm = strdup(strsep(&buff, ")"));

	int col = atoi(colunm);

	free(colunm);

	cols_num[cols] = col;

	TABLE t = proj(copy, cols_num, cols+1);

	if(t == NULL) 
	{
		destroyVariable(var);

		free(copy);

		destroyTable(t);

		return PROJ_ERROR;
	}

	setVarTable(var, t);

	addElem(list, var);

	free(copy);

	return SUCCESS;
}

/**
 \brief Links the controller with the x to execute the (x) command.
 @param command String that holds the command given and has all the parameters required to execute the query. 
*/

static ERROR x_com(char* command)
{
	VAR var = initVariable();

	int original;

	char* buff = strdup(command);

	setVarName(var, strdup(strsep(&buff, "=")));

	if(containsElem(list, var) != -1) 
	{
		destroyVariable(var);

		return VARIABLE_NAME_ALREADY_IN_USE;
	}

	strsep(&buff, "(");

	VAR aux = initVariable();

	setVarName(aux, strdup(strsep(&buff, ",")));

	if((original = containsElem(list, aux)) == -1)
	{
		destroyVariable(var);
		destroyVariable(aux);

		return VARIABLE_NOT_DEFINED;
	}

	destroyVariable(aux);

	VAR copy = getVariable(list, original);

	strsep(&buff, "[");

	char* first_pos = strdup(strsep(&buff, "]"));

	int first = atoi(first_pos);

	free(first_pos);

	strsep(&buff, "[");

	char* second_pos = strdup(strsep(&buff, "]"));

	int second = atoi(second_pos);

	free(second_pos);

	TABLE t = x(copy, first, second);

	if(t == NULL) 
	{
		destroyVariable(var);

		free(copy);

		destroyTable(t);

		return PROJ_ERROR;
	}

	setVarTable(var, t);

	addElem(list, var);

	free(copy);

	return SUCCESS;
}

/**
 \brief Links the controller with the SGR to execute the quit command and destroy the SGR struct.
 @param sgr Struct SGR that holds all the information.
*/

static ERROR quit_con(SGR data)
{
	free_sgr(data);

	return SUCCESS;
}

/**
 \brief Manages the input from the console and manipulates it to be "executable".
*/

ERROR runController()
{
	bool quit = false;
	int howManyComms = 0;
	int com;

	char loading[24] = "A carregar ficheiros...";
	char loaded[21] = "Ficheiros carregados.";

	int mode;

	initVariableList();

	system("clear");

	initShow();

	scanf("%d", &mode); 

	if(mode != 1 && mode != 2) return UNDEFINED_MODE;

	SGR sgr = init_sgr();

	if(!sgr) return LACK_OF_MEMORY;

	if(mode == 1)
	{
		showFilePath();

		char users[100]; 
		char businesses[100]; 
		char reviews[100];

		while(scanf("%s %s %s\n", users, businesses, reviews) != 3)
		{
			system("clear");
			showMessage("There was a problem reading your input. Please try again.");
		}

		showMessage(loading);

		sgr = load_sgr(users, businesses, reviews);

		if(!sgr) return READING_ERROR;

		showMessage(loaded);
	}
	else
	{
		showMessage(loading);

		sgr = load_sgr(STD_USERS_PATH, STD_BUSINESSES_PATH, STD_REVIEWS_PATH);

		if(!sgr) return LACK_OF_MEMORY;

		showMessage(loaded);
	}

	while(!quit)
	{
		char* commands = malloc( sizeof(char) * 10000);

		while(fgets(commands, 10000, stdin) == NULL)
		{
			system("clear");
			showMessage("There was a problem reading your input. Please try again.");
		}
	
		howManyComms = contains(commands, ';');

		for(int j = 0; j < howManyComms && !quit; j++)
		{
			char* command = strdup(clean(sep_val(commands)));

			command = strdup(strsep(&command,")"));

			ERROR e = validate_command(command, &com);

			if(e == SUCCESS)
			{
				switch(com+1)
				{
					case 1:
						e = businesses_started_by_letter_con(sgr, command);
						break;

					case 2:
						e = business_info_con(sgr, command);
						break;

					case 3:
						e = businesses_reviewed_con(sgr, command);
						break;

					case 4:
						e = businesses_with_stars_and_city_con(sgr, command);
						break;

					case 5:
						e = top_businesses_by_city_con(sgr, command);
						break;

					case 6:
						e = international_users_con(sgr, command);
						break;

					case 7:
						e = top_businesses_with_category_con(sgr, command);
						break;

					case 8:
						e = reviews_with_word_con(sgr, command);
						break;

					case 9:
						e = show_con(command);
						break;

					case 10:
						e = toCSV_con(command);
						break;

					case 11:
						e = fromCSV_con(command);
						break;

					case 12:
						e = filter_con(command);
						break;

					case 13:
						e = proj_con(command);
						break;

					case 14:
						e = x_com(command);
						break;

					case 15:
						show(createHelpTable());
						break;

					case 16:
						e = quit_con(sgr);
						quit = true;
						break;

					default:
						showMessage("Não foi possível identificar o seu comando. Use o comando help para verificar os comandos disponíveis.");
						break;
				}
			}

			if( e != SUCCESS)
			{
				showMessage(error_msg(e));
			}
		}
	}
	return SUCCESS;
}