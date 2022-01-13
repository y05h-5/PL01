#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

// macros to avoid magic numbers
#define VALID        1
#define INVALID      0
#define NUM_COEFFS   3
#define NUM_ROOT_MAX 2
#define TORELANCE_F  1e-6

// macros for defining enums/names
#define X_ENUM(X)    X,
#define X_STRING(X) #X,

// macro containing all error types
#define ERRORTYPE_TABLE(X)       \
    X(NO_ERROR)     X(DATA_TYPE) \
    X(TOO_MANY)     X(NUM_ERRORS)

typedef enum {
    // error type enum, for readability
    ERRORTYPE_TABLE(X_ENUM)
} ErrorType;

// names of errors in string, used for printing them on display
const char* ErrorNames[NUM_ERRORS+1] = {ERRORTYPE_TABLE(X_STRING)};

// macro containing all equaton types
#define EQUATION_TYPE_TABLE(X) \
    X(QUADRATIC)    X(LINEAR)  \
    X(CONSTANT)     X(ZERO)    \
    X(NUM_EQ_TYPES)

typedef enum {
    // equation type enum, again for readability
    EQUATION_TYPE_TABLE(X_ENUM)
} EquationType;

// names of equation types in string
const char* EquationTypeNames[NUM_EQ_TYPES+1] = {EQUATION_TYPE_TABLE(X_STRING)};

// structure for containing all 3 coefficients in one place
typedef struct {
    double coef_x2, coef_x, constant;
} QuadraticCoefficients;

/******* function definitions *******/
// error messages for all types of errors
void input_error_message(const ErrorType type) {
    printf("\nERROR: %s\n", ErrorNames[type]);

    switch (type) {
    case DATA_TYPE:
        printf("       Input contains invalid data type.\n");
    break;
    case TOO_MANY:
        printf("       Too many inputs were given.\n");
        printf("       Expected number of inputs = %d\n",NUM_COEFFS);
    break;
    default:
        printf("If you are seeing this message, something is wrong with the code.\n");
        exit(EXIT_FAILURE);
    }
    printf("\n");
}

// validating inputs
ErrorType input_validation(/*const QuadraticCoefficients* input*/) {
    char invisible_input = getchar();

    while (invisible_input!='\n') {
        if (invisible_input!=' ' && invisible_input!='\n')
            return TOO_MANY;
        invisible_input = getchar();
    }

    return NO_ERROR;
}

// function to get user inputs and print error messages if there's any error
int8_t get_coefficients(QuadraticCoefficients* coefs) {
    int retScanf = 0;
    ErrorType error = NO_ERROR;

    retScanf = scanf("%lf %lf %lf",&coefs->coef_x2,&coefs->coef_x,&coefs->constant);
    
    error = (retScanf!=NUM_COEFFS)? DATA_TYPE : input_validation(/*coefs*/);
    if(error) {
        input_error_message(error);
        return INVALID;
    }
    return VALID;
}

// function for figuring out which type of equation was given
EquationType get_eq_type(const QuadraticCoefficients* coefs) {
    EquationType type = QUADRATIC;
    if (coefs->coef_x2 == 0) 
        type = LINEAR;
    if (coefs->coef_x == 0 && type == LINEAR)
        type = CONSTANT;
    if (coefs->constant == 0 && type == CONSTANT)
        type = ZERO;

    printf("\nEquation Type = %s\n",EquationTypeNames[type]);

    return type;
}

// print roots of the equation
void print_roots(int real, double* roots, int num_roots) {
    if (!real) printf("\nroots are imaginary\n");
    for (int i = 0; i < num_roots; ++i) {
        if(real) printf("root #%d = %lf\n", i+1, roots[i]);
        else     printf("root #%d = %lfi\n", i+1, roots[i]);
    }
}

// find roots of ax^2 + bx + c = 0
void solve_quadratic(const QuadraticCoefficients* coefs, double* roots) {
    int num_roots = 0;
    
    // compute discriminant
    double operand = pow(coefs->coef_x2,2) - 4*coefs->coef_x*coefs->constant;
    int real = (operand > 0.0)? 0 : 1; // determine if the solution is real
    double d = sqrt(fabs(operand));
    
    // compute roots by using the discriminant
    roots[0] = (-coefs->coef_x+d) / (2*coefs->coef_x2);
    roots[1] = (-coefs->coef_x-d) / (2*coefs->coef_x2);

    num_roots = (fabs(roots[0]-roots[1]) < TORELANCE_F)? 1 : 2; 

    print_roots(real, roots, num_roots);
}

// find roots of bx + c = 0
void solve_linear(const QuadraticCoefficients* coefs, double* roots) {
    roots[0] = -1.0f * coefs->coef_x / coefs->constant;
    
    int num_roots = 1, real = 1;
    print_roots(real, roots, num_roots);
}

// procedure to call different of solver procedues for different tyupes of equations 
void calculate_roots(const QuadraticCoefficients* coefs, EquationType type) {
    int num_roots = 0;
    double roots[NUM_ROOT_MAX] = {0.0};

    switch (type) {
    case QUADRATIC:
        // when ax^2 + bx + c = 0
        solve_quadratic(coefs, roots);
        break;
    case LINEAR:
        // when bx + c = 0
        solve_linear(coefs, roots);
        break;
    case CONSTANT:
        // when c = 0
        printf("There is no solution for the given equation.\n");
        break;
    case ZERO:
        // when 0 = 0
        printf("There are infinite solutions to the given equation.\n");
        break;
    default:
        printf("If you are seeing this message, something is wrong with the code.\n");
        exit(EXIT_FAILURE);        
        break;
    }
    printf("\n");
}

/******* end of functions ******/

int main() {
    QuadraticCoefficients coefficients = {0.0};
    int8_t valid_input = INVALID;
    EquationType type = QUADRATIC;

    printf("Roots of ax^2 + bx + c = 0, enter a, b and c: ");
    valid_input = get_coefficients(&coefficients);
    if (!valid_input) exit(EXIT_FAILURE);

    type = get_eq_type(&coefficients);
    calculate_roots(&coefficients, type);

    return EXIT_SUCCESS;
}