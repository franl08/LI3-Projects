#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "../../includes/errors.h"
#include "../../includes/controller/comint.h"

/**
 \brief possible commands
*/
static char* func[] = {
	"businesses_started_by_letter",
	"business_info",
	"businesses_reviewed",
	"businesses_with_stars_and_city",
	"top_businesses_by_city",
	"international_users",
	"top_businesses_with_category",
	"reviews_with_word",
	"show",
	"toCSV",
	"fromCSV",
	"filter",
	"proj",
	"x",
	"help",
	"quit"
};

/**
 \brief Number of arguments for each command
*/
int num_args[] = {2,2,2,3,2,1,3,2,1,3,2,4,2,2,0,0};

/**
 \brief Counts how many times a char appears in a String
 @param s String
 @param c Char to count
*/
int contains(char* s, char c)
{
	int res = 0;

	for(int i = 0; i < (int) strlen(s); i++)
	{
		if(s[i] == c) res++;
	}

	return res;
}

/**
 \brief Clean spaces of a string
 @param s String
*/
char* clean(char* s)
{ 
	char* cleanS = malloc(sizeof(char) * (strlen(s) - contains(s, ' ')));
	int j = 0;

	for (int i = 0; i < (int) strlen(s); i++)
	{
		if(s[i] != ' ') 
		{
			cleanS[j] = s[i];
			j++;
		}  
	}

	return cleanS;
}

/**
 \brief Checks if a variable name is correct
 @param var_name Name of the Variable
 */
static bool validate_var_name(char* var_name)
{
	bool res = true;

	for(int i = 0; var_name[i] != '\0' && res; i++)
	{
		if(isalnum(var_name[i]) == 0) res = false;
	}

	return res;
}

/**
 \brief Checks if a command as a correct name
 @param com_name Name of the command
*/
static int validate_com_name(char* com_name)
{
	int res = -1;

	for(int i = 0; i < 16 && res == -1; i++) if(strcmp(func[i], com_name) == 0) res = i;

	return res;
}

/**
 \brief Checks if businesses_started_by_letter command is correct
 @param buff Buffer to check
 @param i Address of int to saves command number
*/
static ERROR validate_com_0(char* buff, int* i)
{
	if(contains(buff, 39) != 2 || contains(buff, ',') != (num_args[0] - 1)) return INVALID_COMMAND;
	
	char* sgr = strdup(strsep(&buff, ","));

	if(strcmp("sgr", sgr) != 0) 
	{
		free(sgr);

		return INVALID_PARAMATER;
	}

	if(buff == NULL || strcmp("\0", buff) == 0) 
	{
		free(sgr);

		return INVALID_COMMAND;
	}

	strsep(&buff, "'");

	if(isalpha(buff[0]) != 0)
	{
		strsep(&buff, "'");

		if(strcmp("\0", buff) == 0)
		{
			*i = 0;

			free(sgr);

			return SUCCESS;
		}
	}
	else
	{
		free(sgr);
		return INVALID_PARAMATER;
	}

	free(sgr);

	return INVALID_COMMAND;
}

/**
 \brief Checks if business_info command is correct
 @param buff Buffer to check
 @param i Address of int to saves command number
*/
static ERROR validate_com_1(char* buff, int* i)
{
	if(contains(buff, ',') != (num_args[1] - 1))
	{
		return INVALID_COMMAND;
	}

	char* sgr = strdup(strsep(&buff, ","));

	if(strcmp("sgr", sgr) != 0) 
	{
		free(sgr);

		return INVALID_PARAMATER;
	}

	if(buff == NULL || strcmp("\0", buff) == 0)
	{
		free(sgr);

		return INVALID_COMMAND;
	}

	strsep(&buff, ")");

	if(buff == NULL) 
	{
		*i = 1;

		free(sgr);

		return SUCCESS;
	}

	free(sgr);
	
	return INVALID_COMMAND;
}

