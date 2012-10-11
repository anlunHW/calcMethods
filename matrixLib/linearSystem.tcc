#pragma once

#include "linearSystem.h"
#include <cmath>

template <typename T>
LinearSystem<T>::LinearSystem(Matrix<T> coef, Matrix<T> constTerm)
		: mSystemSize(coef.lineNumber())
		, mSystemCoef(coef)
		, mConstTerm(constTerm)
{
}
	
template <typename T>
LinearSystem<T>* LinearSystem<T>::createSystem(Matrix<T> coef, Matrix<T> constTerm)
{
	if (coef.lineNumber() != coef.columnNumber()
			|| coef.lineNumber() != constTerm.lineNumber()
			|| constTerm.columnNumber() != 1)
		return 0;

	return new LinearSystem(coef, constTerm);
}

template <typename T>
std::ostream& LinearSystem<T>::print(std::ostream& out) const
{
	for (int i = 0; i < mSystemCoef.lineNumber(); i++) {
		for (int j = 0; j < mSystemCoef.columnNumber(); j++) {
			out.width(mPrintNumberWidth);
			out << mSystemCoef[i][j];
		}

		out.width(mPrintNumberWidth / 4);
		out << "|";

		out.width(mPrintNumberWidth);
		out << mConstTerm[i][0];

		out << std::endl;
	}

	return out;
}

template <typename T>
std::ostream& operator <<(std::ostream& out, LinearSystem<T> const &system)
{
	system.print(out);
	return out;
}

template <typename T>
Matrix<T> LinearSystem<T>::gaussMethodPrinting()
{
	T determinant = 1;

	Matrix<T> startSystemCoef = mSystemCoef;
	Matrix<T> startConstTerm = mConstTerm;

	using namespace std;
	cout << "\n-----------\nGauss method\n-----------\n";
	
	cout << "Start system:\n";
	cout << (*this);
	cout << endl;

	cout << "Forward moving:\n\n";

	for (int i = 0; i < mSystemSize; i++) {
		determinant *= mSystemCoef[i][i];

		T curCoef = 1 / mSystemCoef[i][i];
		mSystemCoef.productLineByNumber(i, curCoef);
		mConstTerm.productLineByNumber(i, curCoef);
		
		cout << "Step " << i + 1 << ":\n";
		cout << (*this);
		cout << "\n\n";
	
		for (int j = i + 1; j < mSystemSize; j++) {
			T coef = -mSystemCoef[j][i];
			mSystemCoef.addLineWithCoef(i, coef, j);
			mConstTerm.addLineWithCoef(i, coef, j);
		}

		cout << "\tAfter production and adding:\n";
		cout << (*this);
		cout << "\n\n";
	}

	// Backward moving
	Matrix<T> solution(mSystemSize, 1);
	for (int i = mSystemSize - 1; i >= 0; i--) {
		T previousVariablesWithCoef = 0;
		for (int j = i + 1; j < mSystemSize; j++) {
			previousVariablesWithCoef += solution[j][0] * mSystemCoef[i][j];
		}

		solution[i][0] = mConstTerm[i][0] - previousVariablesWithCoef;
	}

	cout << "Solution:\n";
	cout << solution;
	cout << endl;

	cout << "Determinant: ";
	cout << determinant;
	cout << endl << endl;

	Matrix<T> disp = startSystemCoef * solution - startConstTerm;
	cout << "Discrepancy:\n" << disp << endl;

	mSystemCoef = startSystemCoef;
	mConstTerm = startConstTerm;

	return solution;
}
	
template <typename T>
Matrix<T> LinearSystem<T>::gaussMethodWithChoosingInLinePrinting()
{
	T determinant = 1;

	Matrix<T> startSystemCoef = mSystemCoef;
	Matrix<T> startConstTerm = mConstTerm;

	using namespace std;
	cout << "\n-----------\nGauss method with choosing in line\n-----------\n";
	
	cout << "Start system:\n";
	cout << (*this);
	cout << endl;

	cout << "Forward moving:\n\n";

	int variablePos[mSystemSize];
	for (int i = 0; i < mSystemSize; i++)
		variablePos[i] = i;

	for (int i = 0; i < mSystemSize; i++) {
		// choosing max abs in line
		T maxAbs = fabs(mSystemCoef[i][i]);
		int maxAbsNumber = i;
		for (int j = i + 1; j < mSystemSize; j++) {
			if (fabs(mSystemCoef[i][j]) > maxAbs) {
				maxAbs = fabs(mSystemCoef[i][j]);
				maxAbsNumber = j;
			}
		}
		if (maxAbs != i) {
			determinant *= -1;
			mSystemCoef.exchangeColumns(i, maxAbsNumber);

			int temp = variablePos[i];
			variablePos[i] = variablePos[maxAbsNumber];
			variablePos[maxAbsNumber] = temp;
		}

		cout << "Step " << i + 1 << ":\n";
		cout << (*this);
		cout << "\n\n";

		determinant *= mSystemCoef[i][i];

		T curCoef = 1 / mSystemCoef[i][i];
		mSystemCoef.productLineByNumber(i, curCoef);
		mConstTerm.productLineByNumber(i, curCoef);
		
		for (int j = i + 1; j < mSystemSize; j++) {
			T coef = -mSystemCoef[j][i];
			mSystemCoef.addLineWithCoef(i, coef, j);
			mConstTerm.addLineWithCoef(i, coef, j);
		}

		cout << "\tAfter production and adding:\n";
		cout << (*this);
		cout << "\n\n";
	}

	// Backward moving
	Matrix<T> preSolution(mSystemSize, 1);
	for (int i = mSystemSize - 1; i >= 0; i--) {
		T previousVariablesWithCoef = 0;
		for (int j = i + 1; j < mSystemSize; j++) {
			previousVariablesWithCoef += preSolution[j][0] * mSystemCoef[i][j];
		}

		preSolution[i][0] = mConstTerm[i][0] - previousVariablesWithCoef;
	}

	Matrix<T> solution(mSystemSize, 1);
	for (int i = 0; i < mSystemSize; i++) {
		solution[variablePos[i]][0] = preSolution[i][0];
	}

	cout << "PreSolution:\n";
	cout << preSolution;
	cout << endl;

	cout << "Solution:\n";
	cout << solution;
	cout << endl;

	cout << "Determinant: ";
	cout << determinant;
	cout << endl << endl;

	Matrix<T> disp = startSystemCoef * solution - startConstTerm;
	cout << "Discrepancy:\n" << disp << endl;

	mSystemCoef = startSystemCoef;
	mConstTerm = startConstTerm;

	return solution;

}
	
