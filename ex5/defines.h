#pragma once

// macros to avoid magic numbers
#define NUM_ARGS 3 // number of command line arguments
#define NUM_ELEMENTS 5 
#define ever ;; // for "for(;;)" loop

// macros to create enums/strings
#define X_ENUM(X)    X,
#define X_STRING(X) #X,