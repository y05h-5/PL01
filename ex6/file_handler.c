#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "includes/error_handler.h"
#include "includes/file_handler.h"

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
    return (success)? file : NULL;
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


int fileX_read(int argc, FILEx* input, const char* format, ...) {
    if (input->pFile == NULL) {
        error_handler(input->nFile, FILE_LOAD_FAILED);
        return UNDEFINED;
    }

    printf("Reading input file \"%s\"\n", input->nFile);
    
    va_list args;
    va_start(args, format);
    int checkScan = vfscanf(input->pFile, format, args);
    va_end(args);

    if (checkScan==EOF) {
		error_handler(input->nFile, DATA_FORMAT);
		return UNDEFINED;
	}
	if (checkScan != argc) {
        error_handler(input->nFile, DATA_TYPE);
        return UNDEFINED;
    }

    ErrorType error = NO_ERROR;
    int invisible_input = getc(input->pFile);
    int eof = (invisible_input == EOF)? 1 : 0;
    while(!eof && invisible_input != '\n' /*&& invisible_input != EOF*/) {
        eof = (invisible_input == EOF)? 1 : 0;

        if (!eof && invisible_input != ' ' && invisible_input != '\n') {
            error = DATA_FORMAT;
        }
        invisible_input = (eof)? EOF : getc(input->pFile);
    }

    if (error) error_handler(input->nFile, DATA_FORMAT);

    return (error)? UNDEFINED : eof;
}

int fileX_write(FILEx* output, const char* content, ...) {
    if (output->pFile == NULL) error_handler(output->nFile, FILE_LOAD_FAILED);
    
    va_list args;
    va_start(args, content);
    int write_success = vfprintf(output->pFile, content, args); // -1 if there's encoding failure
    va_end(args);

    if (write_success < 0) error_handler(output->nFile, FILE_WRITE_FAILED);
    // else printf("Output file \"%s\" has been created/updated.\n", output->nFile);

    return write_success;
}