/**
 \brief Checks if businesses_reviewed command is correct
 @param buff Buffer to check
 @param i Address of int to saves command number
*/
static ERROR validate_com_2(char* buff, int* i)
{
	if(contains(buff, ',') != (num_args[2] - 1))
	{
		return INVALID_COMMAND;
	}

	char* sgr = strdup(strsep(&buff, ","));

	if(strcmp("sgr", sgr) != 0) 
	{
		free(sgr);

		return INVALID_PARAMATER;
	}

	if(buff == NULL || strcmp("\0", buff) == 0) 
	{
		free(sgr);
		return INVALID_COMMAND;
	}

	strsep(&buff, ")");

	if(buff == NULL) 
	{
		*i = 2;

		free(sgr);

		return SUCCESS;
	}

	free(sgr);
	
	return INVALID_COMMAND;
}

/**
 \brief Checks if businesses_with_stars_and_city command is correct
 @param buff Buffer to check
 @param i Address of int to saves command number
*/
static ERROR validate_com_3(char* buff, int* i)
{
	if(contains(buff, ',') != (num_args[3] - 1))
	{
		return INVALID_COMMAND;
	}

	char* sgr = strdup(strsep(&buff, ","));

	if(strcmp("sgr", sgr) != 0) 
	{
		free(sgr);

		return INVALID_PARAMATER;
	}

	if(buff == NULL || strcmp("\0", buff) == 0) 
	{
		free(sgr);

		return INVALID_COMMAND;
	}

	char* float_arg = strdup(strsep(&buff, ","));

	if(!strtof(float_arg, NULL)) 
	{
		free(sgr);
		free(float_arg);

		return INVALID_PARAMATER;
	}

	strsep(&buff, ")");

	if(buff == NULL) 
	{
		*i = 3;

		free(sgr);
		free(float_arg);

		return SUCCESS;
	}

	free(sgr);
	free(float_arg);
	
	return INVALID_COMMAND;
}

/**
 \brief Checks if top_businesses_by_city command is correct
 @param buff Buffer to check
 @param i Address of int to saves command number
*/
static ERROR validate_com_4(char* buff, int* i)
{
	if(contains(buff, ',') != (num_args[4] - 1))
	{
		return INVALID_COMMAND;
	}

	char* sgr = strdup(strsep(&buff, ","));

	if(strcmp("sgr", sgr) != 0) 
	{
		free(sgr);

		return INVALID_PARAMATER;
	}

	if(buff == NULL || strcmp("\0", buff) == 0) 
	{
		free(sgr);

		return INVALID_COMMAND;
	}

	char* int_arg = strdup(strsep(&buff, ")"));

	if(!atoi(int_arg))
	{
		free(sgr);
		free(int_arg);

		return INVALID_PARAMATER;
	}

	if(buff == NULL) 
	{
		*i = 4;

		free(sgr);
		free(int_arg);

		return SUCCESS;
	}

	free(sgr);
	free(int_arg);
	
	return INVALID_COMMAND;
}

/**
 \brief Checks if international_users command is correct
 @param buff Buffer to check
 @param i Address of int to saves command number
*/
static ERROR validate_com_5(char* buff, int* i)
{
	if(contains(buff, ',') != (num_args[5] - 1))
	{
		return INVALID_COMMAND;
	}

	char* sgr = strdup(strsep(&buff, ")"));

	if(strcmp("sgr", sgr) != 0) 
	{
		free(sgr);

		return INVALID_PARAMATER;
	}

	if(buff == NULL) 
	{
		*i = 5;

		free(sgr);

		return SUCCESS;
	}

	free(sgr);
	
	return INVALID_COMMAND;
}

