#include <stdio.h>
#include <stdlib.h>

#define MINUTES_PER_HOUR  60
#define HOURS_PER_DAY     24
#define HOURS_PER_MONTH   (31*HOURS_PER_DAY)
#define VALID              1
#define INVALID            0

enum InputErrorType {
    NO_ERROR,
    NOT_COLON,
    DATA_TYPE, 
    RANGE_HOUR_D,
    RANGE_HOUR_J, 
    RANGE_MIN,
    TOO_MANY
};

enum HourType {
    DEPARTURE,
    JOURNEY
};

void err_msg(enum InputErrorType err_type) {
    printf("\nERROR: ");
    switch (err_type) {
    case DATA_TYPE:
        printf("Invalid input data type.\n");
        break;
    case NOT_COLON:
        printf("Colon (:) is needed between hour and minute.\n");
        printf("       Input example:  10:00\n");
        break;
    case RANGE_HOUR_D:
        printf("Departure hour needs to be between 0 and 23.\n");
        break;
    case RANGE_HOUR_J:
        printf("Journey hour needs to be between 0 and %d (= 1 month).\n", HOURS_PER_MONTH);
        break;
    case RANGE_MIN:
        printf("Input minute needs to be between 0 and 59.\n");
        break;    
    case TOO_MANY:
        printf("Given input is invalid (e.g. Too many inputs).\n");
        break;
    default:
        printf("Something is wrong with the code if you are seeing this\n\n");
        return;
    }
    printf("       Please check yout input.\n\n");
}

int check_input(int* hour, int* minute, enum HourType hour_type) {
    int retScan = 0; // return value for scanf()
    char colon, invisible_input; // colon for reading ':' in the input
                                 // invisible_input for checking too many inputs
    enum InputErrorType error = NO_ERROR; // tells which error message to display
    
    // check if scanf() returns the expected value (=3)
    retScan = scanf("%d%c%d",hour,&colon,minute);
    if (retScan != 3) 
        error = DATA_TYPE;
    
    // check for colon character
    else if (colon != ':')
        error = NOT_COLON;

    // check if the journey hour is positive
    else if (hour_type == JOURNEY && (*hour < 0 || *hour >= HOURS_PER_MONTH))
        error = RANGE_HOUR_J;
    
    // check if the departure hour is within 0 and 24
    else if (hour_type == DEPARTURE && (*hour < 0 || *hour >= HOURS_PER_DAY))
        error = RANGE_HOUR_D;
    
    // check if minute is within 0 and 60 (both journey and departure)
    else if (*minute < 0 || *minute >= MINUTES_PER_HOUR)
        error = RANGE_MIN;

    // check for too many inputs by reading stdin character by character
    invisible_input = getchar();
    while(!error && invisible_input!='\n') {
        // invokes error if there is something other than 
        // a whitespace and newline character after valid input
        if (invisible_input!=' ' && invisible_input!='\n') {
            error = TOO_MANY;
            break;
        }
        invisible_input = getchar();
    }

    if (error) {
        // print error and returns INVALID = 0
        // if there is error (= invalid input)
        err_msg(error);
        return INVALID;
    }
    return VALID; // returns VALID = 1 if no error is found
}

int main(void) {
    int hDepart  = 0, mDepart  = 0; // Departure time (hours and minutes)
    int hJourney = 0, mJourney = 0; // Journey time (hours and minutes)
    int valid_input = INVALID; // check the return value of scanf() function
                               // default value will terminate the program unless overwritten
    
    // input departure time
    printf("Enter departure time (hh:mm): ");
    valid_input = check_input(&hDepart, &mDepart, DEPARTURE);
    if(!valid_input) return EXIT_FAILURE; // exit if the input is invalid
    
    // input journey time
	printf("Enter journey   time (hh:mm): ");
	valid_input = check_input(&hJourney, &mJourney, JOURNEY); // hJourney can be greater than 24
    if(!valid_input) return EXIT_FAILURE; // exit if the input is invalid

    // compute arrival time
    int dArrival = 1, hArrival = 0, mArrival = 0; // Arrival time (days, hours and minutes)
    int dExtra   = 0, hExtra   = 0; // Additional days/hours
    mArrival =  (mDepart + mJourney) % MINUTES_PER_HOUR;
    hExtra   =  (mDepart + mJourney) / MINUTES_PER_HOUR; // does this ever exceed 1 though?
    hArrival =  (hDepart + hJourney + hExtra) % HOURS_PER_DAY;
    dExtra   =  (hDepart + hJourney + hExtra) / HOURS_PER_DAY;
    dArrival +=  dExtra;

    // print arrival time
    printf("\nArrival Time: day %d, %02d:%02d\n\n",dArrival,hArrival,mArrival);
    return EXIT_SUCCESS;
}