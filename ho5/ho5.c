#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "file_operation.h"
#include "max.h"

// function to print error message and exits the code with EXIT_FAILURE
void error_exit(const char* nFile, ErrorType type) {
    printf("\nError ID: %s\n", ErrorNames[type]);
    switch (type) {
    case DATA_FORMAT: 
        /***
         *  DATA_FORMAT error occurs when the input data is not in the 
         *  form of "<floating point value> <floating point value>"
         *  e.g.) data contains more than two values
         */ 
        printf("          Invalid input data format.\n");
        printf("          Expected format: <floating-point-number #1> <floating-point-number #2>"\
                          " (white space in between)\n");
        printf("          Check the content of \"%s\"\n", nFile);
        break;
    case ARG_TOO_MANY:
        /***
         *  ARG_TOO_MANY error occurs when there are too many arguments 
         *  given to the program from the command line
         */ 
        printf("          Too many arguments were given.\n");
        printf("          Usage of the command: <command> <input-file-name> <output-file-name> <tolerance-value>\n");
        printf("          Expected number of arguments: %d\n", NUM_ARGS);
        break;
    case ARG_TOO_FEW:
        /***
         *  ARG_TOO_FEW error occurs when there are too few arguments
         *  given to the program from the command line
         */ 
        printf("          Not enough arguments were given.\n");
        printf("          Usage of the command: <command> <input-file-name> <output-file-name> <tolerance-value>\n");
        printf("          Expected number of arguments: %d\n", NUM_ARGS);
        break;
    case FILE_LOAD_FAILED:
        /***
         *  FILE_LOAD_FAILED error occurs when the program fails to open
         *  a file (when fopen() fails)
         */ 
        printf("          File \"%s\" is unavailable\n", nFile);
        break;
    default: 
        printf("if you are seeing this, something is wrong with the code.\n");
        break;
    }

    // exit message
    printf("\nProcess terminating with failure.\n\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
    FILE *fin = NULL, *fout = NULL;
    double a = 0.0, b = 0.0;
    double tolerance = 0.0;
    double result = 0.0;

    if (argc != NUM_ARGS) 
        error_exit(NULL, (argc<NUM_ARGS)? ARG_TOO_FEW:ARG_TOO_MANY); 
    
    file_open(&fin, argv[1], "rt");
    file_read(argv[1], fin, "%lf %lf", &a, &b);
    fclose(fin);

    file_open(&fout, argv[2], "wt");
    tolerance = atof(argv[3]);

    if (max(a, b, tolerance, &result))
        file_write(argv[2], fout, "max(%le, %le) = %le\n", a, b, result);
    else
        file_write(argv[2], fout, "Two values (%.03le, %.03le) are equal\n",a,b);

    fclose(fout);

    printf("Program terminated with success.\n\n");
    return EXIT_SUCCESS;
}