template <typename T>
Matrix<T> LinearSystem<T>::gaussMethod()
{
	T determinant = 1;

	Matrix<T> startSystemCoef = mSystemCoef;
	Matrix<T> startConstTerm = mConstTerm;

	for (int i = 0; i < mSystemSize; i++) {
		determinant *= mSystemCoef[i][i];

		T curCoef = 1 / mSystemCoef[i][i];
		mSystemCoef.productLineByNumber(i, curCoef);
		mConstTerm.productLineByNumber(i, curCoef);
		
		for (int j = i + 1; j < mSystemSize; j++) {
			T coef = -mSystemCoef[j][i];
			mSystemCoef.addLineWithCoef(i, coef, j);
			mConstTerm.addLineWithCoef(i, coef, j);
		}
	}

	// Backward moving
	Matrix<T> solution(mSystemSize, 1);
	for (int i = mSystemSize - 1; i >= 0; i--) {
		T previousVariablesWithCoef = 0;
		for (int j = i + 1; j < mSystemSize; j++) {
			previousVariablesWithCoef += solution[j][0] * mSystemCoef[i][j];
		}

		solution[i][0] = mConstTerm[i][0] - previousVariablesWithCoef;
	}

	mSystemCoef = startSystemCoef;
	mConstTerm = startConstTerm;

	return solution;
}
	
template <typename T>
Matrix<T> LinearSystem<T>::gaussMethodWithChoosingInLine()
{
	T determinant = 1;

	Matrix<T> startSystemCoef = mSystemCoef;
	Matrix<T> startConstTerm = mConstTerm;

	int variablePos[mSystemSize];
	for (int i = 0; i < mSystemSize; i++)
		variablePos[i] = i;

	for (int i = 0; i < mSystemSize; i++) {
		// choosing max abs in line
		T maxAbs = fabs(mSystemCoef[i][i]);
		int maxAbsNumber = i;
		for (int j = i + 1; j < mSystemSize; j++) {
			if (fabs(mSystemCoef[i][j]) > maxAbs) {
				maxAbs = fabs(mSystemCoef[i][j]);
				maxAbsNumber = j;
			}
		}
		if (maxAbs != i) {
			determinant *= -1;
			mSystemCoef.exchangeColumns(i, maxAbsNumber);

			int temp = variablePos[i];
			variablePos[i] = variablePos[maxAbsNumber];
			variablePos[maxAbsNumber] = temp;
		}

		determinant *= mSystemCoef[i][i];

		T curCoef = 1 / mSystemCoef[i][i];
		mSystemCoef.productLineByNumber(i, curCoef);
		mConstTerm.productLineByNumber(i, curCoef);
		
		for (int j = i + 1; j < mSystemSize; j++) {
			T coef = -mSystemCoef[j][i];
			mSystemCoef.addLineWithCoef(i, coef, j);
			mConstTerm.addLineWithCoef(i, coef, j);
		}
	}

	// Backward moving
	Matrix<T> preSolution(mSystemSize, 1);
	for (int i = mSystemSize - 1; i >= 0; i--) {
		T previousVariablesWithCoef = 0;
		for (int j = i + 1; j < mSystemSize; j++) {
			previousVariablesWithCoef += preSolution[j][0] * mSystemCoef[i][j];
		}

		preSolution[i][0] = mConstTerm[i][0] - previousVariablesWithCoef;
	}

	Matrix<T> solution(mSystemSize, 1);
	for (int i = 0; i < mSystemSize; i++) {
		solution[variablePos[i]][0] = preSolution[i][0];
	}

	mSystemCoef = startSystemCoef;
	mConstTerm = startConstTerm;

	return solution;

}

template <typename T>
Matrix<T>& LinearSystem<T>::systemCoef() {
	return mSystemCoef;
}

template <typename T>
Matrix<T>& LinearSystem<T>::constTerm() {
	return mConstTerm;
}

template <typename T>
int LinearSystem<T>::systemSize() const {
	return mSystemSize;
}
