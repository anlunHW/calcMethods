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
		void operator =(Matrix<T> const &);
		T* operator [](int) const;

		virtual Matrix<T> operator +(Matrix<T> const &);
		virtual Matrix<T> operator -(Matrix<T> const &);
		virtual Matrix<T> operator *(Matrix<T> const &);
		virtual Matrix<T> operator *(T const &);

		Matrix<T> transposed() const;

		std::ostream& print(std::ostream& out = std::cout) const;

		T norm_inf();
		
		T* array() const;

		int lineNumber() const;
		int columnNumber() const;

	protected:
		//for errors
		Matrix();

		int mLineNumber;
		int mColumnNumber;

		T* mArray;
};

#include "matrix.tcc"
