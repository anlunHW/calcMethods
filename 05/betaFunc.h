#pragma once

#include "../integralLib/function.h"

/// Beta from kernel replace method
/// corresponds with kernelFunc
class BetaFunc : public Function {
	public:
		double func(double const x) const  {
			return 0;
		}

		static Function* createFunctionByNumber(unsigned const funcNumber);
};

class BetaFunc1: public Function {
	public:
		double func(double const x) const  {
			return 1 / 5.0;
		}
};

class BetaFunc2: public Function {
	public:
		double func(double const x) const  {
			return x / 5.0;
		}
};

class BetaFunc3: public Function {
	public:
		double func(double const x) const  {
			return x * x / 10.0;
		}
};

class BetaFunc4: public Function {
	public:
		double func(double const x) const  {
			return x * x * x / 30.0;
		}
};

class BetaFunc5: public Function {
	public:
		double func(double const x) const  {
			return x * x * x * x / 120.0;
		}
};
