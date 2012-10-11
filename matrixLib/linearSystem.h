#pragma once

#include "matrix.h"

template <typename T>
class LinearSystem {
	template <typename U> friend
		std::ostream& operator <<(std::ostream& out, LinearSystem<T> const &system);

	public:
		static LinearSystem<T>* createSystem(Matrix<T> coef, Matrix<T> constTerm);
		virtual std::ostream& print(std::ostream& out = std::cout) const;

		Matrix<T> gaussMethod();
		Matrix<T> gaussMethodWithChoosingInLine();
		
		Matrix<T> gaussMethodPrinting();
		Matrix<T> gaussMethodWithChoosingInLinePrinting();

		Matrix<T>& systemCoef();
		Matrix<T>& constTerm();
		int systemSize() const;
	
	private:
		LinearSystem(Matrix<T> coef, Matrix<T> constTerm);

		static int const mPrintNumberWidth = 16;
		int const mSystemSize;

		Matrix<T> mSystemCoef;
		Matrix<T> mConstTerm;
};

#include "linearSystem.tcc"
