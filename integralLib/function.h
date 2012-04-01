#pragma once

#include <QString>
#include <cmath>

class Function {
	public:
		static double func(double x) {
			return sin(x) + x * x;
			//return sin(x);
		}

		static double funcIntegral(double x) {
			return -cos(x) + x * x * x / 3;
			//return -cos(x);
		}

		static QString funcString() {
			return "f(x) = sin(x) + x ^ 2";
			//return "f(x) = sin(x)";
		}
};
