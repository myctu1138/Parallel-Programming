#pragma once
#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
class EquationsLinearSystem
{
private:
	int Dimension;
	int* A;
	int* B;
public:
	EquationsLinearSystem(int N);
	~EquationsLinearSystem(void);
private:
	void AutomaticalInitialization(void);
	void CopyArray(double* Source, double* newArray);
	double Absolute(double a);
	int Absolute(int a);
	double MaxDifference(double* X1, double* X2);
public:
	void Solve(void);
};