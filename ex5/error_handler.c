#include <stdio.h>
#include <stdlib.h>

#include "header/defines.h"
#include "header/error_handler.h"

const char* ErrorNames[NUM_ERRORS+1] = { ERROR_TYPE_TABLE(X_STRING) };

void exit_message(int8_t success) {
    if (success) printf("\nProgram terminated with success.\n\n");
    else printf("\nProgram terminated with failure.\n\n");       
}

// function to print error message and exits the code with EXIT_FAILURE
void error_handler(const char* nFile, ErrorType type) {
    printf("\nError ID: %s\n", ErrorNames[type]);

    switch (type) {
    case MALLOC_FAILURE: 
        printf("       Memory Allocation failed.\n");
        break;
    case DENOM_NEGATIVE: 
        printf("       Denominator needs to be a positive integer value.\n");
        break;
    case DENOM_ZERO: // intentinal fall through
    case ZERO_DIVISION:
        printf("       Division by 0 is not allowed.\n");
        break;

    /***
     *  ARG_TOO_XXX error occurs when there are too many/few 
     *  arguments given to the program from the command line
     *  exits the program instead of returning to the caller
     *  function
     */ 
    case ARG_TOO_MANY:
        printf("          Too many arguments were given.\n");
        // intentioanl fall through
    case ARG_TOO_FEW:
        if (type != ARG_TOO_MANY) printf("          Not enough arguments were given.\n");
        printf("          Usage of the command: <command> <input-file-name> <output-file-name> <tolerance-value>\n");
        printf("          Expected number of arguments: %d\n", NUM_ARGS);
        exit(EXIT_FAILURE); 

    /***
     *  DATA_XXX error occurs when the input data is not in the 
     *  form of "<floating point value> <floating point value>"
     *  e.g.) wrong data type, data contains more than two values etc
     */
    case DATA_FORMAT: 
        printf("          Invalid input data format.\n");
        // intentional fall through
    case DATA_TYPE:
        if (type != DATA_FORMAT) printf("          Invalid input data type.\n");
        printf("          Expected format: <integer> \\ <integer> <character [+, -, * or /]> <integer> \\ <integer>\n");
        printf("          Check the content of \"%s\"\n", nFile);
        break;

    /***
     *  FILE_XXX_FAILED errors occur when the program fails to open
     *  a file (when fopen() fails)
     */ 
    case FILE_LOAD_FAILED:  // intentional fall through
    case FILE_CLOSE_FAILED: // intentional fall through
    case FILE_READ_FAILED:  // intentional fall through
    case FILE_WRITE_FAILED:
        printf("          File \"%s\" is unavailable\n", nFile);
        break;
    default: 
        printf("if you are seeing this, something is wrong with the code.\n");
        exit(EXIT_FAILURE);
    }
    
    // exit(EXIT_FAILURE);
}