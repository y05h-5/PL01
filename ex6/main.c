#include <stdio.h>
#include <stdlib.h>

#include "error_handler.h"
#include "file_handler.h"
#include "flight.h"

#define ARRIVAL_FILE_NAME "inputs/arrival.txt"
#define DEPARTURE_FILE_NAME "inputs/departure.txt"
#define OUTPUT_FILE_NAME "outputs/found.txt"

void safe_exit(FILEx* arrival, FILEx* departure, int ret) {
	if (arrival!=NULL) fileX_kill(arrival);
	if (departure!=NULL) fileX_kill(departure);
	exit(ret);
}

int main(int argc, char* argv[]) {
	Flight *arrival = NULL, *departure = NULL;
	char *from = NULL, *to = NULL;

	FILEx* f_arrival = fileX_init(ARRIVAL_FILE_NAME, "rt");
	if (f_arrival==NULL) return EXIT_FAILURE;
	FILEx* f_departure = fileX_init(DEPARTURE_FILE_NAME, "rt");
	if (f_departure==NULL) safe_exit(f_arrival, f_departure, EXIT_FAILURE);

	int arrlen = 0, dprlen = 0;
	int checkArrival = getFlightList(f_arrival, &arrival, &arrlen);
	int checkDeparture = (checkArrival)? getFlightList(f_departure, &departure, &dprlen)
									   : FAILURE;

	int checkSuccess = (checkArrival && checkDeparture);
	if (checkSuccess) {
		FILEx* f_out = fileX_init(OUTPUT_FILE_NAME, "wt");
		if (f_out==NULL) safe_exit(f_arrival, f_departure, EXIT_FAILURE);
		checkSuccess = getUserFlight(&from, &to);
		if (checkSuccess) searchFlight(f_out, arrival, departure, arrlen, dprlen, from, to);
	}

	return (checkSuccess)? EXIT_SUCCESS : EXIT_FAILURE;
}	