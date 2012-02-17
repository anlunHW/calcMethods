#pragma once

#include <cmath>

class IntegralCalc {
	public:
		IntegralCalc(double leftBorder, double rightBorder):
				leftBorder(leftBorder), rightBorder(rightBorder) {
		}

		virtual ~IntegralCalc() {
		}

		virtual int algebraicAccuracyDegree() = 0;

		double calculateIntegral(int intervalNumber) {
			double intergralValue = 0;

			double step = (rightBorder - leftBorder) / intervalNumber;
			double curPoint = leftBorder;
			for (int i = 0; i < intervalNumber; i++) {
				intergralValue += calculatePrimaryIntervalIntegral(curPoint, curPoint + step);
				curPoint += step;
			}

			return intergralValue;
		}

		double mainCalcError(int intervalNumber, int intervalNumberCoef) {
			double result = calculateIntegral(intervalNumber * intervalNumberCoef)
					- calculateIntegral(intervalNumber);
			result /= pow(intervalNumberCoef, algebraicAccuracyDegree() + 1) - 1;
			return result;
		}

	protected:
		virtual double calculatePrimaryIntervalIntegral(double left, double right) = 0;

		double leftBorder;
		double rightBorder;
};

