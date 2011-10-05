#pragma once

#include <vector>
#include <cmath>

template <class FuncClass>
class FuncInterpolation {
	public:
		FuncInterpolation(bool isNeedToInitParams = false);
		~FuncInterpolation();

		void printValueTable();

		void lagrangeMethod();
		void newtonMethod();
		
		class CompareClass {
			public:
				CompareClass(double interPoint): interPoint(interPoint) {
				}

				bool operator() (double left, double right) {
					//compare
					return fabs(left - interPoint) < fabs(right - interPoint);
				}
			private:
				double interPoint;
		};

	private:
		void initParameters();
		void printValueTable(int nodeToPrintNumber);
		void printParameters();

		double lagrangePolynom(double point, int degree);
		double lagrangeOmega(double point, int degree);

		double leftBorder; //left interval border
		double rightBorder; //right interval border
		double interPoint; //interpolation point
		int polynomDegree; //approximation polinom degree
		int nodeNumber; //approximation node number

		double interPointFuncValue;

		std::vector<double> *interNodes;
		std::vector<double> *interNodeValue;
};

#include "funcInterpolation.tcc"
