#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rational.h"

#define ever ;;
#define DEFAULT_INPUT "inputs/input.txt"
#define DEFAULT_OUTPUT "outputs/output.txt"

int main(int argc, char* argv[]) {
	FILE *fin, *fout; // File for Input/Output
	
	// Input data
	int val1_num = 0, val1_denom = 0; // First fraction
	int val2_num = 0, val2_denom = 0; // Second fraction
	char operator = '\n';

	//Results
	int result_num = 0, result_denom = 0; // Sum of two fractions

	fin = fopen((argc>=2)? argv[1]:DEFAULT_INPUT, "rt");
	if (fin == NULL) {
		printf("Error while opening input file\n");
		return EXIT_FAILURE;
	}
	fout = fopen((argc==3)? argv[2]:DEFAULT_OUTPUT, "wt");
	if (fout == NULL) {
		printf("Error while opening output file\n");
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
		int checkRead = readLine(fin, &val1_num, &val1_denom, 
								 	  &val2_num, &val2_denom, &operator);
		if (checkRead == EOF) break;
		if (checkRead != 1) { // No legal fraction has been read
			printf("Reading error: probably due to improper fraction format\n");
			return EXIT_FAILURE;
		}
		// Here: we expect to have legal val1_num, val1_denom values
		// Here: we expect to have legal val2_num, val2_denom values

		calcRational(&result_num, &result_denom, val1_num, val1_denom, val2_num, val2_denom, operator);

		printEquation(fout, operator, output_double,
					  val1_num, val1_denom, 
					  val2_num, val2_denom, 
					  result_num, result_denom);
	}
	printf("\nOutput was also written to %s\n", (argc==3)? argv[2]:DEFAULT_OUTPUT);
	
	fclose(fin);
	fclose(fout);
	return EXIT_SUCCESS;
}