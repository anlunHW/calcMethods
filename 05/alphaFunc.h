#pragma once

#include "../integralLib/function.h"

/// Alpha from kernel replace method
/// corresponds with kernelFunc
class AlphaFunc: public Function {
	public:
		double func(double const x) const  {
			return 0;
		}

		static Function* createFunctionByNumber(unsigned const funcNumber);
};

class AlphaFunc1: public Function {
	public:
		double func(double const x) const  {
			return 1;
		}
};

class AlphaFunc2: public Function {
	public:
		double func(double const x) const  {
			return x;
		}
};

class AlphaFunc3: public Function {
	public:
		double func(double const x) const  {
			return x * x;
		}
};

class AlphaFunc4: public Function {
	public:
		double func(double const x) const  {
			return x * x * x;
		}
};

class AlphaFunc5: public Function {
	public:
		double func(double const x) const  {
			return x * x * x * x;
		}
};

