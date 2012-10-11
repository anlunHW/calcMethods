#pragma once

#include "function.h"

class FunctionProduction: public Function {
	public:
		FunctionProduction(Function const * const f1, Function const * const f2)
			: mFunction1(f1), mFunction2(f2)
		{
		}

		virtual double func(double const x) const {
			return mFunction1->func(x) * mFunction2->func(x);
		}

	private:
		Function const * const mFunction1;
		Function const * const mFunction2;
};

