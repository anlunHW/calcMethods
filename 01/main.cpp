#include <QLinkedList>
#include <cmath>

//#include "function.h"
#include "interval.h"

#include <iostream>

using namespace std;

const double minimumNotZero = 0.000000000000000000001;

//class CurFunc : public Function {
class CurFunc {
	public:
		static double func(double x) {
			return x * x - sin(5 * x);
		}

		static double derivatedFunc(double x) {
			return 2 * x - 5 * cos(5 * x);
		}
};

template <class FuncClass>
QLinkedList<Interval> rootDividing(double start, double end, double eps) {
	QLinkedList<Interval> result;
	
	if (start >= end) {
		return result;
	}

	double x1 = start;
	double x2 = start + eps < end ? start + eps : end;

	while (x2 <= end) {
		if (FuncClass::func(x1) * FuncClass::func(x2) < 0)
			result.push_back(Interval(x1, x2));
		x1 = x2;
		x2 += eps;
	}

	return result;
}

template <class FuncClass>
void bisectionMethod(Interval const &interval, double const &eps) {
	double left = interval.start();
	double right = interval.end();
	double middle = (right + left) / 2;

	int n = 0;

	while (abs(left - right) > 2 * eps) {
		if (FuncClass::func(left) * FuncClass::func(middle) > 0)
			left = middle;
		else
			right = middle;
		middle = (right + left) / 2;
		
		n++;
	}

	cout << "Bisection method\n";
	cout << "Step: " << n << "\n";
	cout << "Approximated solution: " << middle << "\n";
	cout << "Discrepansy module: " << abs(FuncClass::func(middle)) << "\n\n";
}

template <class FuncClass>
void newtonMethod(Interval const &interval, double const &eps) {
	double x = (interval.end() + interval.start()) / 2;
	double xOld = interval.start();
	int n = 0;
	
	do {
		xOld = x;

		double derivatedFuncValue = FuncClass::derivatedFunc(x);

		if (abs(derivatedFuncValue) > minimumNotZero) {
			x -= FuncClass::func(x) / derivatedFuncValue;
		} else {
			cout << derivatedFuncValue << "\n";
			cout << "Hmmm... problem in Newton Method. Trying to divide by smth, too close to zero.\n";	
			break;
		}

		n++;
	} while (abs(x - xOld) > eps);

	cout << "Newton method\n";
	cout << "Step: " << n << "\n";
	cout << "Approximated solution: " << x << "\n";
	cout << "Discrepansy module: " << abs(FuncClass::func(x)) << "\n\n";
}

template <class FuncClass>
void secantMethod(Interval const &interval, double const &eps) {
	double xOld_1 = interval.end();
	double xOld_2 = interval.start();
	double x = xOld_1;
	
	int n = 0;

	do {
		double temp = x;
		double funcDiff = FuncClass::func(xOld_1) - FuncClass::func(xOld_2);

		if (abs(funcDiff) > minimumNotZero) {
			x -= FuncClass::func(xOld_1) * (xOld_1 - xOld_2) / funcDiff;
		} else {
			cout << funcDiff << "\n";
			cout << "Hmmm... problem in secant Method. Trying to divide by smth, too close to zero.\n";	
			break;
		}

		xOld_2 = xOld_1;
		xOld_1 = temp;
		n++;
	} while (abs(x - xOld_1) > eps);

	cout << "Secant method\n";
	cout << "Step: " << n << "\n";
	cout << "Approximated solution: " << x << "\n";
	cout << "Discrepansy module: " << abs(FuncClass::func(x)) << "\n\n";
}

int main() {
	cout << "Methods of finding function roots.\nPodkopaev Anton, SPbSU, 2011\n\n";

	double A = -10;
	double B = 10;
	double eps = 0.000001;

	cout << "Enter interval\n";
	cout << "Left border: ";
	cin >> A;
	cout << "Right border: ";
	cin >> B;
	cout << "Enter accurancy: ";
	cin >> eps;

	double step = eps * 1000;

	QLinkedList<Interval> intervals = rootDividing<CurFunc>(A, B, step);
	int oldRootNumber = intervals.size();
	do {
		step /= 2;
		intervals = rootDividing<CurFunc>(A, B, step);
	} while((step > 2 * eps) && (oldRootNumber != intervals.size()));

	cin.get();
	foreach (Interval curInterval, intervals) {
		cout << "\n\t\t\tInterval: " << curInterval.toString().toStdString();
		bisectionMethod<CurFunc>(curInterval, eps);
		newtonMethod<CurFunc>(curInterval, eps);
		secantMethod<CurFunc>(curInterval, eps);
		cin.get();
	}

	return 0;
}
