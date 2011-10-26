#pragma once

#include "integralCalc.h"

template <class FuncClass>
class MiddleRectangleIntegralCalc: public IntegralCalc {
	public:
		MiddleRectangleIntegralCalc(double leftBorder, double rightBorder):
			IntegralCalc(leftBorder, rightBorder) {
		}

		virtual ~MiddleRectangleIntegralCalc() {
		}

		virtual int algebraicAccuracyDegree() {
			return 1;
		}

	protected:
		virtual double calculatePrimaryIntervalIntegral(double left, double right) {
			return (right - left) * FuncClass::func((left + right) / 2);
		}
};
