#pragma once

#include <iostream>

template <typename T>
class Matrix {
	//In realisation U is moved by T
	template <typename U> friend
		Matrix<U> operator *(U const &, Matrix<U> const &);
	template <typename U> friend
		std::ostream& operator <<(std::ostream& out, Matrix<T> const & matrix);

	public:
		Matrix(int lineNumber, int columnNumber);
		Matrix(int lineNumber, int columnNumber, T* arrayToCopy);
		Matrix(Matrix<T> const &);
		virtual ~Matrix();

		void operator +=(Matrix<T> const &);
		void operator -=(Matrix<T> const &);
		void operator *=(T const &);
		void operator /=(T const &);
		void operator =(Matrix<T> const &);
		T* operator [](int) const;

		virtual Matrix<T> operator +(Matrix<T> const &);
		virtual Matrix<T> operator -(Matrix<T> const &);
		virtual Matrix<T> operator *(Matrix<T> const &);
		virtual Matrix<T> operator *(T const &);
		virtual Matrix<T> operator /(T const &);

		//scalar product
		//ONLY for matrix with mColumnNumber == 1 
		virtual T operator %(Matrix<T> const &);

		Matrix<T> transposed() const;

		virtual std::ostream& print(std::ostream& out = std::cout) const;

		void exchangeLines(int firstLine, int secondLine);
		void exchangeColumns(int firstColumn, int secondColumn);

		void productLineByNumber(int line, T number);
		void productColumnByNumber(int column, T number);

		void addLineWithCoef(int firstLine, T coef, int resultLine);
		void addColumnWithCoef(int firstColumn, T coef, int resultColumn);

		T approximatedPrimeEigenvalue_scalarMethod(T delta);
		T approximatedPrimeEigenvalue_scalarMethod(T delta, std::ostream& out);

		T approximatedPrimeEigenvalue_degreeMethod(T delta);
		T approximatedPrimeEigenvalue_degreeMethod(T delta, std::ostream& out);

		T norm_inf();

		T gershgorinLeftBorder();
		T gershgorinRightBorder();
		
		T* array() const;

		int lineNumber() const;
		int columnNumber() const;

	protected:
		//for errors
		Matrix();

		static const int mPrintNumberWidth = 12;

		int mLineNumber;
		int mColumnNumber;

		T* mArray;
};

#include "matrix.tcc"
