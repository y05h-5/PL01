/*
 * Programming.Intro
 * Unit 3
 *
 * Cases through in switch
 *
 * switch_cases_through.c
 *
 */
#include <stdio.h>
#include <stdlib.h>

#define DocLevel_Full 3
#define DocLevel_Summary 2
#define DocLevel_NumbersOnly 1

/*
 * Test procedure
 *
 * Modeling bug report with desired documentation level
 * 
 * Compare with the example
 * enum_error_report_example.cpp
 */
int main()
{
	int errorDocLevel;
	errorDocLevel = DocLevel_Full;
	//errorDocLevel = DocLevel_Summary;
	//errorDocLevel = DocLevel_NumbersOnly;
	//errorDocLevel = 0; // Illegal value!

	switch( errorDocLevel )
	{
		case DocLevel_Full:
			printf( "Printing details\n" );							
			// CASE THROUGH Ц 
			// full documentation includes summary

		case DocLevel_Summary:
			printf( "Printing summary\n" );
			// CASE THROUGH Ц 
			// summary includes error number

		case DocLevel_NumbersOnly:
			printf( "Printing error number\n" );
			break;

		default:
			printf( "Internal error: call the developer\n" );
			exit( 1 );
	}

	return( 0 );
}

/*
 *  онец файла Main.cpp
 */