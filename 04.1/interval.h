#pragma once

#include <QString>

class Interval {
	public:
		Interval(double start, double end);

		double start() const;
		void setStart(double);

		double end() const;
		void setEnd(double);

		QString toString() const;

	private:
		double mStart;
		double mEnd;
};
