#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define VALID           1
#define INVALID         0
#define COORDS_PER_LINE 2
#define NUM_LINE        1

typedef struct {
    int x,y;
} Point;
typedef struct {
    Point coords[COORDS_PER_LINE];
} Line;

#define X_ENUM(X) X,
#define X_STRING(X) #X,

#define ERROR_TYPE_TABLE(X)    \
    X(NO_ERROR)   X(DATA_TYPE) \
    X(TOO_MANY)   X(ZERO_SLOPE)\
    X(ASYMPTOTE)  X(OVERLAP)   \
    X(NUM_ERRORS)

enum ErrorType {
    ERROR_TYPE_TABLE(X_ENUM)
};
typedef enum ErrorType InputErrorType;
typedef enum ErrorType CoordErrorType;
const char* ErrorNames[NUM_ERRORS+1] = { ERROR_TYPE_TABLE(X_STRING) };

void print_coord(const Point* crd) {
    printf("\n");
    for (int i = 0; i < COORDS_PER_LINE; ++i)
        printf("coordinates #%d = (%d, %d)\n",i+1, crd[i].x, crd[i].y);
}

void input_error_message(const InputErrorType type) {
    printf("\nERROR: %s\n", ErrorNames[type]);
    switch (type) {
    case DATA_TYPE: 
        printf("    Input contains invalid data type.\n");
    break;
    case TOO_MANY: 
        printf("    Too many inputs were given.\n");
        printf("    Expected number of inputs = %d\n", COORDS_PER_LINE);
    break;
    default: 
        printf("If you are seeing this message, something is wrong with the code.\n");
        exit(EXIT_FAILURE);
    };
    printf("    Please check your input.\n");
}

InputErrorType validate_input(const Point crd) {
    char invisible_input = getchar();
    
    while (invisible_input!='\n') {
        if (invisible_input!=' ' && invisible_input!='\n')
            return TOO_MANY;
        invisible_input = getchar();
    }
    return NO_ERROR;
}

int8_t input_coords(Point* crd) {
    int retScan = 0;
    InputErrorType error = NO_ERROR;

    printf("Input coordinate points (x y)\n");
    for (int i = 0; i < COORDS_PER_LINE; ++i) {
        printf("Input coordinate #%d (x y): ",i+1);
        retScan = scanf("%d %d", &crd[i].x, &crd[i].y);
        error = (retScan!=COORDS_PER_LINE) ? DATA_TYPE : validate_input(crd[i]);
        if (error) {
            input_error_message(error);
            return INVALID;
        }
    }
    return VALID;
}

void coord_error_message(const CoordErrorType type) {
    printf("\nERROR: %s\n", ErrorNames[type]);
    switch (type) {
    case ZERO_SLOPE: 
        printf("    The line has no slope (parallel to the x-axis)\n");
    break;
    case ASYMPTOTE:
        printf("    The line is an asymptote (parallel to the y-axis)\n");
    break;
    case OVERLAP:
        printf("    Two points overlaps.\n");
    break;
    default: 
        printf("If you are seeing this message, something is wrong with the code.\n");
    exit(EXIT_FAILURE);
    };
    printf("    Invalid coordinates.\n");
}

int8_t validate_coords(const Point* crd) {
    CoordErrorType error = NO_ERROR;

    printf("\nchecking coordinates...\n");
    for (int i = 0; i < COORDS_PER_LINE-1; ++i) {
        for (int j = i+1; j < COORDS_PER_LINE; ++j) {
            if (crd[i].x == crd[j].x && crd[i].y == crd[j].y)
                error = OVERLAP;
            else if (crd[i].y == crd[j].y) 
                error = ZERO_SLOPE;
            else if (crd[i].x == crd[j].x) 
                error = ASYMPTOTE;
            
            if (error) {
                coord_error_message(error);
                return INVALID;
            }
        }
    }
    printf("coordinates construct a valid line.\n");
    return VALID;
}

void get_standardform(const Point* crd) {
    int dy = crd[1].y - crd[0].y;  // include this in the for loop when dealing with more than 1 lines???
    int dx = crd[1].x - crd[0].x;
    float slopes[NUM_LINE] = {0.0f};
    slopes[0] = dy/dx;

    printf("\nfinding the standard form equation (Ax + By + C = 0)...\n");

    for (int i = 0; i < COORDS_PER_LINE; ++i) {
        printf("using coordinate #%d\n",i+1);
        float a  = slopes[0], b = 1.0f;
              a *= crd[i].x;
        float c  = a - crd[i].y;
        printf("Result:\n" \
               "%fx + %fy + %f = 0\n", a,b,c);
    }
}

int main(void) {
    Point coordinates[COORDS_PER_LINE] = {0};
    Line lines[NUM_LINE] = {0};
    int8_t valid_input = INVALID, valid_coords = INVALID;

    valid_input = input_coords(coordinates);
    if (!valid_input) return EXIT_FAILURE;
    print_coord(coordinates);
    
    valid_coords = validate_coords(coordinates);
    if (!valid_coords) return EXIT_FAILURE;
    
    get_standardform(coordinates);
    
    return 0;
}