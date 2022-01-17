#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define VALID      1
#define INVALID    0
#define NUM_COORDS 3
#define THRESHOLD  1e-6 // 
typedef struct {
    float x, y;
} Coordinate;

int vertex_input(Coordinate* crd) {
    int num_input = 0;
    char invisible_input = EOF;
    printf("input a pair of coordinates (x then y, space in between)\n");
    for (int i = 0; i < NUM_COORDS; ++i) {
        printf("coordinate #%d: ", i+1);
        num_input = scanf("%f %f", &crd[i].x, &crd[i].y); // how can I check for overflow??
        if (num_input!=2) {
            printf("\nERROR: Invalid data type in coordinate %d. Please check your input.\n", i+1);
            return INVALID;
        } else if (crd[i].x == INFINITY || crd[i].y == INFINITY) {
            printf("\nERROR: Input causes overflow. Please check your input.\n");
            return INVALID;
        }
        do {
            invisible_input = getchar();
            if (invisible_input != '\n' && invisible_input != ' ') {
                printf("\nERROR: Too many inputs in coordinate %d. Please check your input.\n", i+1);
                return INVALID;            
            }
        } while(invisible_input != '\n');
    }
    return VALID;
}

void print_coord(const Coordinate* crd) {
    printf("\n");
    for (int i = 0; i < NUM_COORDS; ++i)
        printf("coordinates #%d = (%f, %f)\n",i+1, crd[i].x, crd[i].y);
}

void get_slopes(const Coordinate* crd, Coordinate* storage) {
    int cmb = 0;
    for (int i = 0; i < NUM_COORDS-1; ++i) {
        for (int j = i+1; j < NUM_COORDS; ++j) {
            storage[cmb++] = (Coordinate) {
                .x = crd[i].x - crd[j].x,
                .y = crd[i].y - crd[j].y
            };
        }
    }
}

void print_slopes(const Coordinate* slp) {
    printf("\n");
    for (int i=0; i < NUM_COORDS; ++i){ 
        if (slp[i].x == 0.0f) {
            printf("slope #%d = %f / %f\n",i+1,slp[i].y,slp[i].x);
        } else {
            printf("slope #%d = %f\n",i+1,slp[i].y/slp[i].x);
        }
    }
}

int compare_slopes(const Coordinate* slp) {
    float ref_slope = slp[0].y / slp[0].x;
    float cur_slope = 0.0;
    print_slopes(slp);
    for (int i = 1; i < NUM_COORDS; ++i) {
        if (slp[0].x == 0.0f) {
            if (slp[0].x != slp[i].x) {return 0;}
        } else {
            if (slp[i].x == 0) {return 0;} 
            cur_slope = slp[i].y / slp[i].x;
            if (fabs(ref_slope-cur_slope) > THRESHOLD) {return 0;}
        }
    }
    return 1;
}

int check_crd_overlap(const Coordinate* crd) {
    int ol = 0;
    for (int i = 0; i < NUM_COORDS-1; ++i) {
        for (int j = i+1; j < NUM_COORDS; ++j)
            ol += (crd[i].x == crd[j].x && crd[i].y == crd[j].y)? 1 : 0;
        if (ol) break;
    }
    return ol;
}

int check_crd_aligned(const Coordinate* crd) {
    enum {NOT_ALIGNED = 0, ALIGNED};
    Coordinate slopes[NUM_COORDS] = {0};
    get_slopes(crd, slopes); // won't work for quadrilaterals
    int aligned = compare_slopes(slopes); // won't work for quadrilaterals
    return (aligned)? ALIGNED : NOT_ALIGNED;
}

void triangle_errormsg(const int ol) {
    switch(ol) {
        case 0:
            printf("\nThere is no overlap, but three verteces are collinear.\n");
            break;
        case 1:
            printf("\nTwo vertices are overlapped.\n");
            break;
        case 2:
            printf("\nThree vertices are overlapped.\n");
            break;
        default: 
            printf("\nUndefined error. Not sure what's wrong.\n");
            break;
    }
    printf("Triangle can't be constructed.\n");
}

int triangle_eval(const Coordinate* crd) {
    int overlap = check_crd_overlap(crd);
    int aligned = (overlap)? 0 : check_crd_aligned(crd);
    if (overlap || aligned) {
        triangle_errormsg(overlap);
        return INVALID;
    }
    return VALID;
}

void get_sides(const Coordinate* crd, float* sides) {
    int cmb = 0;
    for (int i = 0; i < NUM_COORDS-1; ++i) {
        for (int j = i+1; j < NUM_COORDS; ++j) {
            sides[cmb++] = sqrt(pow(crd[i].x-crd[j].x,2) + pow(crd[i].y-crd[j].y,2));
            printf("side #%d = %f\n", cmb, sides[cmb-1]);
        }
    }
}

// void tri_area(const Coordinate* crd) {
float tri_area(const Coordinate* crd) {
    float sides[NUM_COORDS] = {0.0f};
    float s = 0.0f, area = 0.0f;

    printf("\n### Calculation Steps ###\n\n");
    get_sides(crd,sides);
    for (int i = 0; i < 3; ++i)
        s += sides[i]/2.0;
    printf("\ns = (side1 + side2 + side3) / 2\n");
    printf("  = %f\n",s);

    printf("\nUsing Heron's Formula...\n");
    area = sqrt(s*(s-sides[0])*(s-sides[1])*(s-sides[2])); // Heron's formula
    printf("\narea = sqrt( s * (s - side1) * (s - side2) * (s - side3) )\n");
    // printf("     = %f\n", area);
    return area;
}

int main() {
    Coordinate coordinates[NUM_COORDS] = {0};
    
    int valid_in = vertex_input(coordinates);
    if (!valid_in) return EXIT_FAILURE;
    print_coord(coordinates);

    int valid_tri = triangle_eval(coordinates);
    if (!valid_tri) return EXIT_FAILURE;
    printf("\nvalid triangle. calculating the area...\n");
    printf("     = %f\n", tri_area(coordinates));
    printf("\n### DONE! ###\n\n");
    return EXIT_SUCCESS;
}