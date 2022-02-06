#pragma once

#define FAILURE    (0)
#define SUCCESS    (1)
#define UNDEFINED (-1) 
#define VALID   1
#define INVALID 0
#define ever ;; // for "for(;;)" loop
#define N_ELEMENTS_FLIGHT 4
#define MAX_ID_LEN 6
#define NUM_ARGS 4

// macros to create enums/strings
#define X_ENUM(X)    X,
#define X_STRING(X) #X,