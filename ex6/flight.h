#pragma once

typedef struct {
	char* id;
	char* location;
	int hour, minute;
} Flight;

int getFlight(FILEx* file, Flight* flight);
int getFlight1(FILEx* file, Flight* flight);
void byebyeFlights(Flight* flights);
int getFlightList(FILEx* file, Flight** flights, int* listlen);

int getUserFlight(char** dprt, char** dstn);
void searchFlight(FILEx* out, const Flight* arr_list, const Flight* dprt_list,
				  int arrlen, int dprtlen, const char* from, const char* to);