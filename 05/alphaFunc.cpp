#include "alphaFunc.h"

Function* AlphaFunc::createFunctionByNumber(unsigned const funcNumber) {
	switch (funcNumber) {
		case 1:
			return new AlphaFunc1();
		case 2:
			return new AlphaFunc2();
		case 3:
			return new AlphaFunc3();
		case 4:
			return new AlphaFunc4();
		case 5:
			return new AlphaFunc5();
		default:
			return new AlphaFunc(); // default value
	}
}

