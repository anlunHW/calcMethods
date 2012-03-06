#pragma once

#include <cmath>
#include <algorithm>
#include "matrix.h"

template <typename T>
Matrix<T>::Matrix(int lineNumber, int columnNumber)
	: mLineNumber(lineNumber)
	, mColumnNumber(columnNumber)
{
	mArray = new T[lineNumber * columnNumber];
}

template <typename T>
Matrix<T>::Matrix(int lineNumber, int columnNumber, T* arrayToCopy)
	: mLineNumber(lineNumber)
	, mColumnNumber(columnNumber)
{
	mArray = new T[lineNumber * columnNumber];

	for(int i = 0; i < (lineNumber * columnNumber); i++)
	{
		mArray[i] = arrayToCopy[i];
	}
}

template <typename T>
Matrix<T>::Matrix(Matrix<T> const &a)
	: mLineNumber(a.mLineNumber)
	, mColumnNumber(a.mColumnNumber)
{
	mArray = new T[mLineNumber * mColumnNumber];
	for(int i = 0; i < (mLineNumber * mColumnNumber); i++)
	{
		mArray[i] = a.mArray[i];
	}
}

template <typename T>
Matrix<T>::Matrix()
	: mLineNumber(0)
	, mColumnNumber(0)
	, mArray(0)
{
}

template <typename T>
Matrix<T>::~Matrix<T>()
{
	if (mArray)
		delete [] mArray;
}

template <typename T>
T* Matrix<T>::array() const
{
	return mArray;
}

template <typename T>
T *Matrix<T>::operator[]( int i ) const
{
	return (mArray + i * mColumnNumber);
}

template <typename T>
int Matrix<T>::columnNumber() const
{
	return mColumnNumber;
}

template <typename T>
int Matrix<T>::lineNumber() const
{
	return mLineNumber;
}

