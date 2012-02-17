#include <iostream>
#include <QString>
#include <cmath>
#include <iomanip>

#include <QDebug>

using namespace std;

class CurFunc {
	public:
		static double func(double x, int derivatedDegree) {
			if (derivatedDegree == 0) 
				return sin(x) + x * x;
			if (derivatedDegree == 1)
				return 2 * x - cos(x);
			if (derivatedDegree == 2)
				return 2 - sin(x);
			if (derivatedDegree > 2)
				return (((derivatedDegree - 1) % 4) < 2 ? -1 : 1) *
					(derivatedDegree % 2 ? cos(x): sin(x));

			return 1;
		}
};

template<class FuncClass>
class FuncInterpolation {
	public:
		enum InterpolationType {
			tableBegin, tableEnd, tableMiddle, other
		};

		~FuncInterpolation() {
			if (differenceTable != 0) {
				for (int i = 0; i < nodeNumber; i++)
					if (differenceTable[i] != 0)
						delete [] differenceTable[i];
				delete [] differenceTable;
			}
		}

		static FuncInterpolation<FuncClass>* createInterpolator() {
			double startPoint;
			int nodeNumber;
			double nodeStep;
			int polynomDegree;

			cout << "Enter interpolation parameters" << endl;
			cout << "Start point: ";
			cin >> startPoint;
			cout << "Last interpolation node number: ";
			cin >> nodeNumber;
			nodeNumber++;
			cout << "Interpolation node step: ";
			cin >> nodeStep;
			cout << "Polynom degree: ";
			cin >> polynomDegree;

			//determine a case of InterpolationType
			printValueTable(nodeNumber, startPoint, nodeStep);

			cout << "Method of interpolation: " << endl;
			cout << "1) in the beginning of the table" << endl;
			cout << "2) in the endding of the table" << endl;
			cout << "3) in the middle of the table" << endl;

			int interpolationMethod = 0;
			cout << "Choose one of them: ";
			cin >> interpolationMethod;
			cout << endl;

			InterpolationType interType = other;
			double interpolationPoint = 0;
			switch (interpolationMethod) {
				case 1: {
					interType = tableBegin;
					interpolationPoint = initInterpolationPoint(startPoint, startPoint + nodeStep);
					break;
				}

				case 2: {
					interType = tableEnd;
					interpolationPoint = initInterpolationPoint(startPoint + (nodeNumber - 2) * nodeStep,
							startPoint + (nodeNumber - 1) * nodeStep);
					break;
				}

				case 3: {
					interType = tableMiddle;
					//calculate borders
					double leftBorder = startPoint + int(polynomDegree / 2) * nodeStep;
					double rightBorder = startPoint +
						(nodeNumber - int((polynomDegree + 1) / 2) ) * nodeStep;
						//((nodeNumber - 1) - int((polynomDegree + 1) / 2) + 1) * nodeStep;
						//equals but easier to understand

					if (leftBorder > rightBorder)
						return 0;
					
					interpolationPoint = initInterpolationPoint(leftBorder, rightBorder);
					break;
				}

				default: {
					return 0;
				}
			}
			
			return new FuncInterpolation<FuncClass>(startPoint, nodeNumber, nodeStep, interpolationPoint,
				       	polynomDegree, interType);
		}

		void interpolate() {
			switch (interType) {
				case tableBegin: {
					interpolateTableBegin();
					break;
				}

				case tableEnd: {
					interpolateTableEnd();
					break;
				}
			
				case tableMiddle: {
					interpolateTableMiddle();
					break;
				}
				
				case other: {
					cout << "Sorry, I can't interpolate function in this point."\
						" It isn't case of interpolation in the beginning,"\
						" endding or middle of the table.";
					break;
				}
			}
		}

	protected:
		static double initInterpolationPoint(double leftBorder, double rightBorder) {
			cout << QString("Interpolation point. Because your choose"\
				" interpolation point must be between " + QString::number(leftBorder) + " and " +
				QString::number(rightBorder) + ".").toStdString() << endl;

			cout << "Enter value: ";
			while (true) {
				double interpolationPoint;
				cin >> interpolationPoint;

				if ((interpolationPoint >= leftBorder) && (interpolationPoint <= rightBorder))
					return interpolationPoint;

				cout << "Incorrect value. Reenter, please: ";
			}
		}

		static void printValueTable(int nodeToPrintNumber, double start, double step) {
			cout << "Node-value table\n***********" << endl;
			cout.width(25);
			cout << "Node";
			cout.width(25);
			cout << "Value";
			cout << endl;
			double curNode = start;
			for (int i = 0; i < nodeToPrintNumber; i++) {
				cout.width(25);
				cout << curNode;
				cout.width(25);
				cout << FuncClass::func(curNode, 0);
				cout << endl;
				curNode += step;
			}
			cout << endl;
		}

