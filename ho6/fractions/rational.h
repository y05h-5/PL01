#pragma once
#include <stdio.h>

int readLine(FILE* fin, int* pN1, int* pD1, int* pN2, int* pD2, char* pOp);
// void sumRational(
// 	int* pResultNum, int* pResultDenom,
// 	int arg1_num, int arg1_denom,
// 	int arg2_num, int arg2_denom);
void calcRational(
	int* pResultNum, int* pResultDenom,
	int vN1, int vD1, int vN2, int vD2,
	char operator);
void printRational(FILE* out, int num, int denom);
void printRationalWithWholes(FILE* out, int num, int denom);
void printEquation(FILE* out, char opr, char outdouble, 
				   int vN1, int vD1, int vN2, int vD2, int vNr, int vDr);
// double rationalToDouble(int num, int denom);

