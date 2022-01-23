#include <math.h>
#include <string.h>

#include "error_handler.h"
#include "file_handler.h"
#include "rational_fractions.h"

#define F_DEFAULT_IN  "%d \\ %d %c %d \\ %d"
#define F_DEFAULT_OUT "%d\\%d %c %d\\%d = "

enum { DNE=0, EXISTS }; // for readability

static int gcf(const unsigned int num1, const unsigned int num2) {
    int temp = 0;
    int divisor = (num1 < num2)? num1 : num2;
    int factor  = (num1 < num2)? num2 : num1;

    for(ever) {
        temp = factor % divisor;
        factor = divisor;
        divisor = temp;
        // printf("factor: %d\n",factor);
        if (divisor==0) return factor;
    }
}
static Fraction get_irreducible(const Fraction* frac) {
    int factor = gcf(abs(frac->num), abs(frac->denom));
    if (factor == 0) return *frac;

    return (Fraction) {
        .num = frac->num/factor,
        .denom = frac->denom/factor
    };
}
static Fraction add_fraction(const Fraction* oprd1, const Fraction* oprd2) {
    Fraction result = (Fraction) {
        .num = oprd1->num*oprd2->denom + oprd2->num*oprd1->denom,
        .denom = oprd1->denom * oprd2->denom
    };
    return get_irreducible(&result);
}
static Fraction sub_fraction(const Fraction* oprd1, const Fraction* oprd2) {
    Fraction result = (Fraction) {
        .num = oprd1->num*oprd2->denom - oprd2->num*oprd1->denom,
        .denom = oprd1->denom * oprd2->denom
    };
    return get_irreducible(&result);
}
static Fraction mul_fraction(const Fraction* oprd1, const Fraction* oprd2) {
    Fraction result = (Fraction) {
        .num = oprd1->num * oprd2->num,
        .denom = oprd1->denom * oprd2->denom
    };
    return get_irreducible(&result);
}
static Fraction div_fraction(const Fraction* oprd1, const Fraction* oprd2) {
    Fraction result = (Fraction) {
        .num = oprd1->num * oprd2->denom,
        .denom = oprd1->denom * oprd2->num
    };
    return get_irreducible(&result);
}

static Fraction calculate_fraction(const Fraction* oprd1, const Fraction* oprd2, char operator) {
    Fraction result = {0};
    
    printf("Calculating...\n");
    switch (operator) {
    case '+':
        result = add_fraction(oprd1, oprd2); 
        break;
    case '-':
        result = sub_fraction(oprd1, oprd2);
        break;
    case '*':
        result = mul_fraction(oprd1, oprd2);
        break;
    case '/':
        result = div_fraction(oprd1, oprd2);
        break;    
    default:
        error_handler(NULL, NUM_ERRORS);
        break;
    }

    return result;
}

static int write_fraction(const FILEx* output, const Fraction* oprd1, char operator, const Fraction* oprd2, const Fraction* result) {
    int write_success = FAILURE;
    int whole_num = result->num / result->denom;
    int remainder = abs(result->num % result->denom);
    char* format = (char*) malloc(sizeof(char) * strlen(F_DEFAULT_OUT));

    if (whole_num!=0) {
        format = (char*) realloc(format, sizeof(char) * (strlen(format)+2));
        strcat(format, "%d");
    }
    if (remainder!=0) {
        format = (char*) realloc(format, sizeof(char) * (strlen(format)+5));
        strcat(format, "%d\\%d");        
    }

    write_success = fileX_write(output, format, oprd1->num, oprd1->denom, 
                                                    operator, 
                                                    oprd2->num, oprd2->denom, 
                                                    result->num, result->denom);

    free(format);

    return write_success;
}

int rational_fraction_handler(FILEx* input, FILEx* output) {
    Fraction operand1 = {0}, operand2 = {0}, result = {0};
    char operator = '\n';
    int read_eof = 0, write_success = 0;
    int line = 1;

    for(ever) {
        printf("Line #%d:\n", line++);        
        read_eof = fileX_read(input, F_DEFAULT_IN, &operand1.num, &operand1.denom, 
                                                   &operator,
                                                   &operand2.num, &operand2.denom);

        result = calculate_fraction(&operand1, &operand2, operator);

        write_success = write_fraction(output, &operand1, operator, &operand2, &result);

        if (!write_success) error_handler(output->nFile, FILE_WRITE_FAILED);
        if (read_eof) break;
    }
    printf("All computation finished.\n");
    return write_success;
}