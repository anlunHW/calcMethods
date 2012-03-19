#pragma once

template <typename T>
class Vector : public Matrix<T> {
	public:
		Vector(int lineNumber);
		Vector(int lineNumber, T* arrayToCopy);
		Vector(Vector<T> const &);

		//scalar product
		virtual T operator %(Vector<T> const &);
};

#include <vector.tcc>
