#pragma once
#include <stdio.h>
#include "header/defines.h"

/****** function prototypes ******/
void file_open(FILE** pFile, const char* nFile, const char* mode);

void file_read(const char* nFile, FILE* pFile, const char* format, ...);

void file_write(const char* nFile, FILE* pFile, const char* content, ...);