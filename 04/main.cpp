#include <iostream>
#include <cmath>
#include "../matrixLib/linearSystem.h"

using namespace std;

typedef double CurrentType;

/// K(x, y) from problem
CurrentType kernelFunc(CurrentType x, CurrentType y) {
	return exp(x * y) / 5;
}

/// f(x) from problem
CurrentType rightSideFunc(CurrentType x) {
	return 1 - x * x;
}

/// a from problem
CurrentType const intervalLeftBorder = 0;

/// b from problem
CurrentType const intervalRightBorder = 1;

/// N from problem
int const nodeNumber = 10;

int main() {
	return 0;
}
