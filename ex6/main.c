#include <stdio.h>
#include <stdlib.h>

#include "error_handler.h"
#include "file_handler.h"
#include "flight.h"

#define ARRIVAL_FILE_NAME "inputs/arrival.txt"
#define DEPARTURE_FILE_NAME "inputs/departure.txt"
#define OUTPUT_FILE_NAME "outputs/found.txt"

int main(int argc, char* argv[]) {
	Flight *arrival = {0}, *departure = {0};

	FILEx* f_arrival = fileX_init(ARRIVAL_FILE_NAME, "rt");
	if (f_arrival==NULL) return EXIT_FAILURE;
	FILEx* f_departure = fileX_init(DEPARTURE_FILE_NAME, "rt");
	if (f_departure==NULL) {
		fileX_kill(f_arrival);
		return EXIT_FAILURE;
	}

	int checkArrival = getFlight(f_arrival->pFile, arrival);
	int checkDeparture = (checkArrival)? getFlight(f_departure->pFile, departure)
					   	 			   : FAILURE;

	int checkSuccess = (checkArrival && checkDeparture);
	if (checkSuccess) {
		FILEx* f_out = fileX_init(OUTPUT_FILE_NAME, "wt");
		if (f_out==NULL)
	}

	return (checkSuccess)? EXIT_SUCCESS : EXIT_FAILURE;
}