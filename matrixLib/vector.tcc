#include "vector.h"

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
T Vector<T>::operator %(Vector<T> const &v) {
	if (mLineNumber != v.mLineNumber) {
		//warning!
		return 0;
	}

	T result;
	for (int i = 0; i < mLineNumber; i++) {
		result += (*this)[i][0] * v[i][0];
	}

	return result;
}
