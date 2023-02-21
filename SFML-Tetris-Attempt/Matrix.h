#ifndef MATRIX_H
#define MATRIX_H

#include <stdexcept>
#include <cstring>
#include <cstdarg>

namespace Goodie {
	class Matrix;

	void destroyMatrixLine(Matrix& matrix, int line);

	class Vector;

	class Matrix {
	protected:
		int line_count, column_count;
		int **matrix_ptr;

	public:
		Matrix(const Goodie::Matrix &cpy);
		Matrix(int line_count_par, int column_count_par, bool isExtraParameter, ...);
		~Matrix();
		
		//Getters
		const int& getLineCount();
		const int& getColumnCount();

		//Setters
		void setLineCount(const int &&count);
		void setColumnCount(const int &&count);

		//Operator overloads
		Matrix& operator = (Matrix &&matrix_r);
		int* operator [] (int index) const;
		Matrix operator + (Matrix &&matrix_r);
		Matrix operator - (Matrix &&matrix_r);
		Matrix operator * (Matrix &&matrix_r);
		Vector operator * (Vector &&vector_r);
		Matrix operator * (int scalar);

		operator Vector();

		//Friends
		friend void destroyMatrixLine(Goodie::Matrix& matrix, int line);
	};
}
#endif
