#pragma once
#include <stdlib.h>

#include "file_handler.h"

typedef struct {
    int num, denom;
} Fraction;

int rational_fraction_handler(FILEx* input, FILEx* output);