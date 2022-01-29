#pragma once
#include <stdio.h>

typedef struct {
	int num, denom;
} Rational;

int readLine(FILE* fin, Rational* pArg1, Rational* pArg2, char* pOp);
extern inline Rational addRational(const Rational *pArg1, const Rational* pArg2);
extern inline Rational subRational(const Rational *pArg1, const Rational* pArg2);
extern inline Rational mulRational(const Rational *pArg1, const Rational* pArg2);
extern inline Rational divRational(const Rational *pArg1, const Rational* pArg2);
void calcRational(Rational* pRes, const Rational* pArg1, const Rational* pArg2, char operator);
void printRational(FILE* out, const Rational* pArg);
void printRationalWithWholes(FILE* out, const Rational* pArg);
void printEquation(FILE* out, char opr, char outdouble, 
				   const Rational* pArg1, const Rational* pArg2, const Rational* pRes);
