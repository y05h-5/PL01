#pragma once

// macros to avoid magic numbers
#define NUM_ARGS 4
#define NUM_OPERANDS 2

// macros to create enums/strings
#define X_ENUM(X)    X,
#define X_STRING(X) #X,

// macro table containing all error types
#define ERROR_TYPE_TABLE(X)        \
    X(NO_ERROR)     X(DATA_FORMAT) \
    X(ARG_TOO_MANY) X(ARG_TOO_FEW) \
    X(FILE_LOAD_FAILED) X(NUM_ERRORS)

// enum / string containing all error types
typedef enum {
    ERROR_TYPE_TABLE(X_ENUM)
} ErrorType;

extern const char* ErrorNames[NUM_ERRORS+1];

/****** function prototype ******/
void error_exit(const char* nFile, ErrorType type);