#include "funcInterpolation.h"
#include <algorithm>
#include <iomanip>

template <class FuncClass>
FuncInterpolation<FuncClass>::FuncInterpolation(bool isNeedToInitParams):
		leftBorder(0.4), rightBorder(0.9), interPoint(0.75), polynomDegree(7), nodeNumber(15 + 1),
		interNodes(0), interNodeValue(0) {
	using namespace std;
	if (isNeedToInitParams)
		initParameters();

	interNodes = new vector<double>(nodeNumber);
	interNodes->at(0) = leftBorder;
	double step = (rightBorder - leftBorder) / (nodeNumber - 1);
	for (int i = 1; i < nodeNumber; i++)
		interNodes->at(i) = interNodes->at(i - 1) + step;

	//sort interNodes by a
	CompareClass comparator(interPoint);
	sort(interNodes->begin(), interNodes->end(), comparator);

	interNodeValue = new vector<double>(polynomDegree + 1);
	for (int i = 0; i < polynomDegree + 1; i++)
		interNodeValue->at(i) = FuncClass::func(interNodes->at(i), 0);
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
	cout << "Enter approximation node number (m): ";
	cin >> nodeNumber;
	nodeNumber++; //cause nodeNumber is a number of nodes!
}

template <class FuncClass>
void FuncInterpolation<FuncClass>::printValueTable() {
	printValueTable(polynomDegree + 1);
}

template <class FuncClass>
void FuncInterpolation<FuncClass>::printValueTable(int nodeToPrintNumber) {
	using namespace std;
	cout << "Node-value table\n************" << endl;
	for (int i = 0; i < nodeToPrintNumber; i++) {
		cout << "n: " << interNodes->at(i) << endl;
		cout << "v: " << interNodeValue->at(i) << endl;
		cout << endl;
	}
	cout << endl;
}

template <class FuncClass>
void FuncInterpolation<FuncClass>::lagrangeMethod() {
	using namespace std;
	cout << "Lagrange method" << endl;

	double result = lagrangePolynom(interPoint, polynomDegree);
	cout << setprecision(20);
	cout << "Function value: " << FuncClass::func(interPoint, 0) << endl;
	cout << "Approximated solution: " << result << endl;
	cout << "Disperancy module: " << fabs(result - FuncClass::func(interPoint, 0))<< endl;
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
}
