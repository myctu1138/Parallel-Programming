#include "EquationsLinearSystem.h"

EquationsLinearSystem::EquationsLinearSystem(int N) {
	srand(time(0));
	Dimension = N;
	A = new int[N*N];
	B = new int[N];

	this->AutomaticalInitialization();
}
EquationsLinearSystem::~EquationsLinearSystem(void)
{
	delete A;
	delete B;
}
void EquationsLinearSystem::AutomaticalInitialization(void) {
#pragma omp parallel for
	for (int I = 0; I < Dimension; I++)
	{
		double Sum = 0;
		for (int J = 0; J < Dimension;  J++)
		{
			if (I != J) {
				A[I*Dimension + J] = rand() % 18 - 9;
				Sum += this->Absolute(A[I*Dimension + J]);
			}
		}
		int sign;
		if (rand() > 16000)
			sign = 1;
		else
			sign = -1;
		A[I*Dimension + I] = Sum * (rand()/32767.0 + 1) * sign;
		B[I] = rand() % 18 - 9;
	}
}
void EquationsLinearSystem::CopyArray(double* Source, double* newArray) {
	for (int I = 0; I < Dimension; I++)
		newArray[I] = Source[I];
}
double EquationsLinearSystem::Absolute(double a) {
	if (a > 0)
		return a;
	else
		return -a;
}
int EquationsLinearSystem::Absolute(int a) {
	if (a > 0)
		return a;
	else
		return -a;
}
double EquationsLinearSystem::MaxDifference(double* X1, double* X2) {
	double Result = 0.0;
#pragma omp parallel for shared(Result)
	for (int I = 0; I < Dimension; I++)
	{
		double ValueofCurrentIteration = this->Absolute(X1[I]-X2[I]);
		if (ValueofCurrentIteration > Result)
			Result = ValueofCurrentIteration;
	}
	return Result;
}
void EquationsLinearSystem::Solve(void) {

	double* X = new double[Dimension];
	double* X_last = new double[Dimension];

	for (int I = 0; I < Dimension; I++)
		X_last[I] = B[I] / A[I*Dimension + I];

	const double Epsilon = 0.0001;
	double maxDifference;

	int IterationCounter = 1;
	do
	{
		if (IterationCounter > 1)
			this->CopyArray(X, X_last);

#pragma omp parallel for
		for (int I = 0; I < Dimension; I++)
		{
			X[I] = B[I];
			for (int J = 0; J < Dimension; J++)
			{
				if (I != J)
					X[I] -= A[I*Dimension + J] * X_last[J];
			}
			X[I] = X[I] / A[I*Dimension + I];
			X[0];
			X[1];
		}
		maxDifference = MaxDifference(X, X_last);

		IterationCounter++;
	} while (maxDifference > Epsilon);
}