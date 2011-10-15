#include <iostream>

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
class InverseFunctionInterpolation {
	public:
		static InverseFunctionInterpolation* createInterpolator() {
			if (nodeNumber < 1)
				return 0;

			if (nodeStep < 0)
				return 0;

			return new InverseFunctionInterpolation(startPoint, nodeNumber, nodeStep);
		}

		void approximateInverseFunction(double )

		~InverseFunctionInterpolation() {
			if (nodes)
				delete nodes;
			if (funcValues)
				delete funcValues;
		}

	private:
		InverseFunctionInterpolation(double startPoint, int nodeNumber, double nodeStep): startPoint(startPoint),
				nodeNumber(nodeNumber), nodeStep(nodeStep) {
			nodes = new double[nodeNumber];
			for (int i = 0; i < nodeNumber; i++)
				nodes[i] = startPoint + i * nodeStep;

			funcValues = new double[nodeNumber];
			for (int i = 0; i < nodeNumber; i++)
				funcValues[i] = FuncClass::func(nodes[i], 0);
		}
	
		bool checkMonotony(int start, int end, bool isGrowing) {
			for (int i = start; (i < end) && (i < nodeNumber - 1); i++)
				if ((funcValues[i] == funcValues[i + 1]) ||
						((funcValues[i] > funcValues[i + 1]) ^ isGrowing))
					return false;
			return true;
		}

		double startPoint;
		int nodeNumber;
		double nodeStep;

		double* nodes;
		double* funcValues;
};

int main() {
	cout << "Methods of algebraic interpolarion inverse function.\nPodkopaev Anton, SPbSU, 2011\n";
	cout << "f(x) = sin(x) + x^2\n\n";

	double start = 0;
	int nodeNumber = 10;
	double step = 0.1;
	double interPoint = 10;

	cout << "Use default problem parameters? [Y/n] ";
	char useDefaultParameters = 'Y';
	cin >> useDefaultParameters;
	cout << endl;

	if (useDefaultParameters != 'Y') {
		cout << "Enter parameters\n***********" << endl;
		cout << "Start point: ";
		cin >> start;
		cout << "Last node number: ";
		cin >> nodeNumber;
		nodeNumber++; //for 0..nodeNumber
		cout << "Node step: ";
		cin >> step;
		cout << endl;
	}

	return 0;
}
