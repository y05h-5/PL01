#include <stdio.h>

void fillPrimes(FILE* out, int* arPrimes, int size) {
	int primeCount = 0; 
	int current = 2;
	int isPrime = 1;
	
	while(primeCount < size) {
		isPrime = 1;
		fprintf(out, "CURRENT: %d CHECKED:", current);

		for(int ixPrime = 0;
			   (ixPrime < primeCount) && (arPrimes[ixPrime] <= current/arPrimes[ixPrime]);
				ixPrime++)
		{
			fprintf(out, " %d", arPrimes[ixPrime]);
			if(current%arPrimes[ixPrime] == 0) {
				isPrime = 0; 
				break;
			}
		}
		
		if(isPrime) {
			arPrimes[primeCount++] = current;
			fprintf(out, " PRIME");
		}
		fprintf(out, "\n");
		current++;
	}
}