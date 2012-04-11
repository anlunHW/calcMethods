#include <iostream>
#include "problemData.h"
#include "../matrixLib/matrix.h"

using namespace std;

//a.size = n + 1 but we're using (1..n)
//b.size = n + 1 (0..n)
//c.size = n + 1 but we're using (0..n-1)
//d.size = n + 1 (0..n)
Matrix<double> threeDiagonalMatrixResolvingMethod(
		Matrix<double> const &a, Matrix<double> const &b, Matrix<double> const &c,
		Matrix<double> const &d)
{
	int const systemSize = b.lineNumber(); // n + 1
	int const n = systemSize - 1; // n

	Matrix<double> m(systemSize, 1);
	Matrix<double> k(systemSize, 1);

	m[1][0] = -c[0][0] / b[0][0];
	k[1][0] = d[0][0] / b[0][0];

	for (int i = 1; i < n; i++) {
		m[i + 1][0] = -c[i][0] / (a[i][0] * m[i][0] + b[i][0]);
		k[i + 1][0] = (d[i][0] - a[i][0] * k[i][0]) / (a[i][0] * m[i][0] + b[i][0]);
	}
	cout << m;
	
	Matrix<double> result(systemSize, 1);
	result[n][0] = (d[n][0] - a[n][0] * k[n][0]) / (a[n][0] * m[n][0] + b[n][0]);

	for (int i = n - 1; i >= 0; i--) {
		result[i][0] = m[i + 1][0] * result[i + 1][0] + k[i + 1][0];
	}

	return result;
}

void heatEquationSolving() {
	// tau
	double const timeStep = nodeStep * nodeStep / (2 * heatCoef);

	double x[nodeNumber];
	for (int i = 0; i < nodeNumber; i++) {
		x[i] = intervalLeftBorder + nodeStep * i;
	}

	int const timeNodeNumber = static_cast<int>(maxTime / timeStep) + 1;
	double t[timeNodeNumber];
	for (int i = 0; i < timeNodeNumber; i++) {
		t[i] = timeStep * i;
	}

	Matrix<double> approximatedSolution(nodeNumber, timeNodeNumber);

	// u(i, 0) = g(i)
	for (int i = 0; i < nodeNumber; i++) {
		approximatedSolution[i][0] = g(x[i]);
	}

	// u(0, k) = alpha(k)
	// u(nodeNumber - 1, k) = beta(k)
	for (int k = 0; k < timeNodeNumber; k++) {
		approximatedSolution[0][k] = alpha(t[k]);
		approximatedSolution[nodeNumber - 1][k] = beta(t[k]);
	}

	// EVIDENT SCHEMA
	double const equationCoef = heatCoef * timeStep / (nodeStep * nodeStep);
	
	for (int k = 1; k < timeNodeNumber; k++) {
		for (int i = 1; i < nodeNumber - 1; i++) {
			approximatedSolution[i][k] =
				(1 - 2 * equationCoef) * approximatedSolution[i][k - 1]
				+ equationCoef * (approximatedSolution[i + 1][k - 1] + approximatedSolution[i - 1][k - 1])
				+ timeStep * f(x[i], t[k - 1]);
		}
	}

	/*
	approximatedSolution[i][k] =
		(1 - 2 * equationCoef) * approximatedSolution[i][k - 1]
		+ equationCoef * (approximatedSolution[i + 1][k - 1] + approximatedSolution[i - 1][k - 1])
		+ timeStep * f(x[i], t[k - 1]);
	*/
	// IMPLICIT SCHEMA
}

int main() {
	/*
	double a_arr[] = {0, 1, 1, 1};
	double b_arr[] = {1, 1, 1, 1};
	double c_arr[] = {4, 2, 3, 0};
	double d_arr[] = {1, 1, 1, 1 };

	Matrix<double> a(4, 1, a_arr);
	Matrix<double> b(4, 1, b_arr);
	Matrix<double> c(4, 1, c_arr);
	Matrix<double> d(4, 1, d_arr);
	
	cout << threeDiagonalMatrixResolvingMethod(a, b, c, d);
	
	cout << solution(0, 0) << endl;
	*/

	return 0;
}
