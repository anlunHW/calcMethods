#pragma once

#include <cmath>

// u*(x, t)
double solution(double const x, double const t) {
	return exp(-0.25 * t) * cos(0.5 * x) + exp(-t) * (1 - x) * x;
}

// f(x, t)
double f(double const x, double const t) {
	return exp(-t) * (x * x - x + 2);
}

// u(x, 0) = g(x)
double g(double const x) {
	return cos(0.5 * x) + (1 - x) * x;
}

// u(0, t) = alpha(t)
double alpha(double const t) {
	return exp(-0.25 * t);
}

// u(1, t) = beta(t)
double beta(double const t) {
	return exp(-0.25 * t) * cos(0.5);
}

// a - interval left border
double const intervalLeftBorder = 0;

// b - interval right border
double const intervalRightBorder = 1;

// n - (node number - 1)
int const nodeNumber = 10 + 1; 

// a (from heat equation)
double const heatCoef = 1;

// h - node step
double const nodeStep =
	(intervalRightBorder - intervalLeftBorder) / (nodeNumber - 1);

// T - max time
double const maxTime = 1;

// tau
double const timeStep = nodeStep * nodeStep / (2 * heatCoef);
