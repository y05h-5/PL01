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

enum ErrorType {
    NO_ERROR=0,
    DATA_TYPE,
    TOO_MANY,
    ZERO_SLOPE,
    ASYMPTOTE,
    OVERLAP
};
typedef enum ErrorType InputErrorType;
typedef enum ErrorType CoordErrorType;

void print_coord(const Point* crd) {
    printf("\n");
    for (int i = 0; i < COORDS_PER_LINE; ++i)
        printf("coordinates #%d = (%d, %d)\n",i+1, crd[i].x, crd[i].y);
}

void input_error_message(const InputErrorType type) {
    printf("\nERROR: ");
    switch (type) {
    case DATA_TYPE: 
        printf("Input contains invalid data type.\n");
    break;
    case TOO_MANY: 
        printf("Too many inputs were given.\n");
        printf("       Expected number of inputs = %d\n", COORDS_PER_LINE);
    break;
    default: 
        printf("If you are seeing this message, something is wrong with the code.\n");
        exit(EXIT_FAILURE);
    };
    printf("       Please check your input.\n");
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
        retScan = scanf("%d %d", crd[i].x, crd[i].y);
        error = (retScan!=COORDS_PER_LINE) ? DATA_TYPE : validate_input(crd[i]);
        if (error) {
            input_error_message(error);
            return INVALID;
        }
    }
    return VALID;
}

void coord_error_message(const CoordErrorType type) {
    printf("\nERROR: ");
    switch (type) {
    case ZERO_SLOPE: 
        printf("The line has no slope (parallel to the x-axis)\n");
    break;
    case ASYMPTOTE:
        printf("The line is an asymptote (parallel to the y-axis)\n");
    break;
    case OVERLAP:
        printf("Two points overlaps.\n");
    break;
    default: 
        printf("If you are seeing this message, something is wrong with the code.\n");
    exit(EXIT_FAILURE);
    };
    printf("\nInvalid coordinates.\n");
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
    slope[0] = dy/dx;

    printf("\nfinding the standard form equation (Ax + By + C = 0)...\n");

    for (int i = 0; i < COORDS_PER_LINE; ++i) {
        printf("using coordinate #%d\n",i+1);
        float a = slope, b = 1.0f;
        float mx = a * crd[i].x;
        float c  = mx - crd[i].y;

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