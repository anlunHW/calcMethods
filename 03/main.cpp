#include <iostream>
#include <memory>
#include <cmath>
#include "../matrixLib/linearSystem.h"

using namespace std;

typedef double CurrentType;

CurrentType eArr[] = {
	1, 0, 0,
	0, 1, 0,
	0, 0, 1
};

Matrix<CurrentType> matrixE(3, 3, eArr);

CurrentType const delta = 0.001;
CurrentType const eps = 0.001;

CurrentType startApproximationArr[] = {
	1,
	1,
	1
};

int main() {
	cout << "Linear equation systems. Iterative methods.\nPodkopaev Anton, 345 group\n";
	cout << "delta: " << delta << endl;
	
	CurrentType coefArr[] = {
		2.17426, 0.39894, 0.22180,
		0.39894, 3.11849, 0.60613,
		0.22180, 0.60613, 4.79210
	};
	Matrix<CurrentType> systemCoef(3, 3, coefArr);

	CurrentType constTermArr[] = {
		2.13909,
		6.30779,
		5.98485
	};
	Matrix<CurrentType> constTerm(3, 1, constTermArr);

	auto_ptr< LinearSystem<CurrentType> > sys(LinearSystem<CurrentType>::createSystem(systemCoef, constTerm));

	//Matrix<CurrentType> solution = sys->gaussMethod();
	Matrix<CurrentType> solution = sys->gaussMethodWithChoosingInLine();

	cout << "\nSystem:\n";
	cout << *sys;
	cout << endl;

	cout << "Solution that was found by Gauss method:\n";
	cout << solution;
	cout << endl;

	cout << "\t\tUsing Gershgorin theorem:\n";
	CurrentType m = sys->systemCoef().gershgorinLeftBorder();
	CurrentType M = sys->systemCoef().gershgorinRightBorder();

	cout << "m: " << m << endl;
	cout << "M: " << M << endl;
	
	CurrentType alpha = 2 / (m + M);
	cout << "Optimal parameter (alpha): " << alpha << endl;

	cout << "\nScalar method of finding prime matrix eigenvalue:\n";
	CurrentType approximatedEigenvalue = sys->systemCoef().approximatedPrimeEigenvalue_scalarMethod(delta, cout);

	Matrix<CurrentType> matrixB = sys->systemCoef() - approximatedEigenvalue * matrixE;
	cout << "\nOpposite spectrum border: " <<  matrixB.approximatedPrimeEigenvalue_scalarMethod(delta) + approximatedEigenvalue << endl;

	cout << "---------------\n\n" << "Working on transformed system" << "\n---------------\n";

	Matrix<CurrentType> bAlpha = matrixE - alpha * sys->systemCoef();
	Matrix<CurrentType> cAlpha = alpha * sys->constTerm();

	cout << "B alpha:\n" << bAlpha << endl; 
	cout << "B alpha inf norm: " << bAlpha.norm_inf() << endl << endl;	
	cout << "C alpha:\n" << cAlpha << endl;

	cout << "Degree method of finding prime matrix eigenvalue (on B alpha matrix):\n";
	CurrentType approximatedEigenvalue_Balpha = bAlpha.approximatedPrimeEigenvalue_degreeMethod(delta);
	cout << "Prime eigenvalue: " << approximatedEigenvalue_Balpha << endl;
	
	Matrix<CurrentType> matrixB_bAplha = bAlpha - approximatedEigenvalue_Balpha * matrixE;
	cout << "Opposite spectrum border: " <<  matrixB_bAplha.approximatedPrimeEigenvalue_degreeMethod(delta) + approximatedEigenvalue_Balpha << endl;
	
	cout << "\n---------------\nA priori estimation step number calculation" << endl;
	// x(0) = 0
	// x(1) = bAlpha * x (0) + cAlpha = cAlpha;
	// x(1) - x(0) = x(1)
	Matrix<CurrentType> x_0 = cAlpha - cAlpha;
	Matrix<CurrentType> x_1 = cAlpha;

	int const k = log(eps * (1 - bAlpha.norm_inf()) / x_1.norm_inf()) / log(bAlpha.norm_inf()) + 1; // +1 because of double -> int trancation
	cout << "K: " << k << endl;

	cout << "\n---------------\nIterative method" << endl;
	int k_iter = 1;
	Matrix<CurrentType> curDiff = x_1 - x_0;
	Matrix<CurrentType> curX = x_0;
	Matrix<CurrentType> previousX = x_0;
	while (curDiff.norm_inf() > eps) {
		cout << "\nStep " << k_iter << "\n---------------\n";
		cout << "A priori estimation: " << pow(bAlpha.norm_inf(), k_iter) * x_1.norm_inf() / (1 - bAlpha.norm_inf()) << endl;
		cout << "A posteriori estimation: " << bAlpha.norm_inf() * curDiff.norm_inf() / (1 - bAlpha.norm_inf()) << endl;
		cout << "Discrepancy:\n" << sys->systemCoef() * curX - sys->constTerm(); 

		previousX = curX;
		curX = bAlpha * curX + cAlpha;
		curDiff = curX - previousX;
		k_iter++;
	}
	cout << "\nResult\n---------------\n";
	cout << "Number of steps: " << k_iter << endl;
	cout << "A priori estimated number of steps: " << k << endl;
	cout << "A priori estimation: " << pow(bAlpha.norm_inf(), k_iter) * x_1.norm_inf() / (1 - bAlpha.norm_inf()) << endl;
	cout << "A posteriori estimation: " << bAlpha.norm_inf() * curDiff.norm_inf() / (1 - bAlpha.norm_inf()) << endl;

	cout << "\nApproximated solution:\n" << curX;


	cout << "\n---------------\nSeidel method" << endl;
	//x_0 = 0
	Matrix<CurrentType> curDiff_seidel = x_0;
	Matrix<CurrentType> curX_seidel = x_0;
	Matrix<CurrentType> previousX_seidel = x_0;
	k_iter = 0;
	do {
		cout << "\nStep " << k_iter << "\n---------------\n";
		cout << "Discrepancy:\n" << sys->systemCoef() * curX - sys->constTerm(); 
		for (int i = 0; i < sys->systemCoef().lineNumber(); i++) {
			curX_seidel[i][0] = sys->constTerm()[i][0] / sys->systemCoef()[i][i];
			for (int j = 0; j < i; j++) {
				curX_seidel[i][0] -= curX_seidel[j][0] * sys->systemCoef()[i][j] / sys->systemCoef()[i][i];
			}
			for (int j = i + 1; j < sys->systemCoef().lineNumber(); j++) {
				curX_seidel[i][0] -= previousX_seidel[j][0] * sys->systemCoef()[i][j] / sys->systemCoef()[i][i];
			}
		}

		curDiff_seidel = curX_seidel - previousX_seidel;
		previousX_seidel = curX_seidel;

		k_iter++;
	} while (curDiff_seidel.norm_inf() > eps);
	cout << "\nResult\n---------------\n";
	cout << "Number of steps: " << k_iter << endl;

	cout << "\nApproximated solution:\n" << curX_seidel;

	cout << "\n\t\tComparison\n\t\t---------------\n";
	cout << "\nIterative solution:\n" << curX;
	cout << "\nSeidel solution:\n" << curX_seidel;
	cout << "\nSeidel solution - iterative solution:\n" << curX_seidel - curX;

	return 0;
}
