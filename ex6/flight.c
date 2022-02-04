#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "error_handler.h"
#include "file_handler.h"
#include "flight.h"

static int getWord(const FILEx* file, char* word) {
	int idx = 0;
	char c = fgetc(file);
	while (isspace(c)) c = fgetc(file->pFile);
	if (c==EOF) return EOF;

	while (!isspace(c) && c != EOF) {
		if (!isalpha(c) && !isdigit(c)) return FAILURE;
		word = (char*) realloc(word, (idx+1)*sizeof(char));
		word[idx++] = c;
	}
	word = (char*) realloc(word, (idx)*sizeof(char));
	word[idx] = '\0';

	return SUCCESS;
}
static int getFlightTime(const FILEx* file, int* h, int* m) {
	ErrorType error = NO_ERROR;
	int readEOF = fileX_read(2, file, " %d:%d", h, m);
	if (readEOF==UNDEFINED) return FAILURE;
	return (readEOF)? EOF : SUCCESS;
}

int getFlight(const FILEx* file, Flight* flight) {
	char* id = NULL, location = NULL;
	int hour = 0, minute = 0;

	int checkID   = getWord(file, id);
	int checkLOC  = (checkID!=EOF || checkID)? getWord(file, location) : FAILURE;
	int checkTIME = (checkLOC!=EOF || checkLOC)? getFlightTime(file, &hour, &minute)
							  				   : FAILURE;
	int validFlight = ((checkID+checkLOC+checkTIME) == 3);
	if (validFlight) {
		strcpy(flight->id, id);
		strcpy(flight->location, location);
		flight->hour = hour;
		flight->minute = minute;
	} 
	else if (validFlight==EOF) { /* do nothing ? */ } 
	else error_handler(file->nFile, DATA_FORMAT);

	if (id!=NULL) free(id);
	if (location!=NULL) free(location);

	return (validFlight)? FAILURE : SUCCESS;
}