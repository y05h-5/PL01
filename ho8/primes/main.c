#include <stdio.h>
#include <stdlib.h>

void fillPrimes(FILE* out, int* arPrimes, int size);
void printArray(FILE *out, int* array, int size);

#define NUMPRIMES 20

int main(int argc, char* argv[]) {
	printf("Running: %s\n", argv[0]);
	
	int arPrimes[NUMPRIMES] = {0};
	FILE *out;
	
	if (argc >= 2) out = fopen(argv[1], "wt");
	else out = fopen("output.txt", "wt");
	
	if (out == NULL) {
		printf("Unable to open output file\n");
		return EXIT_FAILURE;
	}

	fillPrimes(out, arPrimes, NUMPRIMES);

	printf("%d prime values found\n", NUMPRIMES);
	// printArray(out, arPrimes, NUMPRIMES);
	
	fclose(out);
}

void printArray(FILE *out, int* array, int size) {
	for( int ix=0; ix<size; ix++ ) {
		fprintf( out, "%d\n", array[ ix ] );
	}
}
