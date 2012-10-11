#include "function.h"
#include "functionProduction.h"

Function::~Function() {
}

double Function::calculateIntegral(unsigned const intervalNumber, double const leftBorder, double const rightBorder) const {
	double intergralValue = 0;

	double step = (rightBorder - leftBorder) / intervalNumber;
	double curPoint = leftBorder;
	for (unsigned i = 0; i < intervalNumber; i++) {
		intergralValue += calculatePrimaryIntervalIntegral(curPoint, curPoint + step);
		curPoint += step;
	}

	return intergralValue;
}

//Simpson integral
double Function::calculatePrimaryIntervalIntegral(double const left, double const right) const {
	return (right - left) 
		* (func(left) + 4 * func((left + right) / 2) + func(right))
		/ 6;
}
