void fillPrimes( int* arPrimes, int size )
{
	int primeCount = 0; 
	int current = 2; 
	
	while( primeCount < size )
	{
		int isPrime = 1; 
		for( int ixPrime = 0;
			     ixPrime < primeCount && arPrimes[ ixPrime ] <= current / arPrimes[ ixPrime ];
				 ixPrime++ )
		{
			if( current % arPrimes[ ixPrime ] == 0 )
			{
				isPrime = 0; 
				break;
			}
		}
		
		if( isPrime )
		{
			arPrimes[ primeCount++ ] = current;
		}
		current++;
	}
}