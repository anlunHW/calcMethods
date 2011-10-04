#include "funcInterpolation.h"
#include <cmath>
#include <algorithm>

template <class FuncClass>
FuncInterpolation<FuncClass>::FuncInterpolation(bool isNeedToInitParams):
		leftBorder(0.4), rightBorder(0.9), interPoint(0.75), polinomDegree(7), nodeNumber(15 + 1),
		interNodes(0) {
	if (isNeedToInitParams)
		initParameters();

	interNodes = new double[nodeNumber];
	interNodes[0] = leftBorder;
	double step = (rightBorder - leftBorder) / (nodeNumber - 1);
	for (int i = 1; i < nodeNumber; i++)
		interNodes[i] = interNodes[i - 1] + step;

	//sort interNodes by a
	//sort(interNodes, less);
}

template<class FuncClass>
bool FuncInterpolation<FuncClass>::less(double left, double right) {
	return fabs(left - interPoint) < fabs(right - interPoint);
}

template <class FuncClass>
FuncInterpolation<FuncClass>::~FuncInterpolation() {
	if (interNodes)
		delete [] interNodes;
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
	cin >> polinomDegree;
	cout << "Enter approximation node number (m): ";
	cin >> nodeNumber;
	nodeNumber++; //cause nodeNumber is a number of nodes!
}

template <class FuncClass>
void FuncInterpolation<FuncClass>::printValueTable() {
	printValueTable(polinomDegree + 1);
}

template <class FuncClass>
void FuncInterpolation<FuncClass>::printValueTable(int nodeToPrintNumber) {
	using namespace std;
	cout << "Node-value table\n************" << endl;
	for (int i = 0; i < nodeToPrintNumber; i++) {
		cout << "n: " << interNodes[i] << endl;
		cout << "v: " << FuncClass::func(interNodes[i], 0) << endl;
		cout << endl;
	}
	cout << endl;
}

template <class FuncClass>
void FuncInterpolation<FuncClass>::lagrangeMethod() {
	using namespace std;
	cout << "Lagrange method" << endl;
}

template <class FuncClass>
void FuncInterpolation<FuncClass>::newtonMethod() {
	using namespace std;
	cout << "Newton method" << endl;
}
