#pragma once

#include "matrix2x2.h"

template <typename T>
Matrix2x2<T>::Matrix2x2()
	: Matrix<T>(2, 2)
{
}

template <typename T>
Matrix2x2<T>::Matrix2x2(T* arrayToCopy)
	: Matrix<T>(2, 2, arrayToCopy)
{
}

template <typename T>
Matrix2x2<T>::Matrix2x2(Matrix2x2 const &m)
	: Matrix<T>(m)
{
}
	
template <typename T>
Matrix2x2<T>::Matrix2x2(T const & a00, T const & a01,
		T const & a10, T const & a11)
	: Matrix<T>(2, 2)
{
	(*this)[0][0] = a00;
	(*this)[0][1] = a01;
	(*this)[1][0] = a10;
	(*this)[1][1] = a11;
}

template <typename T>
Matrix2x2<T>::Matrix2x2(Matrix<T> const &m)
	: Matrix<T>(2, 2)
{
	if ((m.lineNumber() != 2)
			|| (m.columnNumber() != 2)) {
		return;
	}

	for (int i = 0; i < 2 * 2; i++) {
		this->mArray[i] = m.array()[i];
	}
}

template <typename T>
T Matrix2x2<T>::determinant() const
{
	return (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0];
}

template <typename T>
Matrix2x2<T> Matrix2x2<T>::inversed() const
{
	T determinant = this->determinant();
	if (determinant == 0) {
		//warning!
		return Matrix2x2();
	}

	Matrix2x2<T> result = Matrix2x2<T>(
			(*this)[1][1], -(*this)[0][1],
			-(*this)[1][0], (*this)[0][0]
		);

	return result * (1 / determinant);
}

/*
template <typename T>
Matrix2x2<T> Matrix2x2<T>::operator +(Matrix2x2<T> const &m)
{
	Matrix<T>* casted = this;
	Matrix<T>* castedArg = *m;
	return Matrix2x2<T>((*casted) + (*castedArg));
	//return Matrix2x2<T>((this) + m);
	return Matrix2x2<T>();
}

template <typename T>
Matrix2x2<T> Matrix2x2<T>::operator -(Matrix2x2<T> const &m)
{
	Matrix<T>* casted = this;
	Matrix<T>* castedArg = *m;
	return Matrix2x2<T>((*casted) - (*castedArg));
	//return Matrix2x2<T>((*this) - m);
	return Matrix2x2<T>();
}

template <typename T>
Matrix2x2<T> Matrix2x2<T>::operator *(Matrix2x2<T> const &m)
{
	Matrix<T>* casted = this;
	Matrix<T>* castedArg = *m;
	return Matrix2x2<T>((*casted) * (*castedArg));
	//return Matrix2x2<T>((*this) * m);
	return Matrix2x2<T>();
}

template <typename T>
Matrix2x2<T> Matrix2x2<T>::operator *(T const &k)
{
	Matrix<T>* casted = this;
	return Matrix2x2<T>((*casted) * k);
	//return Matrix2x2<T>(Matrix(*this) * k);
	return Matrix2x2<T>();
}
*/
