#include <string.h>
#include <stdlib.h>
#include "../../includes/model/user.h"
#include "../../includes/config.h"

/**
 \brief User struct
*/
struct user
{
	char*  user_id;
	char*  name;
};

/**
 \brief Checks if it is a valid user
 @param line Content to check if it is a review
*/
int validUser(char *line)
{
	int j, dotCommas = 0, idSize = 0, commas = 0;

	for (j = 0; line[j]; j++)
	{
		if(line[j] == ';') dotCommas++;

		if(!dotCommas) idSize++;

		if(dotCommas == USSEPS && line[j] == ',') commas++;
	}

	if(dotCommas != USSEPS || idSize != IDSIZE) return -1;

	return (commas + 1);
}

/**
 \brief Initializes a user
 @param line Content to check if it is a review
*/
User initUser(char *line)
{
	int frids = validUser(line), j;

	if (frids != -1)
	{
		User user = malloc(sizeof(struct user));

		user->user_id = strdup(strsep(&line, ";"));
		
		user->name = strdup(strsep(&line, ";"));

		return user;
	}
	return NULL;
	
}

/**
 \brief Gets the user id
 @param u User
*/
char* getUserId(User u)
{
	return strdup(u->user_id);
}

/**
 \brief Gets the user name
 @param u User
*/
char* getUserName(User u)
{
	return strdup(u->name);
}


/**
 \brief Clones a user
 @param u User
*/
User cloneUser(User u)
{
	int size;


	User newUser = (User) malloc(sizeof (struct user*));

	newUser->user_id = strdup(u->user_id);

	newUser->name = strdup(u->name);

	return newUser;
}

/**
 \brief Deletes a user
 @param us User
*/
void destroyUser(void* us)
{
	User u = (User) us;

	free(u->user_id);

	free(u->name);

	free(u);
}