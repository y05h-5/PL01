#pragma once
#include <stdio.h>

typedef struct {
	int num, denom;
} Rational;

// int readRational(FILE* fin, Rational* pArg);
// void printRational(Rational arg);
// void sumRational(Rational* pResult,Rational arg1,Rational arg2);
// void addRational(Rational *pResult,Rational arg);
// void printRationalWithWholes(Rational arg);
// double rationalToDouble(Rational arg);

int readLine(FILE* fin, Rational* pArg1, Rational* pArg2, char* pOp);
inline Rational addRational(const Rational *pArg1, const Rational* pArg2);
inline Rational subRational(const Rational *pArg1, const Rational* pArg2);
inline Rational mulRational(const Rational *pArg1, const Rational* pArg2);
inline Rational divRational(const Rational *pArg1, const Rational* pArg2);
void calcRational(Rational* pRes, const Rational* pArg1, const Rational* pArg2, char operator);
void printRational(FILE* out, const Rational* pArg);
void printRationalWithWholes(FILE* out, const Rational* pArg);
void printEquation(FILE* out, char opr, char outdouble, 
				   const Rational* pArg1, const Rational* pArg2, const Rational* pRes);
