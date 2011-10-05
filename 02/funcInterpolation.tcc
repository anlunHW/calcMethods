#include "funcInterpolation.h"
#include <algorithm>
#include <iomanip>

template <class FuncClass>
FuncInterpolation<FuncClass>::FuncInterpolation(bool isNeedToInitParams):
		leftBorder(0.4), rightBorder(0.9), interPoint(0.75), polynomDegree(7), nodeNumber(15 + 1),
		interPointFuncValue(0),
		interNodes(0), interNodeValue(0)  {
	using namespace std;
	if (isNeedToInitParams)
		initParameters();
	else
		printParameters();

	interNodes = new vector<double>(nodeNumber);
	interNodes->at(0) = leftBorder;
	double step = (rightBorder - leftBorder) / (nodeNumber - 1);
	for (int i = 1; i < nodeNumber; i++)
		interNodes->at(i) = interNodes->at(i - 1) + step;
	
	interNodeValue = new vector<double>(nodeNumber);
	for (int i = 0; i < nodeNumber; i++)
		interNodeValue->at(i) = FuncClass::func(interNodes->at(i), 0);

	printValueTable(nodeNumber);

	//sort interNodes by a
	CompareClass comparator(interPoint);
	sort(interNodes->begin(), interNodes->end(), comparator);
	
	for (int i = 0; i < nodeNumber; i++)
		interNodeValue->at(i) = FuncClass::func(interNodes->at(i), 0);

	interPointFuncValue = FuncClass::func(interPoint, 0);
}

template <class FuncClass>
FuncInterpolation<FuncClass>::~FuncInterpolation() {
	if (interNodes)
		delete interNodes;
	if (interNodeValue)
		delete interNodeValue;
}

template <class FuncClass>
void FuncInterpolation<FuncClass>::initParameters() {
	using namespace std;

	cout << "Enter interval\n";
	cout << "Left border (a): ";
	cin >> leftBorder;
	cout << "Right border (b): ";
	cin >> rightBorder;
	cout << "Enter interpolation point (y): ";
	cin >> interPoint;
	cout << "Enter interpolation polinom degree (n): ";
	cin >> polynomDegree;
	cout << "Enter interpolation node number (m): ";
	cin >> nodeNumber;
	nodeNumber++; //cause nodeNumber is a number of nodes!

	cout << endl;
}

template <class FuncClass>
void FuncInterpolation<FuncClass>::printParameters() {
	using namespace std;

	cout << "Problem parameters\n***********" << endl;
	cout << "Interval left border (a): " << leftBorder << endl;
	cout << "Interval right border (b): " << rightBorder << endl;
	cout << "Interpolation point (y): " << interPoint << endl;
	cout << "Interpolation polinom degree (n): " << polynomDegree << endl;
	cout << "Interpolation node number (m): " << nodeNumber - 1 << endl;

	cout << endl;
}

template <class FuncClass>
void FuncInterpolation<FuncClass>::printValueTable() {
	using namespace std;

	cout << "Print entire point-value table for (a) to (b) or only for (m + 1) nearest points? [E/n] ";
	char printEntireTable = 'n';
	cin >> printEntireTable;

	if (printEntireTable != 'E')	
		printValueTable(polynomDegree + 1);
	else
		printValueTable(nodeNumber);
}

template <class FuncClass>
void FuncInterpolation<FuncClass>::printValueTable(int nodeToPrintNumber) {
	using namespace std;
	cout << "Node-value table\n***********" << endl;
	cout.width(25);
	cout << "Node";
	cout.width(25);
	cout << "Value";
	cout << endl;
	for (int i = 0; i < nodeToPrintNumber; i++) {
		cout.width(25);
		cout << interNodes->at(i);
		cout.width(25);
		cout << interNodeValue->at(i) << endl;
		//cout << endl;
	}
	cout << endl;
}

template <class FuncClass>
void FuncInterpolation<FuncClass>::lagrangeMethod() {
	using namespace std;
	cout << "Lagrange method" << endl;

	double result = lagrangePolynom(interPoint, polynomDegree);
	cout << setprecision(20);
	cout << "Interpolation point: " << interPoint << endl;
	cout << "Function value: " << interPointFuncValue << endl;
	cout << "Approximated solution: " << result << endl;
	cout << "Polynom degree: " << polynomDegree << endl;
	cout << "Disperancy module: " << fabs(result - interPointFuncValue)<< endl;

	cout << endl << endl;
}

template <class FuncClass>
double FuncInterpolation<FuncClass>::lagrangePolynom(double point, int degree) {
	if (degree <= 0)
		return interNodeValue->at(0);
	return lagrangePolynom(point, degree - 1)
		+ (interNodeValue->at(degree) - lagrangePolynom(interNodes->at(degree), degree - 1))
		* lagrangeOmega(point, degree) / lagrangeOmega(interNodes->at(degree), degree);
}

template <class FuncClass>
double FuncInterpolation<FuncClass>::lagrangeOmega(double point, int degree) {
	if (degree <= 1)
		return point - interNodes->at(0);
	return lagrangeOmega(point, degree - 1) * (point - interNodes->at(degree - 1));
}

template <class FuncClass>
void FuncInterpolation<FuncClass>::newtonMethod() {
	using namespace std;
	cout << "Newton method" << endl;

	double differenceTable[polynomDegree + 1][2 + polynomDegree];
	for (int i = 0; i < polynomDegree + 1; i++) {
		differenceTable[i][0] = interNodes->at(i);
	}
	for (int i = 0; i < polynomDegree + 1; i++) {
		differenceTable[i][1] = interNodeValue->at(i);
	}

	for (int j = 2; j < 2 + polynomDegree; j++)
		for (int i = 0; i < polynomDegree - (j - 2); i++) {
			differenceTable[i][j] = (differenceTable[i + 1][j - 1] - differenceTable[i][j - 1])
				/ (interNodes->at((j - 2) + i + 1) - interNodes->at(i));
		}

	double result = interNodeValue->at(0);
	for (int i = 2; i < 2 + polynomDegree; i++)
		result += differenceTable[0][i] * lagrangeOmega(interPoint, i - 1);

	cout << setprecision(20);
	cout << "Interpolation point: " << interPoint << endl;
	cout << "Function value: " << interPointFuncValue << endl;
	cout << "Approximated solution: " << result << endl;
	cout << "Polynom degree: " << polynomDegree << endl;
	cout << "Disperancy module: " << fabs(result - interPointFuncValue)<< endl;

	cout << endl << endl;
}
