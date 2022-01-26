#include <stdio.h>
#include <math.h>
#include "rational.h"

#define SUCCESS 1
#define FAILURE 0

static void reduce(int* pNum, int* pDenom);
static int gcf(int x, int y);

static int readRational(FILE* fin, int* pNum, int* pDenom) {
	char ch;
	int retScan = fscanf(fin, "%d %c %d", pNum, &ch, pDenom);
	if (retScan == EOF) return EOF;
	if (retScan != 3) return FAILURE; // No legal fraction (format error)
	if (ch != '\\') return FAILURE; // No legal separator (format error)
	if (*pDenom <= 0) return FAILURE; // No legal fraction (illegal denominator)

	reduce(pNum, pDenom);
	return SUCCESS; // One fraction has been successfully loaded
}

static int readOperator(FILE* fin, char* pOp) {
	int retScan = fscanf(fin, " %c ", pOp);
	if (retScan == EOF) return EOF;
	if (retScan != 1) return FAILURE; // Format error
	if (*pOp != '+' && *pOp != '-' && 
		*pOp != '*' && *pOp != '/') return FAILURE; // Illegal operator

	return SUCCESS; // One operator has been successfully loaded
}

int readLine(FILE* fin, int* pN1, int* pD1, int* pN2, int* pD2, char* pOp) {
	int checkVal1 = readRational(fin, pN1, pD1);
	char checkOpr = readOperator(fin, pOp);
	int checkVal2 = readRational(fin, pN2, pD2);

	if (*pOp == '/' && *pN2 == 0) return FAILURE; // Division with 0
	if (checkVal1 == 0 || checkVal2 == 0 || checkOpr == 0)
		return FAILURE;
	if (checkVal1 == EOF || checkVal2 == EOF || checkOpr == EOF)
		return EOF;
	
	return SUCCESS;
}

void printRational(FILE* out, int num, int denom) { 
	printf("%d\\%d", num, denom); 
	fprintf(out, "%d\\%d", num, denom); 
}

void printRationalWithWholes(FILE* out, int num, int denom) {
	int whole = num / denom;
	int remaining_part = num % denom;

	if (whole != 0 || remaining_part == 0) {
		printf("%d ", whole);
		fprintf(out, "%d ", whole);
	}
	if (remaining_part != 0) {
		printRational(out, (whole)? abs(remaining_part) : remaining_part, denom);
	}
}

static inline double rationalToDouble( int num, int denom) { return (double)num / denom; }

void printEquation(FILE* out, char opr, char outdouble, 
				   int vN1, int vD1, int vN2, int vD2, int vNr, int vDr) {
	printRational(out, vN1, vD1);
	printf(" %c ", opr); fprintf(out, " %c ", opr);
	printRational(out, vN2, vD2);
	printf(" = "); fprintf(out, " = ");

	if (outdouble == 'y') {
		printf(" %lf", rationalToDouble(vNr, vDr));
		fprintf(out, " %lf", rationalToDouble(vNr, vDr));
	} else {
		printRationalWithWholes(out, vNr, vDr);
	}

	printf("\n"); fprintf(out, "\n");
}

void sumRational(
	int* pResultNum, int* pResultDenom,
	int arg1_num, int arg1_denom,
	int arg2_num, int arg2_denom) 
{
	int resNum, resDenom;

	resDenom = arg1_denom * arg2_denom;
	resNum = arg1_num * arg2_denom + arg2_num * arg1_denom;

	reduce(&resNum, &resDenom);

	*pResultNum = resNum;
	*pResultDenom = resDenom;
}

void calcRational(
	int* pResultNum, int* pResultDenom,
	int vN1, int vD1, int vN2, int vD2,
	char operator)
{
	int resNum = 0, resDenom = 0;

	switch (operator) {
	case '+':
		resDenom = vD1 * vD2;
		resNum = vN1*vD2 + vN2*vD1;
		break;
	case '-': 
		resDenom = vD1 * vD2;
		resNum = vN1*vD2 - vN2*vD1;
		break;	
	case '*': 
		resDenom = vD1 * vD2;
		resNum = vN1 * vN2;	
		break;	
	case '/': 
		resDenom = vD1 * vN2;
		resNum = vN1 * vD2;
		break;	
	default:
		printf("if you are seeing this, something is wrong with the code\n");
		break;
	}

	reduce(&resNum, &resDenom);

	*pResultNum = resNum;
	*pResultDenom = resDenom;
}

// Assures that we have irreducible fraction
static void reduce(int* pNum, int* pDenom) {
	int num = abs(*pNum);
	int denom = abs(*pDenom);

	if (num == 0) {
		*pDenom = 1;
		return;
	}

	int fraction_gcf = gcf(num, denom);

	*pNum = *pNum / fraction_gcf;
	*pDenom = *pDenom / fraction_gcf;
}

static int gcf(int x, int y) {
	while (x != y) {
		if (x > y)	x = x - y;
		else		y = y - x;
	}
	return x;
}
