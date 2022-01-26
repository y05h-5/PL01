#include <stdio.h>
#include <stdlib.h>

#include "rational.h"

//void test();

int main()
{
	FILE* fin; // File for INput
	
	// Input data
	int cur_num, cur_denom; // Current fraction

	//Results
	int result_num = 0, result_denom = 1; // Sum of all fractions

	fin = fopen("input.txt", "rt");
	if (fin == NULL)
	{
		printf("Error while opening input file\n");
		return EXIT_FAILURE;
	}

	for (;;)
	{
		int checkRead = readRational(fin, &cur_num, &cur_denom);
		if (checkRead == EOF) break;
		if (checkRead != 1) // No legal fraction has been read
		{
			printf("Reading error: probably due to improper fraction format\n");
			return EXIT_FAILURE;
		}
		
		addRational(&result_num, &result_denom, cur_num, cur_denom);
	}

	printf("Sum of all scanned fractions:");
	printRationalWithWholes(result_num, result_denom);
	printf("\n");
	printf("Converted to double: %lf\n", rationalToDouble(result_num, result_denom));
	
	fclose(fin);
	return EXIT_SUCCESS;
}

