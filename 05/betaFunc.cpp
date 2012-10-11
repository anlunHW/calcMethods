#include "betaFunc.h"

Function* BetaFunc::createFunctionByNumber(unsigned const funcNumber) {
	switch (funcNumber) {
		case 1:
			return new BetaFunc1();
		case 2:
			return new BetaFunc2();
		case 3:
			return new BetaFunc3();
		case 4:
			return new BetaFunc4();
		case 5:
			return new BetaFunc5();
		default:
			return new BetaFunc(); // default value
	}
}
