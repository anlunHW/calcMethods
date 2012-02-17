#include <iostream>
#include <cstdlib>

#include "matrix.h"
#include "matrix2x2.h"

using namespace std;

#define M 10
#define N 10

int main() {
	/*
	double mas[M * N];
	for (int i = 0; i < M * N; i++)
		mas[i] = rand() / double(rand() + 1);

	Matrix<double> m(M, N, mas);
	cout << m;
	cout << m.norm_inf() << endl;

	cout << endl << endl;
	Matrix<double> m1 = m.transposed();

	cout << m1;
	cout << m1.norm_inf() << endl;

	cout << endl << endl;

	Matrix2x2<double> ma1 = Matrix2x2<double>(
			1, 5,
			3, 4
			);
	Matrix2x2<double> ma2 = ma1.inversed();
	Matrix2x2<double> ma3 = ma1 * ma2;

	cout << ma1 << endl;
	cout << ma2 << endl;
	cout << ma3 << endl;
	*/

	cout << "Linear equation systems.\nPodkopaev Anton, 345 group\n\n";
	cout << "System:\n";

	Matrix2x2<double> A = Matrix2x2<double>(
			-400.94, 200.2,
			1200.12, -600.96
			);
	cout << "A:\n" << A << endl;

	double vectB[] = {200, -600};
	Matrix<double> b = Matrix<double>(2, 1, vectB);
	cout << "b:\n" << b << endl;

	double vectDeltaB[] = {-1, -1};
	Matrix<double> deltaB = Matrix<double>(2, 1, vectDeltaB);
	cout << "deltaB:\n" << deltaB << endl;

	Matrix<double> x = A.inversed() * b;
	cout << "Solution:\n" << x << endl;

	Matrix<double> disp = A * x - b;
	cout << "Disperancy:\n" << disp << endl;	

	Matrix<double> x_cor = A.inversed() * (b + deltaB);
	cout << "Solution of corrected system:\n" << x_cor << endl;

	Matrix<double> disp_cor = A * x_cor - (b + deltaB);
	cout << "Disperancy of corrected system solution:\n" << disp_cor << endl;	

	Matrix<double> x_delta = x - x_cor;
	double relDisp = x_delta.norm_inf() / x.norm_inf();
	cout << "Actual relative disperancy:\n";
	//	||x-x'|| / ||x||\n";
	cout.width(12);
	cout << relDisp << endl << endl;

	double conditionNum = A.norm_inf() * A.inversed().norm_inf();
	cout << "Condition number:\n";
	cout.width(12);
	cout << conditionNum << endl << endl;

	double relB = deltaB.norm_inf() / b.norm_inf();
	double theoryRelDisp = conditionNum * relB;
	cout << "Theoretical relative disperancy:\n";
	cout.width(12);
	cout << theoryRelDisp << endl << endl;

	return 0;
}
