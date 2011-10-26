#pragma once

#include <QList>
#include <QPair>
#include <QVector>
#include <QLinkedList>

#include <cmath>
#include <vector>

#include "mainwindow.h"
#include "interval.h"

class FuncClass {
	public:
		static double func(double x) {
			return sin(x);
		}

		static QString funcStr() {
			return "f(x) = sin(x)";
		}
};

class InverseFunctionInterpolation {
	public:
		static InverseFunctionInterpolation* createInterpolator(double startPoint, int nodeNumber, double nodeStep);

		double interpolateInverseFunction_1(double interPoint, int polynomDegree);
		double interpolateInverseFunction_2();

		~InverseFunctionInterpolation();

		QList< QPair<double, double> > nodeTable();
		QVector< QPair<double, double> > firstMethodTable();

		bool checkMonotony(int start, int end);
		bool checkMonotony(int start, int end, bool isGrowing);

		double startPoint() {
			return mStartPoint;
		}

		int nodeNumber() {
			return mNodeNumber;
		}

		double nodeStep() {
			return mNodeStep;
		}

		void setSecondMethodPolynomDegree(int newSMPD) {
			mSecondMethodPolynomDegree = newSMPD;
		}

		void setSecondMethodAccurancy(double newSMA) {
			mSecondMethodAccuracy = newSMA;
		}

		void setInterpolationValue(double newIV) {
			mInterpolationValue = newIV;
		}

		class CompareClass {
			public:
				CompareClass(double interPoint): interPoint(interPoint) {
				}

				bool operator() (QPair<double, double> left, QPair<double, double> right) {
					//compare
					return fabs(left.first - interPoint) < fabs(right.first - interPoint);
				}
			private:
				double interPoint;
		};

	private:
		InverseFunctionInterpolation(double mStartPoint, int mNodeNumber, double mNodeStep);
		double lagrangeOmega(double point, int degree, double* nodeArr);
		double interpolateFunction_equationFunc(double interPoint);
		double interpolateFunction(double interPoint, int polynomDegree);
		QLinkedList<Interval> rootDividing(double start, double end, double eps);
		double secantMethod(Interval const &interval, double eps);
		double bisectionMethod(Interval const &interval, double const &eps);

		double mStartPoint;
		int mNodeNumber;
		double mNodeStep;

		int mSecondMethodPolynomDegree;
		double mSecondMethodAccuracy;
		double mInterpolationValue;

		double* mNodes;
		double* mFuncValues;

		QVector< QPair<double, double> > mInverseValues;
};
