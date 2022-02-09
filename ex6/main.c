#include <stdio.h>
#include <stdlib.h>

#include "includes/defines.h"
#include "includes/error_handler.h"
#include "includes/file_handler.h"
#include "includes/flight.h"

#define DEF_ARRIVAL_FILE "inputs/arrival.txt"
#define DEF_DEPARTURE_FILE "inputs/departure.txt"
#define DEF_OUTPUT_FILE "outputs/found.txt"

void safe_exit(FILEx* arrival, FILEx* departure, int ret) {
	if (arrival!=NULL) fileX_kill(arrival);
	if (departure!=NULL) fileX_kill(departure);
	exit(ret);
}

int main(int argc, char* argv[]) {
	if (argc > NUM_ARGS) error_handler(NULL, ARG_TOO_MANY);

	Flight *arrival = NULL, *departure = NULL;
	char *from = NULL, *to = NULL;

	FILEx* f_arrival = fileX_init((argc > 1)? argv[1] : DEF_ARRIVAL_FILE, "rt");
	if (f_arrival==NULL) return EXIT_FAILURE;
	FILEx* f_departure = fileX_init((argc > 2)? argv[2] : DEF_DEPARTURE_FILE, "rt");
	if (f_departure==NULL) 
		safe_exit(f_arrival, f_departure, EXIT_FAILURE);

	int arrlen = 0, dprlen = 0;
	int checkArrival = getFlightList(f_arrival, &arrival, &arrlen);
	int checkDeparture = (checkArrival)? getFlightList(f_departure, &departure, &dprlen) : FAILURE;

	int checkSuccess = (checkArrival && checkDeparture);
	if (checkSuccess) {
		FILEx* f_out = fileX_init((argc > 3)? argv[3] : DEF_OUTPUT_FILE, "wt");
		if (f_out==NULL) 
			safe_exit(f_arrival, f_departure, EXIT_FAILURE);

		checkSuccess = getUserFlight(&from, &to);
		if (checkSuccess) 
			searchFlight(f_out, arrival, departure, arrlen, dprlen, from, to);
	}

	if (checkArrival) 	byebyeFlights(arrival, arrlen);
	if (checkDeparture) byebyeFlights(departure, dprlen);

	exit_message(checkSuccess);
	return (checkSuccess)? EXIT_SUCCESS : EXIT_FAILURE;
}	