#include <iostream>
#include <omp.h>
#include <cmath>

using namespace std;

double** createArray(int lines, int rows) {
  double** arr;
  arr = new double*[lines];
  for (int i = 0; i < lines; i++) {
    arr[i] = new double[rows];
  }
  return arr;
}

void removeArray(double** arr, int lines) {
  for (int i = 0; i < lines; i++) {
    delete [] arr[i];
  }
  delete [] arr;
}

void readArray(double** arr, int lines, int rows) {
  for (int i = 0; i < lines; i++) {
    for (int j = 0; j < rows; j++) {
      cin >> arr[i][j];
    }
  }
}

void printArray(double** arr, int lines, int rows) {
  cout << endl;
  for (int i = 0; i < lines; i++) {
    for (int j = 0; j < rows; j++) {
      cout << arr[i][j] << ' ';
    }
    cout << endl;
  }
}

#ifdef N
static int n = N;
#else
static int n = 2;
#endif

#ifdef M
static int m = M;
#else
static int m = 2;
#endif

int main(int argv, char** args) {
  double** matrix = createArray(n, m);
  readArray(matrix, n, m);

#pragma omp parallel
  {
#pragma omp sections
  {
    #pragma omp section
    {//norm 1
      double max = 0;
#pragma omp parallel reduction(max:max)
      for (int i = 0; i < n; i++) {
        double localSum = 0;
#pragma omp parallel reduction(+:localSum)
        for (int j = 0; j < m; j++) {
          localSum += abs(sin(matrix[i][j]));
        }
        if (localSum > max) {
          max = localSum;
        }
      }
      cout << "Norm 1: " << max << endl;
    }

    #pragma omp section
    {//norm 2
      double max = 0;
#pragma omp parallel reduction(max:max)
     for (int i = 0; i < m; i++) {
        double localSum = 0;
#pragma omp parallel reduction(+:localSum)
        for (int j = 0; j < n; j++) {
          localSum += abs(sin(matrix[j][i]));
        }
        if (localSum > max) {
         max = localSum;
        }
      }
      cout << "Norm 2: " << max << endl;
    }
  }
  }

  removeArray(matrix, n);
  return 0;
}
