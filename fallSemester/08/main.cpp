#include <iostream>
#include <cmath>

using namespace std;

double solution(double x) {
	return (exp(2 * x) - 1) / (exp(2 * x) + 1);
}

//f(x, y)
double f(double y) {
	return 1 - y * y;
}

class Problem {
	public:
		Problem() {
			x0 = 0;
			h = 0.1;
			N = 10;

			printWidth = 25;
		
			//до 9 производной
			taylorCoefNumber = 9 + 1;
			taylorCoefs = new double[taylorCoefNumber];

			double diffInStartPointValues[] = {0, 1, 0, -2, 0, 16, 0, -272, 0, 7936};
			int curFact = 1;
			for (int i = 0; i < taylorCoefNumber; i++) {
				curFact = i > 0 ? curFact * i: 1;
				taylorCoefs[i] = diffInStartPointValues[i] / curFact;
			}
		};

		~Problem() {
			delete taylorCoefs;
		}

		void print() {
			cout << "Вычислительный практикум." << endl;
			cout << "Задача №8." << endl;
			cout << "Численное решение задачи Коши для обыкновенного";
			cout << "диффиренциального уравнения первого порядка." << endl;
			cout << "Подкопаев Антон, 345 группа." << endl << endl;

			cout << "Условие задачи Коши:" << endl;
			cout << "y'(x) = -y^2(x) + 1, y(0) = 0" << endl << endl;

			cout << "Параметры задачи:" << endl;
			cout << "h: " << h << endl;
			cout << "N: " << N << endl;
			cout << endl;

			cout << "Точное решение:" << endl;
			cout << "y(x) = (e^(2x) - 1) / (e^(2x) + 1)" << endl;
			cout << endl;

			cout << "Таблица значений точного решения:" << endl;

			cout.width(printWidth);
			cout << "x";
			cout.width(printWidth);
			cout << "f(x)";
			cout << endl << endl;
			for (int k = -2; k <= N; k++) {
				cout.width(printWidth);
				cout << x0 + k * h;
				cout.width(printWidth);
				cout << solution(x0 + k * h);
				cout << endl;
			}

			cout << endl;	
			cout << "Формула Тейлора:" << endl;

			cout.width(printWidth);
			cout << "x";
			cout.width(printWidth);
			cout << "Тейлор";
			cout.width(printWidth);
			cout << "Погрешность";
			cout << endl << endl;

			for (int k = -2; k <= 2; k++) {
				double curPoint = x0 + k * h;
				double taylorValue = 0;

				// разность между текущей и начальной точками
				// в степени i
				double pointCoef = 1;

				for (int i = 0; i < taylorCoefNumber; i++) {
					taylorValue += taylorCoefs[i] * pointCoef;
					pointCoef *= k * h;
				}

				cout.width(printWidth);
				cout << curPoint;
				cout.width(printWidth);
				cout << taylorValue;
				cout.width(printWidth);
				cout << fabs(taylorValue - solution(curPoint));
				cout << endl;
			}

			cout << endl;
			printEuler();

			cout << endl;
			printBetterEuler();

			cout << endl;
			printCaushyEuler();

			cout << endl;
			printRungeKutta();

			cout << endl;
			printAdams();
		}

	private:
		void printEuler() {
			cout << "Метод Эйлера:" << endl;
			cout.width(printWidth);
			cout << "x";
			cout.width(printWidth);
			cout << "f(x)";
			cout.width(printWidth);
			cout << "Погрешность";
			cout << endl << endl;

			double curY = 0;
			for (int k = 1; k <= N; k++) {
				curY += h * f(curY);

				cout.width(printWidth);
				cout << x0 + k * h;
				cout.width(printWidth);
				cout << curY;
				cout.width(printWidth);
				cout << fabs(curY - solution(x0 + k * h));
				cout << endl;
			}
		}
		
		void printBetterEuler() {
			cout << "Усовершенствованный метод Эйлера:" << endl;
			cout.width(printWidth);
			cout << "x";
			cout.width(printWidth);
			cout << "f(x)";
			cout.width(printWidth);
			cout << "Погрешность";
			cout << endl << endl;

			double curY = 0;
			double curY_H_2 = 0;
			for (int k = 1; k <= N; k++) {
				curY_H_2 = curY + f(curY_H_2) * h / 2;
				curY += h * f(curY_H_2);

				cout.width(printWidth);
				cout << x0 + k * h;
				cout.width(printWidth);
				cout << curY;
				cout.width(printWidth);
				cout << fabs(curY - solution(x0 + k * h));
				cout << endl;
			}
		}

		void printCaushyEuler() {
			cout << "Метод Эйлера-Коши:" << endl;
			cout.width(printWidth);
			cout << "x";
			cout.width(printWidth);
			cout << "f(x)";
			cout.width(printWidth);
			cout << "Погрешность";
			cout << endl << endl;

			//double prevY = 0;
			double curY = 0; // Из метода улучшенного Эйлера
			double curY_H_2 = 0;
			
			double yK = 0;

			for (int k = 1; k <= N; k++) {
				curY_H_2 = curY + f(curY_H_2) * h / 2;
				curY += h * f(curY_H_2);
				
				yK += (f(yK) + f(curY)) * h / 2;

				//prevY = curY;

				cout.width(printWidth);
				cout << x0 + k * h;
				cout.width(printWidth);
				cout << yK;
				cout.width(printWidth);
				cout << fabs(yK - solution(x0 + k * h));
				cout << endl;
			}
		}

