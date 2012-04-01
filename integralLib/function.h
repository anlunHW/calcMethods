#pragma once

class Function {
	public:
		virtual ~Function();

		virtual double func(double const x) const = 0;
		virtual double calculateIntegral(unsigned const intervalNumber, double const leftBorder, double const rightBorder) const;


	protected:
		//Simpson integral
		virtual double calculatePrimaryIntervalIntegral(double const left, double const right) const;
};
