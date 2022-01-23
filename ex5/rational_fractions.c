#include <math.h>
#include <string.h>

#include "error_handler.h"
#include "file_handler.h"
#include "rational_fractions.h"

#define F_DEFAULT_IN  "%d \\ %d %c %d \\ %d"
#define F_DEFAULT_OUT "%d\\%d %c %d\\%d = "

enum { DNE=0, EXISTS }; // for readability

static int validate_fraction(const Fraction* oprd1, const Fraction* oprd2, char operator) {
    ErrorType error = NO_ERROR;

    if (oprd1->denom == 0 || oprd2->denom == 0)
        error = DENOM_ZERO;
    else if (oprd1->denom < 0 || oprd2->denom < 0)
        error = DENOM_NEGATIVE;
    else if (operator == '/' && oprd2->num == 0)
        error = ZERO_DIVISION;

    if (error) error_handler(NULL, error);

    return (error)? INVALID : VALID;
}

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
    int factor = (frac->num==0)? 0 : gcf(abs(frac->num), abs(frac->denom));
    if (factor == 0) return *frac;
    return (Fraction) {
        .num = frac->num/factor,
        .denom = frac->denom/factor
    };
}

static Fraction calculate_fraction(const Fraction* oprd1, const Fraction* oprd2, char operator) {
    Fraction result = {0};
    
    printf("Calculating...\n");
    switch (operator) {
    case '+':
        result = (Fraction) {
            .num = oprd1->num*oprd2->denom + oprd2->num*oprd1->denom,
            .denom = oprd1->denom * oprd2->denom
        };
        break;
    case '-':
        result = (Fraction) {
            .num = oprd1->num*oprd2->denom - oprd2->num*oprd1->denom,
            .denom = oprd1->denom * oprd2->denom
        };
        break;
    case '*':
        result = (Fraction) {
            .num = oprd1->num * oprd2->num,
            .denom = oprd1->denom * oprd2->denom
        };
        break;
    case '/':
        result = (Fraction) {
            .num = oprd1->num * oprd2->denom,
            .denom = oprd1->denom * oprd2->num
        };
        break;    
    default:
        error_handler(NULL, NUM_ERRORS);
        break;
    }

    return get_irreducible(&result);
}

static char* format_fraction(int whole_num, int remainder) {
    const int MAX_RESULT = 8; 
    char* format = malloc(sizeof(char) * (strlen(F_DEFAULT_OUT)+MAX_RESULT));
    strcpy(format, F_DEFAULT_OUT);

    if (whole_num!=0 || remainder==0) {
        // format = realloc(format, sizeof(char) * (strlen(format)+2));
        strcat(format, "%d ");
    }

    if (remainder!=0) {
        // format = realloc(format, sizeof(char) * (strlen(format)+5));
        strcat(format, "%d\\%d");        
    }
    return format;
}

static int write_fraction(FILEx* output, const Fraction* oprd1, char operator, const Fraction* oprd2, const Fraction* result) {
    int write_success = FAILURE;
    int whole_num = result->num / result->denom;
    int remainder = abs(result->num % result->denom);
    char* format = format_fraction(whole_num, remainder);

    int check_sum = whole_num + remainder;
    if (check_sum != whole_num && check_sum != remainder)
        write_success = fileX_write(output, format, oprd1->num, oprd1->denom, operator, 
                                                    oprd2->num, oprd2->denom, whole_num,
                                                    remainder,  result->denom);
    else if(check_sum == whole_num)
        write_success = fileX_write(output, format, oprd1->num, oprd1->denom, operator, 
                                                    oprd2->num, oprd2->denom, whole_num);
    else
        write_success = fileX_write(output, format, oprd1->num, oprd1->denom, operator, 
                                                    oprd2->num, oprd2->denom,
                                                    result->num,result->denom);

    free(format);
    
    if (write_success > 0) fprintf(output->pFile, "\n");

    return write_success;
}

int rational_fraction_handler(FILEx* input, FILEx* output) {
    Fraction operand1 = {0}, operand2 = {0}, result = {0};
    char operator = '\n';
    int read_eof = 0, valid_input = 0, write_success = 0;
    ErrorType error = NO_ERROR;
    int line = 1;

    for(ever) {
        printf("Line #%d:\n", line++);        
        read_eof = fileX_read(input, F_DEFAULT_IN, &operand1.num, &operand1.denom, 
                                                   &operator,
                                                   &operand2.num, &operand2.denom);
        if (read_eof < 0) break;

        valid_input = validate_fraction(&operand1, &operand2, operator);
        if (!valid_input) break;

        result = calculate_fraction(&operand1, &operand2, operator);

        write_success = write_fraction(output, &operand1, operator, &operand2, &result);

        if (read_eof || write_success < 0) break;
    }
    if (read_eof && write_success) printf("All computation finished.\n");

    return (read_eof < 0 || write_success < 0)? FAILURE : SUCCESS;
}