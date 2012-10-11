#pragma once

#include "function.h" 

class FixedIntervalFunction: public Function {
	public:
		FixedIntervalFunction(unsigned const intervalNumber, double const leftIntervalBorder, double const rigthIntervalBorder)
			: mIntervalNumber(intervalNumber)
			, mLeftIntervalBorder(leftIntervalBorder)
			, mRightIntervalBorder(rigthIntervalBorder)
		{
		}

		virtual double calculateIntegral() const {
			calculateIntegral(mLeftIntervalBorder, mRightIntervalBorder);
		}

	private:
		unsigned const mIntervalNumber;
		double const mLeftIntervalBorder;
		double const mRightIntervalBorder;
};
