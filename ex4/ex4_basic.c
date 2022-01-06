#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define VALID        1
#define INVALID      0
#define NUM_OPERANDS 2
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
    switch (type) {
    case DENOM_ZERO:break;
    case DENOM_NEGATIVE:break;
    case DATA_TYPE:break;
    case TOO_MANY:break;
    default:break;
    }
}
ErrorType input_validation(const Fraction input) {
    return NO_ERROR;
}

int8_t input_fractions(Fraction* fracs) {
    const int num_elements = 2;
    int retScanf = 0;
    ErrorType error = NO_ERROR;

    printf("Input numerators and denominators\n");

    for_each_operands {
        printf("fraction #%d (numerator denominator): ",i+1);
        retScanf = scanf("%d %d",&fracs[i].num,&fracs[i].denom);

        error = (retScanf!=num_elements)? DATA_TYPE \ 
                                        : input_validation(fracs[i]);
        if(error) {
            input_error_message(error);
            return INVALID;
        }
    }
    return VALID;
}

int gcd(int num1, int num2);
Fraction get_irreducible(const Fraction frac);
Fraction add_fraction(const Fraction* fracs);
void print_fraction(const Fraction frac) {
    printf("%d/%d\n",frac.num,frac.denom);
}
void print_operands(const Fraction* fracs) {
    printf("\n###### Operands ######\n");
    for_each_operands {
        printf("Operand #%d = ",i+1);
        print_fraction(fracs[i]);
    }
    printf("######################\n");
}

int main(void) {
    int8_t valid_input = INVALID;
    Fraction operands[NUM_OPERANDS] = {0};

    valid_input = input_fractions(operands);
    if (!valid_input) return EXIT_FAILURE;
    print_operands(operands);

    Fraction answer = add_fraction(operands);
    printf("Result: ");
    print_fraction(answer);

    printf("computation finished. terminating...\n\n");
    return EXIT_SUCCESS;
}