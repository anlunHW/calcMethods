#include "interval.h"

Interval::Interval(double start, double end): mStart(start), mEnd(end) {
}

double Interval::start() const {
	return mStart;
}

void Interval::setStart(double start) {
	mStart = start;
}

double Interval::end() const {
	return mEnd;
}

void Interval::setEnd(double end) {
	mEnd = end;
}

QString Interval::toString() const {
	return "(" + QString::number(mStart) + ", " + QString::number(mEnd) + ")\n";
}
