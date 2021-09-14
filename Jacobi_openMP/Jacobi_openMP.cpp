// Jacobi_openMP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "EquationsLinearSystem.h"

int main()
{
	int dimension;
	printf("Input dimension of Matrix\n");
	scanf_s("%d", &dimension);
	EquationsLinearSystem* linearSystem = new EquationsLinearSystem(dimension);

	clock_t start = clock();

	linearSystem->Solve();

	clock_t finish = clock();
	printf("Time = %fsec.", (double)(finish - start) / CLOCKS_PER_SEC);
	system("pause");


	return 0;
}