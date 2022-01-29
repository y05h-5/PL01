#include <stdio.h>
#include <stdlib.h>

void fillPrimes( int* arPrimes, int size );
void printArray( FILE *out, int* array, int size );

#define NumPrimes 1000

int main( int argc, char* argv[] )
{
	printf( "Running: %s\n", argv[0]);
	
	int arPrimes[NumPrimes];
	FILE *out;
	
	if (argc >= 2)
	{
		out = fopen(argv[1], "wt");
	}
	else
	{
		out = fopen("output.txt", "wt");
	}
	
	if (out == NULL)
	{
		printf("Unable to open output file\n");
		return EXIT_FAILURE;
	}

	fillPrimes( arPrimes, NumPrimes );

	printf( "%d prime values found\n", NumPrimes );
	
	printArray( out, arPrimes, NumPrimes );
	
	fclose( out );
}

void printArray( FILE *out, int* array, int size )
{
	for( int ix=0; ix<size; ix++ )
	{
		fprintf( out, "%d\n", array[ ix ] );
	}
}
