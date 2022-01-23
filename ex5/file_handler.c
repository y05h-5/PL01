#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error_handler.h"
#include "file_handler.h"

// function to open a file (exits the process if fails)
static int file_open(FILE** pFile, const char* nFile, const char* mode) {
    *pFile = fopen(nFile, mode);
    if (*pFile == NULL) {
        error_handler(nFile, FILE_LOAD_FAILED);
        return FAILURE;
    }
    return SUCCESS;
}

static void file_close(FILE* pFile, const char* nFile) {
    if (pFile == NULL) error_handler(nFile, FILE_CLOSE_FAILED);
    fclose(pFile);
}


// function to initialize a FILEx object
FILEx* fileX_init(const char* name, const char* mode) {
    FILEx* file = malloc(sizeof(FILE)+strlen(name)*sizeof(char));
    if (file==NULL) {
        error_handler(name, MALLOC_FAILURE);
        return NULL;
    }

    int success = file_open(&file->pFile, name, mode);

    if (success) {
        file->nFile = malloc(strlen(name)*sizeof(char));
        strcpy(file->nFile,name);
    }
    return file;
}

int fileX_kill(FILEx* file) {
    int exit_value = SUCCESS;
    if (file==NULL) {
        error_handler(file->nFile, FILE_CLOSE_FAILED);
        return FAILURE;
    }

    file_close(file->pFile, file->nFile);
    free(file->nFile);
    free(file);

    return SUCCESS;
}


// function to read the file content
int file_read(const char* nFile, FILE* pFile, const char* format, ...) {
    if (pFile == NULL) error_handler(nFile, FILE_READ_FAILED);

    va_list args;
    va_start(args, format);

    int checkScan = fscanf(pFile, format, va_arg(args, int*), va_arg(args, int*), va_arg(args, char*), va_arg(args, int*), va_arg(args, int*));
    va_end(args);

    int stop = 0;
    if (checkScan != NUM_ELEMENTS) error_handler(nFile, DATA_TYPE);
    
    int invisible_input = getc(pFile);
    if (invisible_input == EOF) stop = 1;
    while(invisible_input != '\n' && invisible_input != EOF) {
        if (invisible_input == EOF) {
            stop = 1;
            break;
        }
        else if (invisible_input != ' ' && invisible_input != '\n')
            error_handler(nFile, DATA_FORMAT);
        invisible_input = getc(pFile);
    }
    return stop;
}

// function to write the result of computation to an output file
int file_write(const char* nFile, FILE* pFile, const char* content, ...) {
    va_list args;
    va_start(args, content);

    fprintf(pFile, content, va_arg(args, int*), va_arg(args, int*), va_arg(args, char*), va_arg(args, int*), va_arg(args, int*), va_arg(args, int*), va_arg(args, int*));
    printf("\nOutput file \"%s\" has been created/updated.\n", nFile);
    return 0;
}




ErrorType input_validation(const Fraction input) {
    char invisible_input = getchar();

    while (invisible_input!='\n') {
        if (invisible_input=='.')
            return DATA_TYPE;
        if (invisible_input!=' ' && invisible_input!='\n')
            return TOO_MANY;

        invisible_input = getchar();
    }

    if (input.denom == 0) return DENOM_ZERO;
    if (input.denom < 0)  return DENOM_NEGATIVE;

    return NO_ERROR;
}


int fileX_read(FILEx* input, const char* format, ...) {
    if (input->pFile == NULL) error_handler(input->nFile, FILE_READ_FAILED);

    printf("Reading input file \"%s\"\n", input->nFile);
    
    va_list args;
    va_start(args, format);
    int checkScan = vfscanf(input->pFile, format, args);
    va_end(args);

    if (checkScan != NUM_ELEMENTS) error_handler(input->nFile, DATA_TYPE);
    
    int invisible_input = getc(input->pFile);
    int eof = (invisible_input == EOF)? 1 : 0;
    while(!eof && invisible_input != '\n' /*&& invisible_input != EOF*/) {
        if (invisible_input == EOF)
            eof = 1;
        else if (invisible_input != ' ' && invisible_input != '\n') {
            error_handler(input->nFile, DATA_FORMAT);
        }
        invisible_input = getc(input->pFile);
    }
    return eof;
}

int fileX_write(FILEx* output, const char* content, ...) {
    if (output->pFile == NULL) error_handler(output->nFile, FILE_WRITE_FAILED);
    
    va_list args;
    va_start(args, content);
    int write_success = vfprintf(output->pFile, content, args); // -1 if there's encoding failure
    va_end(args);

    printf("Output file \"%s\" has been created/updated.\n", output->nFile);
    return write_success;
}
