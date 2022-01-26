#include <stdio.h>
#include <math.h>
#include "rational.h"

void reduce(int* pNum, int* pDenom);
int gcf(int x, int y);

int readRational(FILE* fin, int* pNum, int* pDenom)
{
	char ch;
	int retScan = fscanf(fin, "%d %c %d", pNum, &ch, pDenom);
	if (retScan == EOF) return EOF;
	if (retScan != 3) return 0; // No legal fraction (format error)
	if (ch != '\\') return 0; // No legal separator (format error)
	if (*pDenom <= 0) return 0; // No legal fraction (illegal denominator)

	reduce(pNum, pDenom);
	return 1; // One fraction has been successfully loaded
}

void printRational(int num, int denom)
{
	printf("%d\\%d", num, denom);
}

void printRationalWithWholes(int num, int denom)
{
	int whole = num / denom;
	int remaining_part = num % denom;

	if (whole != 0)
	{
		printf("%d ", whole);
	}

	printRational(remaining_part, denom);
}

double rationalToDouble( int num, int denom)
{
	return (double)num / denom;
}

void sumRational(
	int* pResultNum, int* pResultDenom,
	int arg1_num, int arg1_denom,
	int arg2_num, int arg2_denom)
{
	*pResultNum = arg1_num;
	*pResultDenom = arg1_denom;

	addRational(pResultNum, pResultDenom, arg2_num, arg2_denom);
}

void addRational(  
	int* pResultNum, int* pResultDenom,
	int arg_num, int arg_denom)
{
	int resNum, resDenom;

	resDenom = *pResultDenom * arg_denom;
	resNum = *pResultNum * arg_denom + arg_num * *pResultDenom;

	reduce(&resNum, &resDenom);

	*pResultNum = resNum;
	*pResultDenom = resDenom;
}

// Assures that we have irreducible fraction
void reduce(int* pNum, int* pDenom)
{
	int num = abs(*pNum);
	int denom = abs(*pDenom);

	if (num == 0)
	{
		*pDenom = 1;
		return;
	}

	int fraction_gcf = gcf(num, denom);

	*pNum = *pNum / fraction_gcf;
	*pDenom = *pDenom / fraction_gcf;
}

int gcf(int x, int y)
{
	while (x != y)
	{
		if (x > y)	x = x - y;
		else		y = y - x;
	}
	return x;
}

//void test()
//{
//	int frac_num = -110;
//	int frac_denom = 1210;
//
//	reduce(&frac_num, &frac_denom);
//
//	printf("%d %d\n", frac_num, frac_denom);
//}
