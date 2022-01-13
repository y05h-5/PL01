#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#define VALID 1
#define INVALID 0
#define NUM_COEFFS 3
#define NUM_ROOT_MAX 2

#define X_ENUM(X)    X,
#define X_STRING(X) #X,
#define ERRORTYPE_TABLE(X) \
    X(NO_ERROR)        X(DATA_TYPE)  \
    X(TOO_MANY)        X(NUM_ERRORS)

typedef enum {
    ERRORTYPE_TABLE(X_ENUM)
} ErrorType;

const char* ErrorNames[NUM_ERRORS+1] = {ERRORTYPE_TABLE(X_STRING)};

#define EQUATION_TYPE_TABLE(X) \
    X(QUADRATIC)       X(LINEAR) \
    X(CONSTANT)        X(ZERO)   \
    X(NUM_EQ_TYPES)

typedef enum {
    EQUATION_TYPE_TABLE(X_ENUM)
} EquationType;

const char* EquationTypeNames[NUM_EQ_TYPES+1] = {EQUATION_TYPE_TABLE(X_STRING)};

typedef struct {
    double coef_x2, coef_x, constant;
} QuadraticCoefficients;

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

ErrorType input_validation(const QuadraticCoefficients input) {
    char invisible_input = getchar();

    while (invisible_input!='\n') {
        if (invisible_input!=' ' && invisible_input!='\n')
            return TOO_MANY;

        invisible_input = getchar();
    }

    return NO_ERROR;
}

int8_t get_coefficients(QuadraticCoefficients* coefs) {
    int retScanf = 0;
    ErrorType error = NO_ERROR;

    retScanf = scanf("%lf %lf %lf",&coefs->coef_x2,&coefs->coef_x,&coefs->constant);

    error = (retScanf!=NUM_COEFFS)? DATA_TYPE : input_validation(coefs);

    if(error) {
        input_error_message(error);
        return INVALID;
    }
    return VALID;
}

EquationType get_eq_type(const QuadraticCoefficients coefs) {
    EquationType type = QUADRATIC;
    if (coefs.coef_x2 == 0)  type = LINEAR;
    if (coefs.coef_x == 0 && type == LINEAR)
        type = CONSTANT;
    if (coefs.constant == 0 && type == CONSTANT)
        type = ZERO;

    printf("Equation Type = %s\n",EquationTypeNames[type]);

    return type;
}

void print_roots(int real, double* roots, int num_roots) {

}

// find roots of ax^2 + bx + c = 0
void solve_quadratic(const QuadraticCoefficients coefs, double* roots) {
    int num_roots = 0;
    
    // compute discriminant
    double operand = pow(coefs.coef_x2,2) - 4*coefs.coef_x*coefs.constant;
    int neg_operand = (operand > 0.0)? 0 : 1; // determine if the solution is real
    double d = sqrt(fabs(operand));
    // compute roots by usign discriminant
    double x1 = (-b+d) / (2*a);
    double x2 = (-b-d) / (2*a);
}

// find roots of bx + c = 0
void solve_linear(QuadraticCoefficients coefs, double* roots) {
}

// find roots of c = 0
void solve_constant(QuadraticCoefficients coefs, double* roots) {
}

void calculate_roots(const QuadraticCoefficients coefs, EquationType type) {
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
        solve_constant(coefs, roots);
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
}

int main() {
    QuadraticCoefficients coefficients = {0.0};
    int8_t valid_input = INVALID;
    EquationType type = QUADRATIC;

    printf("Roots of ax^2 + bx + c = 0, enter a, b and c: ");
    valid_input = get_coefficients(&a, &b, &c);
    if (!valid_input) exit(EXIT_FAILURE);

    type = get_eq_type(coefficients);
    calculate_roots(coefficients, type);

    return EXIT_SUCCESS;
}