#include "../../includes/errors.h"

/**
 \brief Returns a error message
 @param num Error type
*/
char * error_msg(const int num){
    switch(num){
        case 0:
            return "Success";
        case 1: 
            return "Leak of memory";
        case 2:
            return "Reading error";
        case 3:
            return "File stream failed";
        case 4:
            return "Undefined mode";
        case 5:
            return "Invalid variable name";
        case 6:
            return "Invalid command";
        case 7:
            return "Invalid paramater";
        case 8:
            return "Variable name already in use";
        case 9:
            return "Variable not defined";
        case 10:
            return "Invalid delimiter";
        case 11:
            return "Filter error";
        default:
            return "Unkown error";
    }
}