		void printRungeKutta() {
			cout << "Метод Рунге-Кутта четвертого порядка:" << endl;
			cout.width(printWidth);
			cout << "x";
			cout.width(printWidth);
			cout << "f(x)";
			cout.width(printWidth);
			cout << "Погрешность";
			cout << endl << endl;

			double curY = 0;
			//double curY_H_2 = 0;
			for (int k = 1; k <= N; k++) {
				//curY_H_2 = curY + f(curY_H_2) * h / 2;
				double k1 = h * f(curY);
				double k2 = h * f(curY + k1 / 2);
				double k3 = h * f(curY + k2 / 2);
				double k4 = h * f(curY + k3);

				//curY += (k1 + 2 * k2 + 2 * k3 + k4) * h / 6; //ОШИБКА!!!
				curY += (k1 + 2 * k2 + 2 * k3 + k4) / 6;

				cout.width(printWidth);
				cout << x0 + k * h;
				cout.width(printWidth);
				cout << curY;
				cout.width(printWidth);
				cout << fabs(curY - solution(x0 + k * h));
				cout << endl;
			}
		}

		void printAdams() {
			cout << "Метод Адамса:" << endl;

			//таблица точка - значение по Тейлору
			double taylorTable[2][5];

			for (int k = -2; k <= 2; k++) {
				double curPoint = x0 + k * h;
				double taylorValue = 0;

				// разность между текущей и начальной точками
				// в степени i
				double pointCoef = 1;

				for (int i = 0; i < taylorCoefNumber; i++) {
					taylorValue += taylorCoefs[i] * pointCoef;
					pointCoef *= k * h;
				}

				taylorTable[0][k + 2] = curPoint;
				taylorTable[1][k + 2] = taylorValue;
			}

			//таблица с разделенными разностями
			double bigTable[7][N + 3];
			for (int i = 0; i < 7; i++)
				for (int j = 0; j < N + 3; j++)
					bigTable[i][j] = 0;

			for (int j = 0; j < N + 3; j++)
				bigTable[0][j] = x0 + (j - 2) * h;

			for (int j = 0; j < 5; j++)
				bigTable[1][j] = taylorTable[1][j];

			//заполнение первых ню
			for (int j = 0; j < 5; j++)
				bigTable[2][j] = f(bigTable[1][j]) * h;

			//заполнение первых конечных разностей
			for (int i = 3; i < 7; i++)
				for (int j = 0; j < (2 + 3 - (i - 2)); j++)
					bigTable[i][j] = bigTable[i - 1][j + 1] - bigTable[i - 1][j];

			/*
			for (int j = 0; j < N + 3; j++) {
				for (int i = 0; i < 7; i++) {
					cout.width(12);
					cout << bigTable[i][j];
				}
				cout << endl;
			}
			*/
			
			// заполняем таблицу по строчке до конца
			for (int j = 5; j < N + 3; j++) {
				double curLineValue = 0;
				
				curLineValue += bigTable[1][j - 1];
				curLineValue += bigTable[2][j - 1];
				curLineValue += bigTable[3][j - 2] * (1 / 2.0);
				curLineValue += bigTable[4][j - 3] * (5 / 12.0);
				curLineValue += bigTable[5][j - 4] * (3 / 8.0);
				curLineValue += bigTable[6][j - 5] * (251 / 720.0);

				bigTable[1][j] = curLineValue;
				//
				bigTable[2][j] = h * f(bigTable[1][j]);
				bigTable[3][j - 1] = bigTable[2][j - 0] - bigTable[2][j - 1];
				bigTable[4][j - 2] = bigTable[3][j - 1] - bigTable[3][j - 2];
				bigTable[5][j - 3] = bigTable[4][j - 2] - bigTable[4][j - 3];
				bigTable[6][j - 4] = bigTable[5][j - 3] - bigTable[5][j - 4];
			}

			/*
			cout << endl << "**********" << endl << endl;
			for (int j = 0; j < N + 3; j++) {
				for (int i = 0; i < 7; i++) {
					cout.width(12);
					cout << bigTable[i][j];
				}
				cout << endl;
			}
			*/
		
			cout << endl;	
			cout.width(printWidth);
			cout << "x";
			cout.width(printWidth);
			cout << "f(x)";
			cout.width(printWidth);
			cout << "Погрешность";
			cout << endl << endl;

			for (int k = 5; k < N + 3; k++) {
				double curPoint = x0 + (k - 2) * h;

				cout.width(printWidth);
				cout << curPoint;
				cout.width(printWidth);
				cout << bigTable[1][k];
				cout.width(printWidth);
				cout << fabs(bigTable[1][k] - solution(curPoint));
				cout << endl;
			}

		}

		double x0;
		double h;
		int N;
		int printWidth;

		int taylorCoefNumber;
		double *taylorCoefs;
};

int main() {
	Problem pr;
	pr.print();

	return 0;
}
