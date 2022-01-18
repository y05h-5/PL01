#include <math.h>
#include "max.h"

enum { DNE=0, EXISTS }; // for readability
// function to calculate the larger value of two floating point 
// numbers given as arguments
int8_t max(double arg1, double arg2, double tolerance, double *pResult) {
    if (fabs(arg1-arg2) <= fabs(tolerance)) return DNE;
    *pResult = (arg1>arg2)? arg1 : arg2;
    return EXISTS;
}