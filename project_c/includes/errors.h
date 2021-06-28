#ifndef ERRORS_H
#define ERRORS_H

typedef enum error{
    SUCCESS = 0,
    LACK_OF_MEMORY = 1,
    READING_ERROR = 2,
    FILE_STREAM_FAILED = 3,
    UNDEFINED_MODE = 4,

    INVALID_VAR_NAME = 5,
    INVALID_COMMAND = 6,
    INVALID_PARAMATER = 7,

    VARIABLE_NAME_ALREADY_IN_USE = 8,
    VARIABLE_NOT_DEFINED = 9,

    INVALID_DELIM = 10,
    FILTER_ERROR = 11,
    PROJ_ERROR = 12,
} ERROR;

char * error_msg(const int num);

#endif
