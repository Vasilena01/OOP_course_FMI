#include "Matrix.h"

// Big 4
void Matrix::copyFrom(const Matrix& other)
{
	matrix = new int*[other.rowsCount];
	
	for (int i = 0; i < rowsCount; i++)
	{
		matrix[i] = new int[other.colsCount];
	}

	rowsCount = other.rowsCount;
	colsCount = other.colsCount;

	for (int i = 0; i < rowsCount; i++)
	{
		for (int j = 0; j < colsCount; j++)
		{
			matrix[i][j] = other.matrix[i][j];
		}
	}
}

void Matrix::free()
{
	for (int i = 0; i < rowsCount; i++)
		delete[] matrix[i];

	delete[] matrix;
}

Matrix::Matrix()
{
	rowsCount = 2;
	colsCount = 2;

	for (int i = 0; i < rowsCount; i++)
	{
		matrix[i] = new int[colsCount];
	}

	for (int i = 0; i < rowsCount; i++)
	{
		for (int j = 0; j < colsCount; j++)
		{
			matrix[i][j] = 0;
		}
	}
}

Matrix::Matrix(unsigned newRowsCount, unsigned newColsCount)
{
	matrix = new int* [newRowsCount];

	for (int i = 0; i < newRowsCount; i++)
	{
		matrix[i] = new int[newColsCount];
	}

	rowsCount = newRowsCount;
	colsCount = newColsCount;

	for (int i = 0; i < rowsCount; i++)
	{
		for (int j = 0; j < colsCount; j++)
		{
			matrix[i][j] = 0;
		}
	}
}

Matrix::Matrix(const Matrix& other)
{
	copyFrom(other);
}

Matrix& Matrix::operator=(const Matrix& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Matrix::~Matrix()
{
	free();
}

// Additional functions
Matrix& Matrix::operator+=(const Matrix& other)
{
	if (rowsCount != other.rowsCount || colsCount != other.colsCount)
	{
		return *this;
	}

	for (int i = 0; i < rowsCount; i++)
	{
		for (int j = 0; j < colsCount; j++)
		{
			matrix[i][j] += other.matrix[i][j];
		}
	}

	return *this;
}

Matrix& Matrix::operator-=(const Matrix& other)
{
	if (rowsCount != other.rowsCount || colsCount != other.colsCount)
	{
		return *this;
	}

	for (int i = 0; i < rowsCount; i++)
	{
		for (int j = 0; j < colsCount; j++)
		{
			matrix[i][j] -= other.matrix[i][j];
		}
	}

	return *this;
}

Matrix& Matrix::operator*=(const Matrix& other)
{
	if (rowsCount != other.rowsCount || colsCount != other.colsCount)
	{
		return *this;
	}

	for (int i = 0; i < rowsCount; i++)
	{
		for (int j = 0; j < colsCount; j++)
		{
			matrix[i][j] *= other.matrix[j][i];
		}
	}

	return *this;
}

Matrix& Matrix::operator*=(int number)
{
	for (int i = 0; i < rowsCount; i++)
	{
		for (int j = 0; j < colsCount; j++)
		{
			matrix[i][j] *= number;
		}
	}

	return *this;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs)
{
	Matrix resultMatrix(lhs);

	resultMatrix += rhs;
	return resultMatrix;
}

Matrix operator-(const Matrix& lhs, const Matrix& rhs)
{
	Matrix resultMatrix(lhs);

	resultMatrix -= rhs;
	return resultMatrix;
}

