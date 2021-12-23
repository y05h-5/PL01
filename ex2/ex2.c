#include <stdio.h>
#include <stdlib.h>

#define VALID 1
#define INVALID 0
#define NUM_COORDS 2

typedef struct {
    float x,y;
} Point;

enum ErrorType {
    NO_ERROR=0,
    DATA_TYPE,
    TOO_MANY
    ZERO_SLOPE,
    ASYMPTOTE,
};
typedef enum ErrorType InputErrorType;
typedef enum ErrorType CoordErrorType;

InputErrorType validate_input(const Point crd) {
    return NO_ERROR;
}

CoordErrorType validate_coords(const Point* crd) {
    return NO_ERROR;
}

void input_error_message(const InputErrorType type) {
    printf("\nERROR: ")
    switch (type) {
    case DATA_TYPE: break;
    case TOO_MANY: break;
    default: 
        printf("If you are seeing this message, something is wrong with the code.\n");
        exit(EXIT_FAILURE);
    // return;
    }
    printf("Please check your input.\n")
}

void coord_error_message(const CoordErrorType type) {
    printf("\nERROR: ")
    switch (type) {
    case ZERO_SLOPE: break;
    case ASYMPTOTE: break;
    default: 
        printf("If you are seeing this message, something is wrong with the code.\n");
        exit(EXIT_FAILURE);
    // return;
    }
    printf("Please check your input.\n")
}

int8_t input_coords(Point* crd) {
    int retScan = 0;
    InputErrorType error = NO_ERROR;
    for (int i = 0; (i < NUM_COORDS; ++i) {
        retScan = scanf("%f %f", crd[i].x, crd[i].y);
        error = (retScan!=NUM_COORDS) ? DATA_TYPE : validate_input(crd[i]);
        if (error) {
            input_error_message(error);
            return INVALID;
        }
    }
    return VALID;
}

void get_standardform(const Point* crd) {
    printf("\nfinding the standard form equation...\n");
}

int main(void) {
    Point coordinates[NUM_COORDS] = {0};
    int8_t valid_input = INVALID, valid_coords = INVALID;

    valid_input = input_coords(coordinates);
    if (!valid_input) return EXIT_FAILURE;
    
    valid_coords = validate_coords(coordinates);
    if (!valid_coords) return EXIT_FAILURE;
    
    printf("\ncoordinates construct a valid line.\n");
    get_standardform(coordinates);
    
    return 0;
}