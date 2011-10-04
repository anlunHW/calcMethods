#pragma once

template <class FuncClass>
class FuncInterpolation {
	public:
		FuncInterpolation(bool isNeedToInitParams = false);
		~FuncInterpolation();

		void printValueTable();

		void lagrangeMethod();
		void newtonMethod();

	private:
		void initParameters();
		bool less(double left, double right);
		void printValueTable(int nodeToPrintNumber);

		double leftBorder; //left interval border
		double rightBorder; //right interval border
		double interPoint; //interpolation point
		int polinomDegree; //approximation polinom degree
		int nodeNumber; //approximation node number

		double* interNodes;
};

#include "funcInterpolation.tcc"
