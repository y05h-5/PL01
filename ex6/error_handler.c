#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "includes/defines.h"
#include "includes/error_handler.h"

const char* ErrorNames[NUM_ERRORS+1] = { ERROR_TYPE_TABLE(X_STRING) };

void exit_message(int success) {
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

	/***
     *  ARG_TOO_XXX error occurs when there are too many/few 
     *  arguments given to the program from the command line
     *  exits the program instead of returning to the caller
     *  function
     */ 
    case ARG_TOO_MANY:
        printf("          Too many arguments were given.\n");
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
        printf("          Expected format: <flight id>(<=6 characters) <airport name> <time>(number:number)\n");
        printf("          Check the content of \"%s\"\n", nFile);
        break;

    /***
     *  FILE_XXX_FAILED errors occur when the program fails to open
     *  a file (when fopen() fails)
     */
	case FILE_CLOSE_FAILED: //intentional fallthrough
 	case FILE_READ_FAILED:  //intentional fallthrough
	case FILE_WRITE_FAILED: //intentional fallthrough
    case FILE_LOAD_FAILED:  //intentional fallthrough
        printf("          File \"%s\" is unavailable\n", nFile);
        break;
    default: 
        printf("if you are seeing this, something is wrong with the code.\n");
        exit(EXIT_FAILURE);
    }
}