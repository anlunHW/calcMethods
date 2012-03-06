#pragma once

template <typename T>
class Matrix2x2: public Matrix<T> {
	public:
		Matrix2x2();
		Matrix2x2(T* arrayToCopy);
		Matrix2x2(Matrix2x2<T> const &);
		Matrix2x2(T const & a00, T const & a01, T const & a10, T const & a11);

		Matrix2x2(Matrix<T> const &); // works correctly only for 2x2 Matrix object

		/*		
		virtual Matrix2x2<T> operator +(Matrix2x2<T> const &);
		virtual Matrix2x2<T> operator -(Matrix2x2<T> const &);
		virtual Matrix2x2<T> operator *(Matrix2x2<T> const &);
		virtual Matrix2x2<T> operator *(T const &);
		*/

		T determinant() const;
		Matrix2x2<T> inversed() const;
};

#include "matrix2x2.tcc"
