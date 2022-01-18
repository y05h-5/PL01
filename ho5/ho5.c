#include <float.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// macros to avoid magic numbers
#define NUM_ARGS 4
#define NUM_OPERANDS 2

// macros to create enums/strings
#define X_ENUM(X)    X,
#define X_STRING(X) #X,

// macro table containing all error types
#define ERROR_TYPE_TABLE(X)        \
    X(NO_ERROR)                    \
    X(DATA_FORMAT) X(DATA_TYPE)    \
    X(ARG_TOO_MANY) X(ARG_TOO_FEW) \
    X(FILE_LOAD_FAILED) X(NUM_ERRORS)

// enum / string containing all error types
typedef enum {
    ERROR_TYPE_TABLE(X_ENUM)
} ErrorType;
const char* ErrorNames[NUM_ERRORS+1] = { ERROR_TYPE_TABLE(X_STRING) };

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
    case DATA_TYPE: 
        /***
         *  DATA_TYPE error occurs when the input data is not in the 
         *  right data type = floating point value
         *  e.g.) data contains character literals
         */ 
        printf("          Invalid input data type.\n");
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

// function to open a file (exits the process if fails)
void file_open(FILE** pFile, const char* nFile, const char* mode) {
    *pFile = fopen(nFile, mode);
    if (*pFile == NULL) error_exit(nFile, FILE_LOAD_FAILED);
}

// function to read the file content
void file_read(const char* nFile, FILE* pFile, const char* format, ...) {
    va_list args;
    va_start(args, format);
    int checkScan = fscanf(pFile, format, va_arg(args, double*), va_arg(args, double*));
    va_end(args);

    if (checkScan != NUM_OPERANDS) error_exit(nFile, DATA_TYPE);

    int invisible_input = EOF;
    while((invisible_input=getc(pFile)) != EOF) {
        if (invisible_input != ' ' && invisible_input != '\n')
            error_exit(nFile, DATA_FORMAT);
    }
}

// function to write the result of computation to an output file
void file_write(const char* nFile, FILE* pFile, const char* content, ...) {
    va_list args;
    va_start(args, content);

    fprintf(pFile, content, va_arg(args,double), va_arg(args,double), va_arg(args,double));
    printf("\nOutput file \"%s\" has been created/updated.\n", nFile);
}

enum { DNE=0, EXISTS };
// function to calculate the larger value of two floating point 
// numbers given as arguments
int8_t max(double arg1, double arg2, double tolerance, double *pResult) {
    if (fabs(arg1-arg2) <= fabs(tolerance)) return DNE;
    *pResult = (arg1>arg2)? arg1 : arg2;
    return EXISTS;
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
        printf("\nTwo values (%.03le, %.03le) are equal\n", a,b);

    fclose(fout);

    printf("Program terminated with success.\n\n");
    return EXIT_SUCCESS;
}