		FuncInterpolation(double startPoint, int nodeNumber, double nodeStep,
				double interpolationPoint, int polynomDegree,
				InterpolationType interType): startPoint(startPoint),
					nodeNumber(nodeNumber), nodeStep(nodeStep), interpolationPoint(interpolationPoint),
					polynomDegree(polynomDegree), interType(interType) {
			differenceTable = new double*[nodeNumber];
			for (int i = 0; i < nodeNumber; i++) {
				differenceTable[i] = new double[polynomDegree + 2];
			}

			//init differenceTable
			for (int i = 0; i < nodeNumber; i++) {
				differenceTable[i][0] = startPoint + nodeStep * i;
			}

			for (int i = 0; i < nodeNumber; i++) {
				differenceTable[i][1] = FuncClass::func(differenceTable[i][0], 0);
			}

			for (int j = 2; j < 2 + polynomDegree; j++)
				//for (int i = 0; i < polynomDegree - (j - 2); i++) {
				for (int i = 0; i < nodeNumber - (j - 1); i++) {
					differenceTable[i][j] = (differenceTable[i + 1][j - 1] - differenceTable[i][j - 1]);
				}

			printDifferenceTable();
		}

		void printDifferenceTable() {
			if (!differenceTable)
				return;

			cout << "Difference Table:\n";
			for (int i = 0; i < nodeNumber; i++) {
				for (int j = 0; j < polynomDegree + 2; j++) {
					cout.width(15);
					cout << differenceTable[i][j];
				}
				cout << endl;
			}
		}

		void interpolateTableBegin() {
			double t = (interpolationPoint - startPoint) / nodeStep;
			double result = differenceTable[0][1];
			double coef = 1;
			double fact = 1;
			for (int j = 2; j < 2 + polynomDegree; j++) {
				fact *= (j - 1);
				coef *= t - (j - 2);
				result += differenceTable[0][j] * coef / fact;
			}

			printResults(result, "beginning");
		}

		void interpolateTableEnd() {
			double endPoint = startPoint + (nodeNumber - 1) * nodeStep;
			//qDebug() << endPoint;

			double t = (interpolationPoint - endPoint) / nodeStep;
			double result = differenceTable[nodeNumber - 1][1];
			double coef = 1;
			double fact = 1;
			for (int j = 2; j < 2 + polynomDegree; j++) {
				fact *= (j - 1);
				coef *= t + (j - 2);
				result += differenceTable[nodeNumber - j][j] * coef / fact;
			}

			printResults(result, "endding");
		}

		void interpolateTableMiddle() {
			int middlePointNum = int ((interpolationPoint - startPoint) / nodeStep);
			double middlePoint = startPoint + middlePointNum * nodeStep;
			//qDebug() << "AAA" << middlePointNum;

			//double t = (interpolationPoint - middlePointNum) / nodeStep;
			double t = (interpolationPoint - middlePoint) / nodeStep;
			double result = differenceTable[middlePointNum][1];

			double coef = 1;
			double fact = 1;
			int sign = -1;
			for (int j = 2; j < 2 + polynomDegree; j++) {
				fact *= (j - 1);
				coef *= (t - sign * ((j - 1) / 2));
				sign *= -1;

				//result += differenceTable[middlePointNum - int(j / 2)][j] * coef / fact;
				result += differenceTable[middlePointNum - ((j - 1) / 2)][j] * coef / fact;
			}

			printResults(result, "middle");
		}

		void printResults(double result, QString type) {
			double trueValue = FuncClass::func(interpolationPoint, 0);
			cout << endl;
			cout << setprecision(20);
			cout << "Interpolation in the " + type.toStdString() + " on the table\n***********" << endl;
			cout << "Interpolation point: " << interpolationPoint << endl;
			cout << "Function value: " << trueValue << endl;
			cout << "Approximated solution: " << result << endl;
			cout << "Polynom degree: " << polynomDegree << endl;
			cout << "Disperancy module: " << fabs(result - trueValue) << endl;
		}

		double startPoint;
		int nodeNumber;
		double nodeStep;
		double interpolationPoint;
		int polynomDegree; //interpolation polynom degree

		InterpolationType interType;

		double** differenceTable;
};

int main() {
	cout << "Methods of algebraic interpolation.\nPodkopaev Anton, SPbSU, 2011\n";
	cout << "f(x) = sin(x) + x^2\n\n";

	FuncInterpolation<CurFunc>* interpolation = FuncInterpolation<CurFunc>::createInterpolator();
	if (interpolation == 0)
		return 0;

	interpolation->interpolate();
	delete interpolation;
	
	return 0;
}
