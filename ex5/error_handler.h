#pragma once

#include "defines.h"

/***
 * macro table containing all error types
 */
#define ERROR_TYPE_TABLE(X)                  \
    X(NO_ERROR)         X(MALLOC_FAILURE)    \
    X(ARG_TOO_MANY)     X(ARG_TOO_FEW)       \
    X(DATA_FORMAT)      X(DATA_TYPE)         \
    X(DENOM_ZERO)       X(DENOM_NEGATIVE)    \
    X(FILE_LOAD_FAILED) X(FILE_CLOSE_FAILED) \
    X(FILE_READ_FAILED) X(FILE_WRITE_FAILED) \
    X(NUM_ERRORS)

/***
 * enum & char string containing all error types
 */
typedef enum {
    ERROR_TYPE_TABLE(X_ENUM)
} ErrorType;

extern const char* ErrorNames[NUM_ERRORS+1];

/****** function prototype ******/

// exit message
void exit_msg(int8_t error);

/***
 * @param nFile: const char string containing the file name
 *               in which the error occured
 * @param type: ErrorType variable representing the invoked error type 
 */
void error_exit(const char* nFile, ErrorType type);