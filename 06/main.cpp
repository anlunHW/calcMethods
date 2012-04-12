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
	
	Matrix<double> result(systemSize, 1);
	result[n][0] = (d[n][0] - a[n][0] * k[n][0]) / (a[n][0] * m[n][0] + b[n][0]);

	for (int i = n - 1; i >= 0; i--) {
		result[i][0] = m[i + 1][0] * result[i + 1][0] + k[i + 1][0];
	}

	return result;
}

void interactiveTimeLayerPrinting(
		Matrix<double> const &approximatedSolution_evident
		, Matrix<double> const &approximatedSolution_implicit
		, Matrix<double> const &solution
		)
{
	int columnIndex = 0;
	while (columnIndex >= 0) {
		cout << "Enter number of time layer to print (-1 to stop): ";
		cin >> columnIndex;
		if (columnIndex < 0)
			break;

		cout << "Approximated solution by evident method:\n";
		cout << approximatedSolution_evident.column(columnIndex).transposed() << endl;
		cout << "Approximated solution by implicit method:\n";
		cout << approximatedSolution_implicit.column(columnIndex).transposed() << endl;
		cout << "Solution:\n";
		cout << solution.column(columnIndex).transposed() << endl << endl;

		Matrix<double> discepancy_evident = approximatedSolution_evident.column(columnIndex) - solution.column(columnIndex);
		cout << "Discepancy of evident method:\n" << discepancy_evident.transposed(); 

		Matrix<double> discepancy_implicit = approximatedSolution_implicit.column(columnIndex) - solution.column(columnIndex);
		cout << "Discepancy of implicit method:\n" << discepancy_implicit.transposed(); 
		
		cout << endl << endl;
	}
}

void heatEquationSolving() {
	double x[nodeNumber];
	for (int i = 0; i < nodeNumber; i++) {
		x[i] = intervalLeftBorder + nodeStep * i;
	}

	int const timeNodeNumber = static_cast<int>(maxTime / timeStep) + 1;
	double t[timeNodeNumber];
	for (int i = 0; i < timeNodeNumber; i++) {
		t[i] = timeStep * i;
	}

	// CALCULATING SOLUTION
	Matrix<double> solutionMatrix(nodeNumber, timeNodeNumber);
	for (int i = 0; i < nodeNumber; i++) {
		for (int j = 0; j < timeNodeNumber; j++) {
			solutionMatrix[i][j] = solution(x[i], t[j]);
		}
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

	// IMPLICIT SCHEMA
	Matrix<double> approximatedSolution_implicitMethod(nodeNumber, timeNodeNumber);
	
	// u(i, 0) = g(i)
	for (int i = 0; i < nodeNumber; i++) {
		approximatedSolution_implicitMethod[i][0] = g(x[i]);
	}

	for (int k = 1; k < timeNodeNumber; k++) {
		Matrix<double> b(nodeNumber, 1);
		Matrix<double> a(nodeNumber, 1);
		Matrix<double> c(nodeNumber, 1);
		Matrix<double> d(nodeNumber, 1);

		b[0][0] = 1;
		c[0][0] = 0;
		d[0][0] = alpha(t[k]);

		b[nodeNumber - 1][0] = 1;
		a[nodeNumber - 1][0] = 0;
		d[nodeNumber - 1][0] = beta(t[k]);

		for (int i = 1; i < nodeNumber - 1; i++) {
			b[i][0] = 1 + 2 * heatCoef * timeStep / (nodeStep * nodeStep);
			d[i][0] = timeStep * f(x[i], t[k]) + approximatedSolution_implicitMethod[i][k - 1];

			a[i][0] = -heatCoef * timeStep / (nodeStep * nodeStep);
			c[i][0] = -heatCoef * timeStep / (nodeStep * nodeStep);
		}

		Matrix<double> curSolution_i = threeDiagonalMatrixResolvingMethod(a, b, c, d);
		for (int i = 0; i < nodeNumber; i++) {
			approximatedSolution_implicitMethod[i][k] = curSolution_i[i][0];
		}
	}

	// result printing
		
	interactiveTimeLayerPrinting(approximatedSolution, approximatedSolution_implicitMethod, solutionMatrix);
}

int main() {
	cout << "Problem №6, 8. Solving II level differential equation\nPodkopaev Anton, 345 group\n\n";
	cout << "Solving interval:\n";
	cout << "a = " << intervalLeftBorder << "\n";
	cout << "b = " << intervalRightBorder << "\n\n";
	cout << "f(x, t) = exp(-t) * (x^2 - x + 2)\n";
	cout << "u(x, 0) = cos(0.5 * x) + (1 - x) * x\n";
	cout << "u(0, t) = exp(-0.25 * t)\n";
	cout << "u(1, t) = exp(-0.25 * t) * cos(0.5)\n";
	cout << "Number of node on coordinate dimension: " << nodeNumber << "\n";
	cout << "Coordinate node step: " << nodeStep << "\n";
	cout << "Max time: " << maxTime << "\n";
	cout << "Time node step: " << timeStep << "\n";
	cout << "Number of time nodes: " << (int) maxTime / timeStep << "\n";

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

	heatEquationSolving();

	return 0;
}
