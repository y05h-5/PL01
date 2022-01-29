#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rational.h"

#define SUCCESS 1
#define FAILURE 0

static void reduce(Rational *pArg);
static int gcf(int x, int y);

static int readRational(FILE* fin, Rational* pArg) {
	char ch = '\n';
	int retScan = fscanf(fin, "%d %c %d", &(pArg->num), &ch, &(pArg->denom));
	if (retScan == EOF) return EOF;
	if (retScan != 3) return FAILURE; // No legal fraction (format error)
	if (ch != '\\') return FAILURE; // No legal separator (format error)
	if (pArg->denom <= 0) return FAILURE; // No legal fraction (illegal denominator)

	reduce(pArg);
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

int readLine(FILE* fin, Rational* pArg1, Rational* pArg2, char* pOp) {
	int checkVal1 = readRational(fin, pArg1);
	char checkOpr = readOperator(fin, pOp);
	int checkVal2 = readRational(fin, pArg2);

	if (*pOp == '/' && pArg2->num == 0) return FAILURE; // Division with 0
	if (checkVal1 == 0 || checkVal2 == 0 || checkOpr == 0)
		return FAILURE;
	if (checkVal1 == EOF || checkVal2 == EOF || checkOpr == EOF)
		return EOF;
	
	return SUCCESS;
}

void printRational(FILE* out, const Rational* pArg) {
	printf("%d\\%d", pArg->num, pArg->denom); 
	fprintf(out, "%d\\%d", pArg->num, pArg->denom); 
}

void printRationalWithWholes(FILE* out, const Rational* pArg) {	
    int whole = pArg->num / pArg->denom;
	int remaining_part = pArg->num % pArg->denom;

	if (whole != 0 || remaining_part == 0) {
		printf("%d ", whole);
		fprintf(out, "%d ", whole);
	}
	if (remaining_part != 0) {
        int output_num = (whole)? abs(remaining_part) : remaining_part;
		printRational(out, &(Rational) {output_num, pArg->denom});
	}
}

static inline double rationalToDouble(const Rational* pArg) {
	return (double)pArg->num / pArg->denom;
}

void printEquation(FILE* out, char opr, char outdouble, 
				   const Rational* pArg1, const Rational* pArg2, const Rational* pRes) {
	printRational(out, pArg1);
	printf(" %c ", opr); fprintf(out, " %c ", opr);
	printRational(out, pArg2);
	printf(" = "); fprintf(out, " = ");

	if (outdouble == 'y') {
		printf(" %lf", rationalToDouble(pRes));
		fprintf(out, " %lf", rationalToDouble(pRes));
	} else {
		printRationalWithWholes(out, pRes);
	}
	printf("\n"); fprintf(out, "\n");
}

inline Rational addRational(const Rational* pArg1, const Rational* pArg2) {
    return (Rational) {
        .num = pArg1->num*pArg2->denom + pArg2->num*pArg1->denom,
        .denom = pArg1->denom * pArg2->denom
    };
}
inline Rational subRational(const Rational* pArg1, const Rational* pArg2) {
    return (Rational) {
        .num = pArg1->num*pArg2->denom - pArg2->num*pArg1->denom,
        .denom = pArg1->denom * pArg2->denom
    };
}
inline Rational mulRational(const Rational* pArg1, const Rational* pArg2) {
    return (Rational) {
        .num = pArg1->num * pArg2->num,
        .denom = pArg1->denom * pArg2->denom
    };
}
inline Rational divRational(const Rational* pArg1, const Rational* pArg2) {
    return (Rational) {
        .num = pArg1->num * pArg2->denom,
        .denom = pArg1->denom * pArg2->num
    };
}

void calcRational(Rational* pRes, const Rational* pArg1, 
                  const Rational* pArg2, char operator)
{
	Rational result = {0};

	switch (operator) {
	case '+':
		result = addRational(pArg1, pArg2); break;
	case '-': 
        result = subRational(pArg1, pArg2); break;	
	case '*': 
		result = mulRational(pArg1, pArg2); break;	
	case '/': 
		result = divRational(pArg1, pArg2); break;	
	default:
		printf("if you are seeing this, something is wrong with the code\n");
		exit(EXIT_FAILURE);
	}

	reduce(&result);
	*pRes = result;
}

// Assures that we have irreducible fraction
static void reduce(Rational* pArg) {
	int num = abs(pArg->num);
	int denom = abs(pArg->denom);

	if (num == 0) {
		pArg->denom = 1;
		return;
	}

	int fraction_gcf = gcf(num, denom);

	pArg->num /= fraction_gcf;
	pArg->denom /= fraction_gcf;
}

static int gcf(int x, int y) {
	while (x != y) {
		if (x > y)	x = x - y;
		else		y = y - x;
	}
	return x;
}
