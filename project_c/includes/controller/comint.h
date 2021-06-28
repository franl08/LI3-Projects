#ifndef COMINT_H
#define COMINT_H

int contains(char* s, char c);

char* clean(char* s);

ERROR validate_command(char* command, int* com_to_validate);

#endif