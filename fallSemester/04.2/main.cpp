#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

class CurFunc {
	public:
		static double func(double x, int derDegree) {
			if (derDegree == 0)
				return x * x - sin(5 * x);
			if (derDegree == 1)
				return 2 * x - 5 * cos(5 * x);
			if (derDegree == 2)
				return 2  + 25 * sin(5 * x);

			return 1;
		}

};

template<class FuncClass>
class CalcDerivating {
	public:
		CalcDerivating(double start, int nodeNumber, double step): start(start),
				nodeNumber(nodeNumber), step(step), funcNodes(0), funcValues(0) {
			funcNodes = new double[nodeNumber]; 
			for (int i = 0; i < nodeNumber; i++)
				funcNodes[i] = start + step * i;

			funcValues = new double[nodeNumber];
			for (int i = 0; i < nodeNumber; i++)
				funcValues[i] = FuncClass::func(funcNodes[i], 0);

			derFuncValues_1 = new double[nodeNumber];
			der_1();

			derFuncValues_2 = new double[nodeNumber];
			der_2();
		}

		void printParameters() {
			cout << "Problem parameters\n***********" << endl;
			cout << "Start point: " << start << endl;
			cout << "Last node number: " << nodeNumber - 1 << endl;
			cout << "Node step: " << step << endl;
		}

		void print() {
			int symNum = 22;
			cout.width(symNum);
			cout << "x";
			cout.width(symNum);
			cout << "f(x)";
			cout.width(symNum);
			cout << "f'c(x)";
			cout.width(symNum);
			cout << "|f'(x) - f'c(x)|";
			cout.width(symNum);
			cout << "f''c(x)" ;
			cout.width(symNum);
			cout << "|f''(x) - f''c(x)|";
			cout << endl << endl;

			for (int i = 0; i < nodeNumber; i++) {
				cout.width(symNum);
				cout << funcNodes[i];
				cout.width(symNum);
				cout << funcValues[i];
				cout.width(symNum);
				cout << derFuncValues_1[i];
				cout.width(symNum);
				cout << fabs(FuncClass::func(funcNodes[i], 1) - derFuncValues_1[i]);
				if ((i != 0) && (i != nodeNumber - 1)) {
					cout.width(symNum);
					cout << derFuncValues_2[i];
					cout.width(symNum);
					cout << fabs(FuncClass::func(funcNodes[i], 2) - derFuncValues_2[i]);
				} else {
					cout.width(symNum);
					cout << "CNBC";
					cout.width(symNum);
					cout << "CNBC";
				}
				cout << endl;
			}

			cout << endl << "CNBC - can't be calculated" << endl;
			cout << "f'c, f''c - calculated derivated function values" << endl;
		}

		~CalcDerivating() {
			if (funcNodes != 0)
				delete [] funcNodes;
			if (funcValues != 0)
				delete [] funcValues;
			if (derFuncValues_1 != 0)
				delete [] derFuncValues_1;
			if (derFuncValues_2 != 0)
				delete [] derFuncValues_2;
		}

	private:
		void der_1() {
			derFuncValues_1[0] = (-3 * funcValues[0] + 4 * funcValues[1] - funcValues[2]) / (2 * step);
			derFuncValues_1[nodeNumber - 1] =
				(3 * funcValues[nodeNumber - 1] - 4 * funcValues[nodeNumber - 2] + funcValues[nodeNumber -3])
				/ (2 * step);

			for (int i = 1; i < nodeNumber - 1; i++)
				derFuncValues_1[i] = (funcValues[i + 1] - funcValues[i - 1]) / (2 * step);
		}

		void der_2() {
			derFuncValues_2[0] = 0; // we don't can calculate these values
			derFuncValues_2[nodeNumber - 1] = 0;

			for (int i = 1; i < nodeNumber - 1; i++)
				derFuncValues_2[i] = (funcValues[i + 1] - 2 * funcValues[i] + funcValues[i - 1]) / (step * step);
		}

		double start;
		int nodeNumber;
		double step;

		double* funcNodes;
		double* funcValues;
		double* derFuncValues_1;
		double* derFuncValues_2;
};

int main() {
	cout << "Calculation methods of function derivating.\nPodkopaev Anton, SPbSU, 2011\n";
	cout << "f(x) = x^2 - sin(5x)\n\n";

	double start = 0;
	int nodeNumber = 10;
	double step = 0.1;

	cout << "Use default problem parameters? [Y/n] ";
	char useDefaultParameters = 'Y';
	cin >> useDefaultParameters;
	cout << endl;

	if (useDefaultParameters != 'Y') {
		cout << "Enter parameters\n***********" << endl;
		cout << "Start point: ";
		cin >> start;
		cout << "Last node number: ";
		cin >> nodeNumber;
		nodeNumber++; //for 0..nodeNumber
		cout << "Node step: ";
		cin >> step;
		cout << endl;
	}

	CalcDerivating<CurFunc> derivatingTest(start, nodeNumber, step);
	derivatingTest.printParameters();
	derivatingTest.print();
	return 0;
}
