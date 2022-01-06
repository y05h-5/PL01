#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define VALID      1
#define INVALID    0
#define NUM_COORDS 2
// #define NUM_LINE        1


/* ### STRUCTS & ENUMS ### */
/***
 * struct for representing coordinates
*/
typedef struct {
    int x,y;
} Point;
// typedef struct {
//     Point coords[NUM_COORDS];
// } Line;

// some special macros
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
/* ### END OF STRUCTS & ENUMS ### */


/* ### INPUT & INPUT ERROR FUNCTIONS ### */
/***
 * displays an error message according to the error type
 * 
 * @param type : type of the error. used to determine which error message
 *               to display on console 
 */
void input_error_message(const InputErrorType type) {
    printf("\nERROR: %s\n", ErrorNames[type]);
    switch (type) {
    case DATA_TYPE: 
        printf("    Input contains invalid data type.\n");
    break;
    case TOO_MANY: 
        printf("    Too many inputs were given.\n");
        printf("    Expected number of inputs = %d\n", NUM_COORDS);
    break;
    default: 
        printf("If you are seeing this message, something is wrong with the code.\n");
        exit(EXIT_FAILURE);
    };
    printf("    Please check your input.\n");
}

/***
 * checks if the input coordinate was valid
 * 
 * @return type of the error (if no error, returns NO_ERROR(=0))
 */
InputErrorType validate_input(const Point crd) {
    char invisible_input = getchar();
    
    while (invisible_input!='\n') {
        if (invisible_input!=' ' && invisible_input!='\n')
            return TOO_MANY;
        invisible_input = getchar();
    }
    return NO_ERROR;
}

/***
 * gets the inputs and put them into coordinate positions
 * 
 * @return if the input was valid or not
*/
int8_t input_coords(Point* crd) {
    int retScan = 0;
    InputErrorType error = NO_ERROR;

    printf("Input coordinate points (x y)\n");
    for (int i = 0; i < NUM_COORDS; ++i) {
        printf("Input coordinate #%d (x y): ",i+1);
        retScan = scanf("%d %d", &crd[i].x, &crd[i].y);
        error = (retScan!=NUM_COORDS) ? DATA_TYPE : validate_input(crd[i]);
        if (error) {
            input_error_message(error);
            return INVALID;
        }
    }
    return VALID;
}
/* ### END OF INPUT FUNCTIONS ### */


/* ### COORDINATES FUNCTIONS ### */
/***
 * displays an error message according to the error type
 * 
 * @param type : type of the error. used to determine which error message
 *               to display on console 
 */
void coord_error_message(const CoordErrorType type) {
    printf("\nERROR: %s\n", ErrorNames[type]); // shows the error name
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

/***
 * checking if two coordinates can form a standard form equation
 * invokes error when...
 * 1. two points overlaps (coord1 == coord2)
 * 2. two points have same x position (creates an asymptote)
 * 3. two points hvae same y position (line will have no slope)
*/
int8_t validate_coords(const Point* crd) {
    CoordErrorType error = NO_ERROR; // tells if there's error or not

    printf("\nchecking coordinates...\n");
    for (int i = 0; i < NUM_COORDS-1; ++i) {
        for (int j = i+1; j < NUM_COORDS; ++j) {
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

/***
 * displaying all coordinates in @param crd
*/
void print_coord(const Point* crd) {
    printf("\n");
    for (int i = 0; i < NUM_COORDS; ++i)
        printf("coordinates #%d = (%d, %d)\n",i+1, crd[i].x, crd[i].y);
}
/* ### END OF COORDINATES FUNCTIONS ### */


/* ### CALCULATION FUNCTIONS ### */
void get_standardform(const Point* crd) {
    // assume there is only one line 
    // and a line has only two points
    /***
     * int x1,y1 : coordinates of the first point
     * int x2,y2 : coordinates of the second point
     * int dx,dy : represents delta x and delta y
     * 
     * float slope = slope of the line constructed by 2 points
     */
    int   x1 = crd[0].x, y1 = crd[0].y;
    int   x2 = crd[1].x, y2 = crd[1].y; 
    float dy = y2 - y1,  dx = x2 - x1;
    float slope = dy/dx;

    printf("\nfinding the standard form equation (Ax + By + C = 0)...\n");
    printf("slope of the line = %f\n", slope);
    for (int i = 0; i < NUM_COORDS; ++i) {
        // use both coordinates to make sure the answer is right
        printf("\nusing coordinate #%d\n",i+1); 

        /***
         * standard form equation: Ax + By + C = 0
         * float a : represents 'A', which is the coefficient of x
         * float b : represents 'B', which is the coefficient of x
         * float c : represents 'C', which is the constant in the equation
         * 
         * char operator1&2 : '+' or '-' characters in the equation. changes according to 
         *                    the signs of float variables b and c to make the result 
         *                    look better.
         */
        float a = 0.0f, b = 0.0f, c = 0.0f;
        char operator1 = '+', operator2 = '+';
        
        /***
         * calculating a,b and c by...
         *  1) y - y1 = slope(x - x1)
         *  2) y - y1 = slope*x - slope*x1
         *  3) y - slope*x -y1 + slope*x1 = 0
         * so result will look like...
         *     by - slope*x + (-y1 + slope*x1) = 0
         * where...
         *     a = -(slope*x)
         *     b = 1
         *     c = (slope*x1 - y1)
         */
        a = (-1) * slope;
        b = 1.0f;
        c = slope * crd[i].x - crd[i].y;
        printf("A = %f\n",a);
        printf("B = %f\n",b);
        printf("C = %f\n",c);

        operator1 = (b < 0)? '-' : '+';
        operator2 = (c < 0)? '-' : '+';
        b = fabs(b);
        c = fabs(c);

        printf("\nResult:\n"              \
               "%fx %c %fy %c %f = 0\n",\
               a,operator1,b,operator2,c);
    }
}
/* ### END OF CALCULATION FUNCTIONS ### */

int main(void) {
    /***
     * Point coordinates[] : array of coordinates
     *      @see Point
     * 
     * int8_t valid_input / valid_coords:
     *      variables to make sure that there is no error
     *      before proceeding to next steps.
     *      if they are INVALID (=0), program exits with failure
     */
    Point coordinates[NUM_COORDS] = {0};
    int8_t valid_input = INVALID, valid_coords = INVALID;

    // getting inputs and verifying them
    valid_input = input_coords(coordinates);
    if (!valid_input) return EXIT_FAILURE;
    print_coord(coordinates);
    
    // checking if coordinates can construct a
    // standard form equation of a line
    valid_coords = validate_coords(coordinates);
    if (!valid_coords) return EXIT_FAILURE;
    
    // calculating & displaying the equation
    get_standardform(coordinates);
    
    return 0;
}