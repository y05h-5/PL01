#pragma once
#include <stdint.h>

#include "defines.h"

/***
 * macro table containing all error types
 */
#define ERROR_TYPE_TABLE(X)                  \
    X(NO_ERROR)         X(MALLOC_FAILURE)    \
    X(DATA_FORMAT)      X(DATA_TYPE)         \
    X(FILE_LOAD_FAILED) X(FILE_CLOSE_FAILED) \
    X(FILE_READ_FAILED) X(FILE_WRITE_FAILED) \
    X(ARG_TOO_MANY) 	X(NUM_ERRORS)

/***
 * enum & char string containing all error types
 */
typedef enum {
    ERROR_TYPE_TABLE(X_ENUM)
} ErrorType;

extern const char* ErrorNames[NUM_ERRORS+1];

/****** function prototype ******/

/***
 * message to display at the end of the execution of 
 * the program.
 * 
 * @param error: shows if the program is exiting with or
 *               without an error
 */
void exit_message(int error);

/***
 * function to display various error messages when an error occurs.
 * 
 * @param nFile: const char string containing the file name
 *               in which the error occured
 * @param type: ErrorType variable representing the invoked error type 
 */
void error_handler(const char* nFile, ErrorType type);