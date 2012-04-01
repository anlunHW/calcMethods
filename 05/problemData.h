typedef double CurrentType;

/// K(x, y) from problem
CurrentType kernelFunc(CurrentType const x, CurrentType const y) {
	return exp(x * y) / 5;
}

/// Alpha from kernel replace method
/// corresponds with kernelFunc
CurrentType alpha(CurrentType const x, int const alphaNumber) {
	switch (alphaNumber) {
		case 1: {
				return 1;
			};

		case 2: {
				return x;
			};

		case 3: {
				return x * x;
			};

		case 4: {
				return x * x * x;
			};

		case 5: {
				return x * x * x * x;
			};
	}

	return 0;
}

/// Beta from kernel replace method
/// corresponds with kernelFunc
CurrentType beta(CurrentType const y, int const betaNumber) {
	switch (betaNumber) {
		case 1: {
				return 1 / 5.0;
			};

		case 2: {
				return y / 5.0;
			};

		case 3: {
				return y * y / 10.0;
			};

		case 4: {
				return y * y * y / 30.0;
			};

		case 5: {
				return y * y * y * y / 120.0;
			};
	}

	return 0;
}

/// f(x) from problem
CurrentType rightSideFunc(CurrentType const x) {
	return 1 - x * x;
}

/// a from problem
CurrentType const intervalLeftBorder = 0;

/// b from problem
CurrentType const intervalRightBorder = 1;

/// N from problem
int const nodeNumber = 10;

