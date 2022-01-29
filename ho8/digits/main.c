#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_DIGITS 64
#define DECIMAL_BASE 10
#define BINARY_BASE 2

int openFile( FILE**, char*, char* );
void printDigitsReverseOrder( FILE*fout, int value, int base );
void printDigitsStraightOrder( FILE*fout, int value, int base );

int main(int argc, char** argv) {

    FILE *fin;
    FILE *fout;
    
    int inputValue;
    
    if( argc < 3 )
    {
        printf("Command line parameters are missing\n");
        return (EXIT_FAILURE);
    }
    
    if( !openFile(&fin,argv[1],"rt")) return (EXIT_FAILURE);
    
    int checkScan = fscanf( fin, "%d", &inputValue);
    if( checkScan == EOF )
    {
        printf("Input file seems to be empty\n");
        return (EXIT_FAILURE);
    }
    if( checkScan != 1 )
    {
        printf("Illegal data formal in input file\n");
        return (EXIT_FAILURE);
    }
    
    fclose(fin);
    
    if( inputValue <= 0 )
    {
        printf("Input value should be positive\n");
        return (EXIT_FAILURE);
    }
    
    printf("Input value: %d", inputValue);
    
    if( !openFile(&fout, argv[2], "wt")) return (EXIT_FAILURE);
    
    printDigitsReverseOrder( fout, inputValue, DECIMAL_BASE );
    printDigitsStraightOrder( fout, inputValue, DECIMAL_BASE );
    
    printDigitsReverseOrder( fout, inputValue, BINARY_BASE );
    printDigitsStraightOrder( fout, inputValue, BINARY_BASE );
        
    fclose(fout);
    return (EXIT_SUCCESS);
}

int openFile( FILE** pFile, char* filename, char* filemode)
{
    *pFile = fopen(filename, filemode);
    if( *pFile == NULL )
    {
        printf("Unable to open file \"%s\"\n");
        return 0; // not opened
    }
    
    return 1; // successfully opened
}

void printDigitsReverseOrder( FILE*fout, int value, int base )
{
    int digit;
    int sumDigits = 0;
    
    int remainingValue = value;
    
    while( remainingValue > 0 )
    {
        digit = remainingValue % base;
        
        fprintf(fout, "%d ", digit);
        
        sumDigits += digit; // sumDigit = sumDigit + digit;
        remainingValue /= base; // remainingValue = remainingValue / base;
    }
    
    fprintf(fout, "; sum is %d\n", sumDigits);
}

void printDigitsStraightOrder( FILE*fout, int value, int base )
{
    int digit;
    int sumDigits = 0;
    
    int allDigits[ NUMBER_OF_DIGITS ];
    int ixDigit = 0;
    
    int remainingValue = value;
    
    while( remainingValue > 0 )
    {
        digit = remainingValue % base;
        allDigits[ ixDigit++ ] = digit;
                        
        sumDigits += digit; // sumDigit = sumDigit + digit;
        remainingValue /= base; // remainingValue = remainingValue / base;
    }
    
    for( int ixPrint = ixDigit-1; ixPrint >= 0; ixPrint--)
    {
        fprintf(fout, "%d ", allDigits[ ixPrint ] );
    }
    
    fprintf(fout, "; sum is %d\n", sumDigits);
    
}
