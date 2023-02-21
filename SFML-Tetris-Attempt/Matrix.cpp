#include "Matrix.h"
#include "Vector.h"

Goodie::Matrix::Matrix(int line_count_par, int column_count_par, bool isExtraParameter, ...) {
	line_count = line_count_par;
	column_count = column_count_par;
	
	do {
		matrix_ptr = new int*[line_count];
	} while (matrix_ptr == nullptr);
	for (int i = 0; i < line_count; i++) {
		do {
			matrix_ptr[i] = new int[column_count];
		} while (matrix_ptr[i] == nullptr);
		for (int j = 0; j < column_count; j++) {
			matrix_ptr[i][j] = 0;
		}
	}

	if (isExtraParameter == false) return;

	std::va_list a_list;
	va_start(a_list, isExtraParameter);
	
	for (int i = 0; i < line_count; i++) {
		for (int j = 0; j < column_count; j++) {
			matrix_ptr[i][j] = va_arg(a_list, int);
		}
	}
	
	va_end(a_list);
}

Goodie::Matrix::Matrix(const Goodie::Matrix &cpy) {
	line_count = cpy.line_count;
	column_count = cpy.column_count;

	do {
		matrix_ptr = new int* [line_count];
	} while (matrix_ptr == nullptr);
	for (int i = 0; i < line_count; i++) {
		do {
			matrix_ptr[i] = new int[column_count];
		} while (matrix_ptr[i] == nullptr);
		for (int j = 0; j < column_count; j++) {
			matrix_ptr[i][j] = cpy.matrix_ptr[i][j];
		}
	}
}

Goodie::Matrix::~Matrix() {
	if (matrix_ptr != nullptr) {
		for (int i = 0; i < line_count; i++) {
			if (matrix_ptr[i] != nullptr) 
				delete [] matrix_ptr[i];
		}
		delete [] matrix_ptr;
	}
}

//Getters
const int& Goodie::Matrix::getLineCount() {
	return line_count;
}

const int& Goodie::Matrix::getColumnCount() {
	return column_count;
}

//Setters
void Goodie::Matrix::setLineCount(const int &&count) {
	line_count = count;
}

void Goodie::Matrix::setColumnCount(const int &&count) {
	column_count = count;
}

//Operators

Goodie::Matrix& Goodie::Matrix::operator = (Matrix &&matrix_r) {
	if (this->line_count != matrix_r.line_count || this->column_count != matrix_r.column_count)
		return *this;
	for (int i = 0; i < this->line_count; i++) {
		for (int j = 0; j < this->column_count; j++) {
			(*this)[i][j] = matrix_r[i][j];
		}
	}
	return *this;
}

int* Goodie::Matrix::operator [] (int index) const {
	if (index >= this->line_count || index < 0)
		return nullptr;
	return this->matrix_ptr[index];
}

Goodie::Matrix Goodie::Matrix::operator + (Goodie::Matrix &&matrix_r) {
	if (this->line_count != matrix_r.line_count || this->column_count != matrix_r.column_count)
		throw std::runtime_error("The matrices don't suit each other.");

	Matrix new_matrix(this->line_count, this->column_count, false);
	for (int i = 0; i < this->line_count; i++) {
		for (int j = 0; j < this->column_count; j++) {
			new_matrix[i][j] = (*this)[i][j] + matrix_r[i][j];
		}
	}
	
	return new_matrix;
}

Goodie::Matrix Goodie::Matrix::operator - (Goodie::Matrix &&matrix_r) {
	if (this->line_count != matrix_r.line_count || this->column_count != matrix_r.column_count)
		throw std::runtime_error("The matrices don't suit each other.");

	Matrix new_matrix(this->line_count, this->column_count, false);
	for (int i = 0; i < this->line_count; i++) {
		for (int j = 0; j < this->column_count; j++) {
			new_matrix[i][j] = (*this)[i][j] - matrix_r[i][j];
		}
	}
	
	return new_matrix;
}

Goodie::Matrix Goodie::Matrix::operator * (Goodie::Matrix &&matrix_r) {
	if (this->column_count != matrix_r.line_count) 
		throw std::runtime_error("The matrices don't suit each other.");
	
	Matrix new_matrix(this->line_count, matrix_r.column_count, false);
	for (int i = 0; i < this->line_count; i++) {
		for (int j = 0; j < matrix_r.column_count; j++) {
			for (int k = 0; j < matrix_r.line_count; k++) {
				new_matrix[i][j] += (*this)[i][k] * matrix_r[k][j];
			}
		}
	}

	return new_matrix;
}

Goodie::Vector Goodie::Matrix::operator * (Goodie::Vector &&vector_r) {
	if (this->column_count != vector_r.line_count)
		throw std::runtime_error("The matrices don't suit each other.");

	Vector new_vector(this->line_count);
	for (int i = 0; i < this->line_count; i++) {
		for (int j = 0; j < vector_r.column_count; j++) {
			for (int k = 0; k < vector_r.line_count; k++) {
				new_vector[i][j] += (*this)[i][k] * vector_r[k][j];
			}
		}
	}

	return new_vector;
}

Goodie::Matrix Goodie::Matrix::operator * (int scalar) {
	Goodie::Matrix new_matrix(this->line_count, this->column_count, false);
	for (int i = 0; i < this->line_count; i++) {
		for (int j = 0; j < this->column_count; j++) {
			new_matrix[i][j] = (*this)[i][j] * scalar;
		}
	}
	
	return new_matrix;
}

Goodie::Matrix::operator Goodie::Vector() {
	Goodie::Vector vec(this->line_count);

	for (int i = 0; i < vec.line_count; i++) {
		vec[i][0] = (*this)[i][0];
	}

	return vec;
}
