#include "alphaFunc.h"
#include "betaFunc.h"

/// K(x, y) from problem
class KernelFunc {
	public:
		static double func(double const x, double const y) {
			return exp(x * y) / 5;
		}
};

/// f(x) from problem
class RightSideFunc {
	public:
		static double func(double const x) {
			return 1 - x * x;
		}
};

/// a from problem
double const intervalLeftBorder = 0;

/// b from problem
double const intervalRightBorder = 1;

/// N from problem
int const nodeNumber = 10;

