#pragma once
#include <stdio.h>

#include "defines.h"

/***
 * extended FILE structure containing... 
 * 1.FILE* pFile: pointer to a FILE object
 * 2.char* nFile: name of the file in char string
 */
typedef struct {
    FILE* pFile;
    char* nFile;
} FILEx;

/****** function prototypes ******/
// void file_open(FILE** pFile, const char* nFile, const char* mode);
// void file_close(FILE* pFile, const char* nFile);

FILEx* fileX_init(const char* name, const char* mode);
int fileX_kill(FILEx* file);

// int file_read(const char* nFile, FILE* pFile, const char* format, ...);
// int file_write(const char* nFile, FILE* pFile, const char* content, ...);

int fileX_read(int argc, FILEx* fileX, const char* format, ...);
int fileX_write(FILEx* fileX, const char* content, ...);