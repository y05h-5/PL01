#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define VALID        1
#define INVALID      0
#define NUM_OPERANDS 2
#define NUM_ELEMENTS 2
#define for_each_operands for(int i = 0; i < NUM_OPERANDS; ++i)

#define X_ENUM(X)    X,
#define X_STRING(X) #X,
#define ERRORTYPE_TABLE(X) \
    X(NO_ERROR)        X(DENOM_ZERO) \
    X(DENOM_NEGATIVE)  X(DATA_TYPE)  \
    X(TOO_MANY)        X(NUM_ERRORS)

typedef enum {
    ERRORTYPE_TABLE(X_ENUM)
} ErrorType;

const char* ErrorNames[NUM_ERRORS+1] = {ERRORTYPE_TABLE(X_STRING)};

typedef struct {
    int num, denom;
} Fraction;

void input_error_message(const ErrorType type) {
    printf("\nERROR: %s\n", ErrorNames[type]);

    switch (type) {
    case DENOM_ZERO:
        printf("       Division by 0 is not allowed.\n");
    break;
    case DENOM_NEGATIVE:
        printf("       Denominator needs to be a positive integer value.\n");
    break;
    case DATA_TYPE:
        printf("       Input contains invalid data type.\n");
    break;
    case TOO_MANY:
        printf("       Too many inputs were given.\n");
        printf("       Expected number of inputs = %d\n",NUM_ELEMENTS);
    break;
    default:
        printf("If you are seeing this message, something is wrong with the code.\n");
        exit(EXIT_FAILURE);
    }
    printf("\n");
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

int8_t input_fractions(Fraction* fracs) {
    int retScanf = 0;
    ErrorType error = NO_ERROR;

    printf("Input numerators and denominators\n");

    for_each_operands {
        printf("fraction #%d (numerator denominator): ",i+1);
        retScanf = scanf("%d %d",&fracs[i].num,&fracs[i].denom);

        error = (retScanf!=NUM_ELEMENTS)? DATA_TYPE \
                                        : input_validation(fracs[i]);
        if(error) {
            input_error_message(error);
            return INVALID;
        }
    }
    return VALID;
}

int gcd(const unsigned int num1, const unsigned int num2) {
    int temp = 0;
    int divisor = (num1 < num2)? num1 : num2;
    int factor = (num1 > num2)? num1 : num2;

    for(;;) {
        temp = factor % divisor;
        factor = divisor;
        divisor = temp;
        // printf("factor: %d\n",factor);
        if (divisor==0) return factor;
    }
}
Fraction get_irreducible(const Fraction frac) {
    int factor = gcd(abs(frac.num),abs(frac.denom));
    if (factor == 0) return frac;

    return (Fraction) {
        .num = frac.num/factor,
        .denom = frac.denom/factor
    };
}
Fraction add_fraction(const Fraction* fracs) {
    Fraction result = fracs[0];

    for(int i = 1; i < NUM_OPERANDS; ++i) {
        result.num = result.num*fracs[i].denom + fracs[i].num*result.denom;
        result.denom *= fracs[i].denom; 
    }
    
    return get_irreducible(result);
}

void print_fraction(const Fraction frac) {
    printf("%d/%d\n",frac.num,frac.denom);
}
void print_mixed(const Fraction frac) {
    int whole_num = frac.num / frac.denom;
    int remainder = abs(frac.num % frac.denom);

    printf("%d ", whole_num);
    if (remainder!=0)
        print_fraction((Fraction){.num=remainder, .denom=frac.denom});
    else 
        printf("\n");
}
void print_operands(const Fraction* fracs) {
    printf("\n###### Operands ######\n");
    for_each_operands {
        printf("  Operand #%d = ",i+1);
        print_fraction(fracs[i]);
    }
    printf("######################\n\n");
}

int main(void) {
    int8_t valid_input = INVALID;
    Fraction operands[NUM_OPERANDS] = {0};

    valid_input = input_fractions(operands);
    if (!valid_input) return EXIT_FAILURE;
    print_operands(operands);

    Fraction answer = add_fraction(operands);
    printf("Result: ");
    // print_fraction(answer);
    print_mixed(answer);

    printf("computation finished. terminating...\n\n");
    return EXIT_SUCCESS;
}