#pragma once
#include <stdlib.h>

#include "header/file_handler.h"

typedef struct {
    int num, denom;
} Fraction;

int rational_fraction_handler(FILEx* input, FILEx* output);