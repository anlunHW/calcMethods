#include <iostream>
#include <cmath>
#include <memory>
#include "../matrixLib/linearSystem.h"
#include "problemData.h"
#include "../integralLib/functionProduction.h"

using namespace std;

// INITIALIZATION
Function** alphaArr = new Function* [5];
Function** betaArr = new Function* [5];
Function* rightFunc = new RightSideFunc();

double scalarProduct[5][5];

int const printWidth = 12;
// INITIALIZATION END

Matrix<double> trivialKernelMethod(unsigned n) {
	Matrix<double> eN(n);

	Matrix<double> betaAlphaScalar(n);
	for (unsigned i = 0; i < n; i++) {
		for (unsigned j = 0; j < n; j++) {
			betaAlphaScalar[i][j] = scalarProduct[i][j];
		}
	}

	// matrixCoef - matrix of coef on Ai
	Matrix<double> matrixCoef = betaAlphaScalar + eN;

	Matrix<double> constTerm(n, 1);
	for (unsigned i = 0; i < n ; i++) {
		FunctionProduction curProduction(
				betaArr[i],
				rightFunc
				);
		constTerm[i][0] =
			curProduction.calculateIntegral(nodeNumber,
					intervalLeftBorder,
					intervalRightBorder);
	}

	auto_ptr< LinearSystem<double> > systemAi(
		LinearSystem<double>::createSystem(matrixCoef, constTerm)
		);
	Matrix<double> solution = systemAi->gaussMethodWithChoosingInLine();

	cout << "Trivial kernel method\n";
	cout << "Rank " << n << endl;
	cout << "A:\n" << solution << endl;

	cout.width(printWidth);
	cout << "Node:";
	cout.width(printWidth);
	cout << "Value:";
	cout << "\n-----------------------------------\n";

	Matrix<double> result(nodeNumber + 1, 2);

	for (unsigned i = 0; i < nodeNumber + 1; i++) {
		double curNode = intervalLeftBorder + 
			i * (intervalRightBorder - intervalLeftBorder)
			/ nodeNumber;

		double curValue = rightFunc->func(curNode);
		for (unsigned j = 0; j < n; j++) {
			curValue -= solution[j][0] * alphaArr[j]->func(curNode);
		}

		cout.width(printWidth);
		cout << curNode;
		cout.width(printWidth);
		cout << curValue;

		result[i][0] = curNode;
		result[i][1] = curValue;

		cout << endl;
	}
	cout << endl;

	return result;
}