template <typename T>
Matrix<T> Matrix<T>::operator *(Matrix<T> const &m)
{
	if (mColumnNumber != m.mLineNumber) {
		//warning!
		return Matrix<T>();
	}

	Matrix<T> result(mLineNumber, m.mColumnNumber);
	for (int i = 0; i < mLineNumber; i++)
	{
		for (int j = 0; j < m.mColumnNumber; j++)
		{
			result.mArray[i * result.mColumnNumber + j] = 0;

			for (int k = 0; k < mColumnNumber; k++)
			{
				result.mArray[i * result.mColumnNumber + j] +=
					mArray[i * mColumnNumber + k]
					* m.mArray[k * m.mColumnNumber + j];
			}
		}
	}

	return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator *(T const &k)
{
	Matrix<T> result(*this);
	for ( int i = 0; i < mLineNumber; i++ )
		for (int j = 0; j < mColumnNumber; j++)
			result.mArray[i * result.mColumnNumber + j] *= k;
	return result;
}

template <typename T>
Matrix<T> operator *(T const &k, Matrix<T> const &m1)
{
	Matrix<T> result(m1);
	for (int i = 0; i < m1.mLineNumber; i++)
		for (int j = 0; j < m1.mColumnNumber; j++)
			result.mArray[i * result.mColumnNumber + j] *= k;
	return result;
}

template <typename T>
void Matrix<T>::operator +=(Matrix<T> const &m)
{
	if ((m.mLineNumber != mLineNumber) ||
			(m.mColumnNumber != mColumnNumber)) {
		//warning!
		return;
	}

	for (int i = 0; i < m.mLineNumber; i++)
		for (int j = 0; j < m.mColumnNumber; j++)
			mArray[i * mColumnNumber + j] +=
				m.mArray[i * mColumnNumber + j];
}

template <typename T>
void Matrix<T>::operator -=(Matrix<T> const &m)
{
	if ((m.mLineNumber != mLineNumber) ||
			(m.mColumnNumber != mColumnNumber)) {
		//warning!
		return;
	}

	for (int i = 0; i < m.mLineNumber; i++)
		for (int j = 0; j < m.mColumnNumber; j++)
			mArray[i * mColumnNumber + j] -=
				m.mArray[i * mColumnNumber + j];
}

template <typename T>
Matrix<T> Matrix<T>::operator +(Matrix<T> const &m)
{
	Matrix<T> result(*this);
	result += m;
	return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator -(Matrix<T> const &m)
{
	Matrix<T> result(*this);
	result -= m;
	return result;
}

template <typename T>
void Matrix<T>::operator =(Matrix<T> const &m)
{
	if (mArray)
		delete [] mArray;

	mLineNumber = m.mLineNumber;
	mColumnNumber = m.mColumnNumber;
	mArray = new T[mLineNumber * mColumnNumber];

	for (int i = 0; i < mLineNumber; i++)
	{
		for (int j = 0; j < mColumnNumber; j++)
		{
			mArray[i * mColumnNumber + j] =
				m.mArray[i * mColumnNumber + j];
		}
	}
}

template <typename T>
Matrix<T> Matrix<T>::transposed() const
{
	Matrix<T> result(mColumnNumber, mLineNumber);

	for(int i = 0; i < mLineNumber; i++)
		for(int j = 0; j < mColumnNumber; j++)
		{
			result[j][i] = (*this)[i][j];
		}

	return result;
}

template <typename T>
std::ostream& Matrix<T>::print(std::ostream& out) const
{
	for (int i = 0; i < mLineNumber; i++) {
		for (int j = 0; j < mColumnNumber; j++) {
			out.width(mPrintNumberWidth);
			//out << mArray[i * mColumnNumber + j] << ' ';
			out << mArray[i * mColumnNumber + j];
		}
		out << std::endl;
	}
	return out;
}

template <typename T>
std::ostream& operator <<(std::ostream& out, Matrix<T> const &matrix)
{
	matrix.print(out);
	return out;
}

template <typename T>
T Matrix<T>::norm_inf()
{
	T result = 0;

	for (int i = 0; i < mLineNumber; i++) {
		T lineResult = 0;
		for (int j = 0; j < mColumnNumber; j++) {
			lineResult += fabs((*this)[i][j]);
		}

		result = max(result, lineResult);
	}

	return result;
}

template <typename T>
void Matrix<T>::productLineByNumber(int line, T number)
{
	for (int i = 0; i < mColumnNumber; i++) {
		(*this)[line][i] *= number;
	}
}
	
template <typename T>
void Matrix<T>::productColumnByNumber(int column, T number)
{
	for (int i = 0; i < mLineNumber; i++) {
		(*this)[i][column] *= number;
	}
}

template <typename T>
void Matrix<T>::addLineWithCoef(int firstLine, T coef, int resultLine)
{
	for (int i = 0; i < mColumnNumber; i++) {
		(*this)[resultLine][i] += (*this)[firstLine][i] * coef;
	}
}
	
template <typename T>
void Matrix<T>::addColumnWithCoef(int firstColumn, T coef, int resultColumn)
{
	for (int i = 0; i < mLineNumber; i++) {
		(*this)[i][resultColumn] += (*this)[i][firstColumn] * coef;
	}
}

template <typename T>
void Matrix<T>::exchangeLines(int firstLine, int secondLine)
{
	for (int i = 0; i < mColumnNumber; i++) {
		T temp = (*this)[firstLine][i];
		(*this)[firstLine][i] = (*this)[secondLine][i];
		(*this)[secondLine][i] = temp;
	}
}
	
template <typename T>
void Matrix<T>::exchangeColumns(int firstColumn, int secondColumn)
{
	for (int i = 0; i < mLineNumber; i++) {
		T temp = (*this)[i][firstColumn];
		(*this)[i][firstColumn] = (*this)[i][secondColumn];
		(*this)[i][secondColumn] = temp;
	}
}