/**
 \brief Checks if top_businesses_with_category command is correct
 @param buff Buffer to check
 @param i Address of int to saves command number
*/
static ERROR validate_com_6(char* buff, int* i)
{
	if(contains(buff, ',') != (num_args[6] - 1))
	{
		return INVALID_COMMAND;
	}

	char* sgr = strdup(strsep(&buff, ","));

	if(strcmp("sgr", sgr) != 0) 
	{
		free(sgr);

		return INVALID_PARAMATER;
	}

	if(buff == NULL || strcmp("\0", buff) == 0) 
	{
		free(sgr);

		return INVALID_COMMAND;
	}

	char* int_arg = strdup(strsep(&buff, ","));

	if(!atoi(int_arg)) 
	{
		free(sgr);
		free(int_arg);

		return INVALID_PARAMATER;
	}

	strsep(&buff, ")");

	if(buff == NULL) 
	{
		*i = 6;

		free(sgr);
		free(int_arg);

		return SUCCESS;
	}

	free(sgr);
	free(int_arg);

	return INVALID_COMMAND;
}

/**
 \brief Checks if reviews_with_word command is correct
 @param buff Buffer to check
 @param i Address of int to saves command number
*/
static ERROR validate_com_7(char* buff, int* i)
{
	if(contains(buff, ',') != (num_args[7] - 1))
	{
		return INVALID_COMMAND;
	}

	char* sgr = strdup(strsep(&buff, ","));

	if(strcmp("sgr", sgr) != 0) 
	{
		free(sgr);

		return INVALID_PARAMATER;
	}

	strsep(&buff, ")");

	if(buff == NULL) 
	{
		*i = 7;

		free(sgr);

		return SUCCESS;
	}
	
	free(sgr);

	return INVALID_COMMAND;
}

/**
 \brief Checks if show command is correct
 @param buff Buffer to check
 @param i Address of int to saves command number
*/
static ERROR validate_com_8(char* buff, int* i)
{
	strsep(&buff, ")");

	if(buff == NULL) 
	{
		*i = 8;
		return SUCCESS;
	}
	
	return INVALID_COMMAND;
}

/**
 \brief Checks if toCSV command is correct
 @param buff Buffer to check
 @param i Address of int to saves command number
*/
static ERROR validate_com_9(char* buff, int* i)
{
	strsep(&buff, ")");

	if(buff == NULL) 
	{
		*i = 9;
		return SUCCESS;
	}
	
	return INVALID_COMMAND;
}

/**
 \brief Checks if fromCSV command is correct
 @param buff Buffer to check
 @param i Address of int to saves command number
*/
static ERROR validate_com_10(char* buff, int* i)
{
	*i = 10;
	return SUCCESS;
}

/**
 \brief Checks if filter command is correct
 @param buff Buffer to check
 @param i Address of int to saves command number
*/
static ERROR validate_com_11(char* buff, int* i)
{
	strsep(&buff, ")");

	if(buff == NULL) 
	{
		*i = 11;
		return SUCCESS;
	}
	
	return INVALID_COMMAND;
}

/**
 \brief Checks if proj command is correct
 @param buff Buffer to check
 @param i Address of int to saves command number
*/
static ERROR validate_com_12(char* buff, int* i)
{
	strsep(&buff, ")");

	if(buff == NULL)
	{
		*i = 12;
		return SUCCESS;
	}
	
	return INVALID_COMMAND;
}

/**
 \brief Checks if x command is correct
 @param buff Buffer to check
 @param i Address of int to saves command number
*/
static ERROR validate_com_13(char* buff, int* i)
{
	if(contains(buff, ']') != 2 || contains(buff, '[') != 1)
	{
		return INVALID_COMMAND;
	}

	char* int_arg_1 = strdup(strsep(&buff, "]"));

	if(!atoi(int_arg_1)) 
	{
		free(int_arg_1);

		return INVALID_PARAMATER;
	}

	strsep(&buff, "[");

	char* int_arg_2 = strdup(strsep(&buff, "]"));

	if(!atoi(int_arg_2)) 
	{
		free(int_arg_1);
		free(int_arg_2);

		return INVALID_PARAMATER;
	}

	if(buff == NULL) 
	{
		*i = 13;

		free(int_arg_1);
		free(int_arg_2);

		return SUCCESS;
	}

	free(int_arg_1);
	free(int_arg_2);

	return INVALID_COMMAND;
}