//void mechanicMethod(unsigned gaussNodeNumber, double* gaussNode, double* gaussCoef) {
Matrix<double> mechanicMethod(unsigned gaussNodeNumber, double* gaussNode_1, double* gaussCoef_1) {
	double gaussNode[gaussNodeNumber];

	double h = (intervalRightBorder - intervalLeftBorder) / 2;
	for (unsigned i = 0; i < gaussNodeNumber; i++) {
		gaussNode[i] = (intervalRightBorder + intervalLeftBorder) / 2 + gaussNode_1[i] * h;
	}

	double gaussCoef[gaussNodeNumber];
	for (unsigned i = 0; i < gaussNodeNumber; i++) {
		gaussCoef[i] = gaussCoef_1[i] * h;
	}

	Matrix<double> constTerm(gaussNodeNumber, 1);
	for (unsigned i = 0; i < gaussNodeNumber; i++) {
		constTerm[i][0] = rightFunc->func(gaussNode[i]);
	}

	Matrix<double> systemCoef(gaussNodeNumber, gaussNodeNumber);
	for (unsigned i = 0; i < gaussNodeNumber; i++) {
		for (unsigned j = 0; j < gaussNodeNumber; j++) {
			systemCoef[j][i] = gaussCoef[i]
				* KernelFunc::func(gaussNode[i], gaussNode[j]);
		}
	}
	systemCoef += Matrix<double>(gaussNodeNumber);

	auto_ptr< LinearSystem<double> > systemUi(
		LinearSystem<double>::createSystem(systemCoef, constTerm)
		);
	
	cout << *systemUi << endl;

	Matrix<double> solutionUi = systemUi->gaussMethodWithChoosingInLine();

	cout << "Ui:\n";
	cout << solutionUi << endl << endl;

	Matrix<double> result(nodeNumber + 1, 2);

	cout << "Mechenic quadratur method\n";
	cout << "Quadratur node number: " << gaussNodeNumber << endl;

	cout.width(printWidth);
	cout << "Node:";
	cout.width(printWidth);
	cout << "Value:";
	cout << "\n-----------------------------------\n";

	for (unsigned i = 0; i < nodeNumber + 1; i++) {
		double curNode = intervalLeftBorder + 
			i * (intervalRightBorder - intervalLeftBorder)
			/ nodeNumber;

		double curValue = rightFunc->func(curNode);
		for (unsigned j = 0; j < gaussNodeNumber; j++) {
			curValue -= gaussCoef[j] * solutionUi[j][0]
				* KernelFunc::func(curNode, gaussNode[j]);
		}

		cout.width(printWidth);
		cout << curNode;
		cout.width(printWidth);
		cout << curValue;

		result[i][0] = curNode;
		result[i][1] = curValue;

		cout << endl;
	}
	cout << endl;

	return result;
}

int main() {
	for (unsigned i = 0; i < 5; i++)
		alphaArr[i] = AlphaFunc::createFunctionByNumber(i + 1);
	for (unsigned i = 0; i < 5; i++)
		betaArr[i] = BetaFunc::createFunctionByNumber(i + 1);

	// SCALAR PRODUCTS
	for (unsigned i = 0; i < 5; i++)
		for (unsigned j = 0; j < 5; j++) {
			FunctionProduction curProduction(
					betaArr[i],
					alphaArr[j]
					);
			scalarProduct[i][j] =
				//curProduction.calculateIntegral(nodeNumber,
				curProduction.calculateIntegral(10000,
						intervalLeftBorder,
						intervalRightBorder);
		}

	Matrix<double> result3(trivialKernelMethod(3));
	Matrix<double> result4(trivialKernelMethod(4));

	double maxDiscrepancy = 0;
	for (unsigned i = 0; i < nodeNumber + 1; i++)
		maxDiscrepancy = max(maxDiscrepancy,
				fabs(result4[i][1] - result3[i][1]));
	cout << "Max discrepancy: " << maxDiscrepancy << endl << endl;

	/* TESTING
	double curX = 0.1;
        double curY = 0.75;	
	double result = 0;
	for (unsigned i = 0; i < 4; i++) {
		result += alphaArr[i]->func(curX) * betaArr[i]->func(curY);
	}
	cout << "Result: " << result << endl;
	double realRes = exp(curX * curY) / 5;
	cout << "exp(x, y) / 5: " << realRes << endl; 
	cout << "discrepancy: " << fabs(realRes - result) << endl;
	*/

	double gaussNode3[] = {-0.7745966692, 0, 0.7745966692};
	double gaussCoef3[] = {0.555555556, 0.888888889, 0.555555556};
	mechanicMethod(3, gaussNode3, gaussCoef3);


	double gaussNode4[] = {-0.861136312, -0.339981044, 0.339981044, 0.861136312};
	double gaussCoef4[] = {0.347854845, 0.652145155, 0.652145155, 0.347854845};
	mechanicMethod(4, gaussNode4, gaussCoef4);

	// MEMORY CLEANING	
	for (unsigned i = 0 ; i < 5; i++)
		delete alphaArr[i];
	delete [] alphaArr;

	for (unsigned i = 0 ; i < 5; i++)
		delete betaArr[i];
	delete [] betaArr;
	
	delete rightFunc;

	return 0;
}
