#pragma once

#include "integralCalc.h"

template <class FuncClass>
class SimpsonIntegralCalc: public IntegralCalc {
	public:
		SimpsonIntegralCalc(double leftBorder, double rightBorder):
			IntegralCalc(leftBorder, rightBorder) {
		}

		virtual ~SimpsonIntegralCalc() {
		}

		virtual int algebraicAccuracyDegree() {
			return 3;
		}

	protected:
		virtual double calculatePrimaryIntervalIntegral(double left, double right) {
			return (right - left)
					* (FuncClass::func(left) + 4 * FuncClass::func((left + right) / 2) + FuncClass::func(right))
					/ 6;
		}
};
