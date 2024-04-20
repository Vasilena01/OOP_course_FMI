#pragma once
#include <iostream>

class Matrix {
	int** matrix;
	unsigned rowsCount;
	unsigned colsCount;

	void copyFrom(const Matrix& other);
	void free();
public:
	Matrix();
	Matrix(unsigned rowsSize, unsigned ColsSize);
	Matrix(const Matrix& other);
	Matrix& operator=(const Matrix& other);
	~Matrix();

	Matrix& operator+=(const Matrix& other);
	Matrix& operator-=(const Matrix& other);
	Matrix& operator*=(const Matrix& other);
	Matrix& operator*=(int number);
};

Matrix operator+(const Matrix& lhs, const Matrix& rhs);
Matrix operator-(const Matrix& lhs, const Matrix& rhs);