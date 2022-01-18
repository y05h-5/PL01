#include <stdarg.h>
#include <stdio.h>

#include "file_operation.h"

const char* ErrorNames[NUM_ERRORS+1] = { ERROR_TYPE_TABLE(X_STRING) };

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

    if (checkScan != NUM_OPERANDS) error_exit(nFile, DATA_FORMAT);
    
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