/**
 \brief Checks if help command is correct
 @param buff Buffer to check
 @param i Address of int to saves command number
*/
static ERROR validate_com_14(char* buff, int* i)
{
	*i = 14;
	return SUCCESS;
}

/**
 \brief Checks if quit command is correct
 @param buff Buffer to check
 @param i Address of int to saves command number
*/
static ERROR validate_com_15(char* buff, int* i)
{
	*i = 15;
	return SUCCESS;
}

/**
 \brief General function to validate commands
 @param buff Buffer to check
 @param com Number of the command
 @param i Address of int to saves command number
*/
static ERROR validate(char* buff, int com, int* i)
{
	switch(com)
	{
		case 0:
			return validate_com_0(buff, i);
			break;

		case 1:
			return validate_com_1(buff, i);
			break;

		case 2:
			return validate_com_2(buff, i);
			break;

		case 3:
			return validate_com_3(buff, i);
			break;

		case 4:
			return validate_com_4(buff, i);
			break;

		case 5:
			return validate_com_5(buff, i);
			break;

		case 6:
			return validate_com_6(buff, i);
			break;

		case 7:
			return validate_com_7(buff, i);
			break;

		case 8:
			return validate_com_8(buff, i);
			break;

		case 9:
			return validate_com_9(buff, i);
			break;

		case 10:
			return validate_com_10(buff, i);
			break;

		case 11:
			return validate_com_11(buff, i);
			break;

		case 12:
			return validate_com_12(buff, i);
			break;

		case 13:
			return validate_com_13(buff, i);
			break;

		case 14:
			return validate_com_14(buff, i);
			break;

		case 15:
			return validate_com_15(buff, i);
			break;

		default:
			return INVALID_COMMAND;
			break;
	}
}

ERROR validate_command(char* command, int* com_to_validate)
{
	ERROR e;

	char* buff = strdup(command);

	if(contains(buff, '[') > 0)
	{
		*com_to_validate = 13;
		return SUCCESS;
	}

	if(contains(buff, '=') == 1)
	{
		char* var_name = strdup(strsep(&buff, "="));

		if(!validate_var_name(var_name)) 
		{
			free(var_name);

			return INVALID_VAR_NAME;
		}

		if(buff != NULL)
		{
			char* com_name = strdup(strsep(&buff, "(["));

			int com = validate_com_name(com_name);

			if(com == -1 || buff == NULL) 
			{
				free(var_name);

				return INVALID_COMMAND;
			}

			if(com != 8 && com != 9 && com != 15) 
			{
				e = validate(buff, com, com_to_validate);

				free(var_name);
				free(com_name);

				return e; 
			}

			free(var_name);
			free(com_name);

			return INVALID_COMMAND;
		}

		free(var_name);

		return INVALID_COMMAND;
	}

	else if(contains(buff, '=') == 0)
	{
		char* com_name = strdup(strsep(&buff, "("));

		int com = validate_com_name(com_name);

		if(com == -1) 
		{
			free(com_name);

			return INVALID_COMMAND;
		}

		e = validate(buff, com, com_to_validate);

		free(com_name);
		return e;
	}

	return INVALID_COMMAND;
}

/*
int main(int argc, char static *argv[])
{
	char* command = malloc(sizeof (char) * 100);

	fgets(command, 100, stdin);

	int i = -1;

	if(validate_command(command, &i) == SUCCESS) printf("SUCCESS %d\n", i);

	else if(validate_command(command, &i) == INVALID_VAR_NAME) printf("INVALID_VAR_NAME %d\n", i);

	else if(validate_command(command, &i) == INVALID_COMMAND) printf("INVALID_COMMAND %d\n", i);

	else if(validate_command(command, &i) == INVALID_PARAMATER) printf("INVALID_PARAMATER %d\n", i);

	return 0;
}
*/