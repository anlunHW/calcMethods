#include <iostream>
#include "../matrixLib/linearSystem.h"

using namespace std;

//typedef double CurrentType;
typedef float CurrentType;

int main() {
	cout << "Linear equation systems. Gauss method.\nPodkopaev Anton, 345 group\n";
	
	
	CurrentType coefArr[] = {
		6.5126e-06, -8.0648e-03, 4.23528,
		5.9176e-03,    -0.80648, 1.46528,
		   0.87176,     0.79352, 0.91528
	};
	/*
	CurrentType coefArr[] = {
		1, 0.1,  0,
		0,   1,  0,
		0,   0,  1
	};
	*/

	Matrix<CurrentType> systemCoef(3, 3, coefArr);

	CurrentType constTermArr[] = {
		3.61628,
		1.52097,
		1.81150
	};
	/*
	CurrentType constTermArr[] = {
		1,
		2,
		3
	};
	*/

	Matrix<CurrentType> constTerm(3, 1, constTermArr);

	LinearSystem<CurrentType>* sys = LinearSystem<CurrentType>::createSystem(systemCoef, constTerm);
	
	//cout << (*sys);
	//cout << endl << endl;

	sys->gaussMethod();
	sys->gaussMethodWithChoosingInLine();

	if (sys)
		delete sys;

	return 0;
}
