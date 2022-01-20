#include <math.h>

#include "file_handler.h"
#include "rational_fractions.h"

enum { DNE=0, EXISTS }; // for readability

typedef struct {
    int num, denom;
} Fraction;

static int expression_read(FILE* input, Fraction* oprd1, Fraction* oprd2, char* oprt) {
    int read_eof = file_read("inputs/input00.txt",input, "%d \\ %d %c %d \\ %d", &oprd1->num, &oprd1->denom, oprt, &oprd2->num, &oprd2->denom);
    return read_eof;
}

void rational_fraction_handler(FILEx* input, FILEx* output) {
    Fraction operand1 = {0}, operand2 = {0};
    Fraction result = {0};
    char operator = '\n';
    int read_eof = 0;
    int write_success = 0;
    int line = 1;

    for(ever) {
        printf("Line #%d:\n", line);        
        read_eof = fileX_read(input, "%d \\ %d %c %d \\ %d", &operand1.num, &operand1.denom, &operator,
                                                             &operand2.num, &operand2.denom);
        // calculate
        printf("Calculating...\n");
        write_success = fileX_write(output, "%d\\%d%c%d\\%d=%d\\%d\n", operand1.num, operand1.denom, operator,
                                                                       operand2.num, operand2.denom, result.num, result.denom);
        if (read_eof) break;
    }
    printf("All computation finished.\n");
}