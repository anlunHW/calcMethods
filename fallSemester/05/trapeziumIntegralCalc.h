#pragma once

#include "integralCalc.h"

template <class FuncClass>
class TrapeziumIntegralCalc: public IntegralCalc {
	public:
		TrapeziumIntegralCalc(double leftBorder, double rightBorder):
			IntegralCalc(leftBorder, rightBorder) {
		}

		virtual ~TrapeziumIntegralCalc() {
		}

		virtual int algebraicAccuracyDegree() {
			return 1;
		}

	protected:
		virtual double calculatePrimaryIntervalIntegral(double left, double right) {
			return (right - left) * (FuncClass::func(left) + FuncClass::func(right)) / 2;
		}
};
