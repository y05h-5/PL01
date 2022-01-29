#include <stdio.h>
#include <stdlib.h>

#include "rational.h"

#define ever ;;
#define DEFAULT_INPUT "inputs/input.txt"
#define DEFAULT_OUTPUT "outputs/output.txt"

int main(int argc, char* argv[]) {
    FILE *fin, *fout; // File for Input/Output
	
	// Input data
	Rational operand1 = {0}; // First fraction
	Rational operand2 = {0}; // Second fraction
	char operator = '\n';

	//Results
	Rational result = {0}; // Sum of two fractions

	fin = fopen((argc>=2)? argv[1]:DEFAULT_INPUT, "rt");
	if (fin == NULL) {
		printf("Error while opening the input file\n");
		return EXIT_FAILURE;
	}
	fout = fopen((argc==3)? argv[2]:DEFAULT_OUTPUT, "wt");
	if (fout == NULL) {
		printf("Error while opening the output file\n");
		return EXIT_FAILURE;
	}

	char output_double = '\n';
	while (output_double != 'y' && output_double != 'n' &&
		   output_double != 'Y' && output_double != 'N') 
	{
		printf("Output as decimals? [y/N]: ");
		output_double = getchar();
		fflush(stdin);
	}

	for(ever) {
		int checkRead = readLine(fin, &operand1, &operand2, &operator);
		if (checkRead == EOF) break;
		if (checkRead != 1) { // No legal fraction has been read
			printf("\nReading error: probably due to improper fraction format\n");
			return EXIT_FAILURE;
		}
		// Here: we expect to have legal val1_num, val1_denom values
		// Here: we expect to have legal val2_num, val2_denom values

		calcRational(&result, &operand1, &operand2, operator);

		printEquation(fout, operator, output_double, &operand1, &operand2, &result);
	}
	printf("\nOutput was also written to %s\n", (argc==3)? argv[2]:DEFAULT_OUTPUT);
	
	fclose(fin);
	fclose(fout);
	return EXIT_SUCCESS;
}

