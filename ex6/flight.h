#pragma once

typedef struct {
	char* id;
	char* location;
	int hour, minute;
} Flight;

int getFlight(const FILEx* file, Flight* flight);