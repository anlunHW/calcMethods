#include "inverseFunctionInterpolation.h"
#include "interval.h"

#include <QtAlgorithms>
#include <QDebug>

using namespace std;

InverseFunctionInterpolation* InverseFunctionInterpolation::createInterpolator(double startPoint, int nodeNumber, double nodeStep) {
	if (nodeNumber < 1)
		return 0;

	if (nodeStep < 0)
		return 0;

	return new InverseFunctionInterpolation(startPoint, nodeNumber, nodeStep);
}

InverseFunctionInterpolation::~InverseFunctionInterpolation() {
	if (mNodes)
		delete mNodes;
	if (mFuncValues)
		delete mFuncValues;
}

InverseFunctionInterpolation::InverseFunctionInterpolation(double startPoint, int nodeNumber, double nodeStep):
		mStartPoint(startPoint), mNodeNumber(nodeNumber), mNodeStep(nodeStep) {
	mNodes = new double[nodeNumber];
	for (int i = 0; i < nodeNumber; i++)
		mNodes[i] = startPoint + i * nodeStep;

	mFuncValues = new double[nodeNumber];
	for (int i = 0; i < nodeNumber; i++)
		mFuncValues[i] = FuncClass::func(mNodes[i]);
}

bool InverseFunctionInterpolation::checkMonotony(int start, int end) {
	return checkMonotony(start, end, mFuncValues[start] < mFuncValues[start + 1]);
}

bool InverseFunctionInterpolation::checkMonotony(int start, int end, bool isGrowing) {
	for (int i = start; (i < end - 1) && (i < mNodeNumber - 1); i++)
		if ((mFuncValues[i] == mFuncValues[i + 1]) ||
				!((mFuncValues[i] > mFuncValues[i + 1]) ^ isGrowing))
			return false;

	return true;
}

QList< QPair<double, double> > InverseFunctionInterpolation::nodeTable() {
	QList< QPair<double, double> > result;

	if ((mNodes == 0) || (mFuncValues == 0))
		return result;

	for (int i = 0; i < mNodeNumber; i++)
		result.append(QPair<double, double>(mNodes[i], mFuncValues[i]));

	return result;
}

QVector< QPair<double, double> > InverseFunctionInterpolation::firstMethodTable() {
	return mInverseValues;
}

double InverseFunctionInterpolation::interpolateInverseFunction_1(double interPoint, int polynomDegree) {
	mInverseValues.clear();
	for (int i = 0; i < mNodeNumber; i++)
		mInverseValues.push_back(QPair<double, double>(mFuncValues[i], mNodes[i]));
	qSort(mInverseValues.begin(), mInverseValues.end(), CompareClass(interPoint));

	double differenceTable[polynomDegree + 1][2 + polynomDegree];
	for (int i = 0; i < polynomDegree + 1; i++) {
		differenceTable[i][0] = mInverseValues[i].first;
	}
	for (int i = 0; i < polynomDegree + 1; i++) {
		differenceTable[i][1] = mInverseValues[i].second;
	}

	for (int j = 2; j < 2 + polynomDegree; j++)
		for (int i = 0; i < polynomDegree - (j - 2); i++) {
			differenceTable[i][j] = (differenceTable[i + 1][j - 1] - differenceTable[i][j - 1])
				/ (mInverseValues[(j - 2) + i + 1].first - mInverseValues[i].first);
		}

	double result = mInverseValues[0].second;
	for (int i = 2; i < 2 + polynomDegree; i++)
		result += differenceTable[0][i] * lagrangeOmega(interPoint, i - 1, mInverseValues[0].first);

	return result;
}

double InverseFunctionInterpolation::lagrangeOmega(double point, int degree, double interFirstNode) {
	if (degree <= 1)
		return point - interFirstNode;
	return lagrangeOmega(point, degree - 1, interFirstNode) * (point - interFirstNode);
}

double InverseFunctionInterpolation::interpolateFunction_equationFunc(double interPoint) {
	return interpolateFunction(interPoint, mSecondMethodPolynomDegree) - mInterpolationValue;
}

double InverseFunctionInterpolation::interpolateFunction(double interPoint, int polynomDegree) {
	QVector< QPair<double, double> > curInterpolationNodes;
	for (int i = 0; i < mNodeNumber; i++)
		curInterpolationNodes.push_back(QPair<double, double>(mNodes[i], mFuncValues[i]));
	qSort(curInterpolationNodes.begin(), curInterpolationNodes.end(), CompareClass(interPoint));

	double differenceTable[polynomDegree + 1][2 + polynomDegree];
	for (int i = 0; i < polynomDegree + 1; i++) {
		differenceTable[i][0] = curInterpolationNodes[i].first;
	}
	for (int i = 0; i < polynomDegree + 1; i++) {
		differenceTable[i][1] = curInterpolationNodes[i].second;
	}

	for (int j = 2; j < 2 + polynomDegree; j++)
		for (int i = 0; i < polynomDegree - (j - 2); i++) {
			differenceTable[i][j] = (differenceTable[i + 1][j - 1] - differenceTable[i][j - 1])
				/ (curInterpolationNodes[(j - 2) + i + 1].first - curInterpolationNodes[i].first);
		}

	double result = curInterpolationNodes[0].second;
	for (int i = 2; i < 2 + polynomDegree; i++)
		result += differenceTable[0][i] * lagrangeOmega(interPoint, i - 1, curInterpolationNodes[0].first);

	return result;
}

double InverseFunctionInterpolation::interpolateInverseFunction_2() {
	QLinkedList<Interval> intervals = rootDividing(mStartPoint, mStartPoint + mNodeNumber * mNodeStep, 2 * mSecondMethodAccuracy);

	QLinkedList<double> result;
	foreach (Interval curInterval, intervals) {
		result.append(secantMethod(curInterval, mSecondMethodAccuracy));
	}

	return result.first();
}

double InverseFunctionInterpolation::secantMethod(Interval const &interval, double eps) {
	double minimumNotZero = 0.000000000000000000001;

	double xOld_1 = interval.end();
	double xOld_2 = interval.start();

	double x = xOld_1;

	int n = 0;
	do {
		double temp = x;
		double funcDiff = interpolateFunction_equationFunc(xOld_1) - interpolateFunction_equationFunc(xOld_2);

		if (abs(funcDiff) > minimumNotZero) {
			x -= interpolateFunction_equationFunc(xOld_1) * (xOld_1 - xOld_2) / funcDiff;
		} else {
			qDebug() << funcDiff << "\n";
			qDebug() << "Hmmm... problem in secant Method. Trying to divide by smth, too close to zero.\n";
			break;
		}

		xOld_2 = xOld_1;
		xOld_1 = temp;
		n++;
	} while (abs(x - xOld_1) > eps);

	return x;
}

QLinkedList<Interval> InverseFunctionInterpolation::rootDividing(double start, double end, double eps) {
	QLinkedList<Interval> result;

	if (start >= end) {
		return result;
	}

	double x1 = start;
	double x2 = start + eps < end ? start + eps : end;

	while (x2 <= end) {
		if (interpolateFunction_equationFunc(x1) * interpolateFunction_equationFunc(x2) < 0)
			result.push_back(Interval(x1, x2));
		x1 = x2;
		x2 += eps;
	}

	return result;
}
