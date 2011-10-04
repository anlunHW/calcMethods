#include <iostream>

#include "funcInterpolation.h"

using namespace std;

const double minimumNotZero = 0.000000000000000000001;

//class CurFunc : public Function {
class CurFunc {
	public:
		static double func(double x, int derivatedDegree) {
			if (derivatedDegree == 0) 
				return sin(x) + x * x;
			if (derivatedDegree == 1)
				return 2 * x - cos(x);
			if (derivatedDegree == 2)
				return 2 - sin(x);
			if (derivatedDegree > 2)
				return (((derivatedDegree - 1) % 4) < 2 ? -1 : 1) *
					(derivatedDegree % 2 ? cos(x): sin(x));

			return 1;
		}
};

int main() {
	cout << "Methods of algebraic interpolation.\nPodkopaev Anton, SPbSU, 2011\n";
	cout << "f(x) = sin(x) + x^2\n\n";
	
	FuncInterpolation<CurFunc> interpolation;
	interpolation.printValueTable();
	interpolation.lagrangeMethod();
	interpolation.newtonMethod();

	return 0;
}
