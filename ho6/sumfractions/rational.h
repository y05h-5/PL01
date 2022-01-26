#pragma once
#include <stdio.h>
int readRational(FILE* fin, int* pNum, int* pDenom);
void printRational(int num, int denom);
void sumRational(
	int* pResultNum, int* pResultDenom,
	int arg1_num, int arg1_denom,
	int arg2_num, int arg2_denom);
void addRational(
	int* pResultNum, int* pResultDenom,
	int arg_num, int arg_denom);
void printRationalWithWholes(int num, int denom);
double rationalToDouble(int num, int denom);

