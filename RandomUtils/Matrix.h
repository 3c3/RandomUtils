#pragma once
#include <iostream>
#include <algorithm>

template<class T>
class Matrix
{
private:
	
	// мързел

public:
	T *data;
	inline int Idx(int row, int column);
	int rows;
	int columns;

	~Matrix()
	{
		delete data;
	}

	void Create(int rows, int columns);
	T Get(int r, int c);
	void Set(int r, int c, T value);
	int GetRows();
	int GetColumns();
	bool GetDeterminant(T *outDet);

	void Print();
};

bool IsPermutationEven(int *perm, int size)
{
	bool even = true;
	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (perm[i] > perm[j]) even = !even;
		}
	}
	return even;
}

template<class T>
inline int Matrix<T>::Idx(int r, int c)
{
	return r*columns + c;
}

template<class T>
void Matrix<T>::Create(int rows, int columns)
{
	this->rows = rows;
	this->columns = columns;
	data = new T[rows*columns];
}

template<class T>
T Matrix<T>::Get(int r, int c)
{
	return data[Idx(r, c)];
}

template<class T>
void Matrix<T>::Set(int r, int c, T value)
{
	data[Idx(r, c)] = value;
}

template<class T>
int Matrix<T>::GetColumns()
{
	return columns;
}

template<class T>
int Matrix<T>::GetRows()
{
	return rows;
}

template<class T>
bool Matrix<T>::GetDeterminant(T *outDet)
{
	if (rows != columns) return false;

	int* permutation = new int[rows];
	for (int i = 0; i < rows; i++) permutation[i] = i + 1;

	*outDet = 0;
	do
	{
		T product = 1;
		for (int i = 0; i < rows; i++)
		{
			T current = data[Idx(i, permutation[i] - 1)];
			product *= current;
		}			

		if (IsPermutationEven(permutation, rows)) *outDet += product;
		else *outDet -= product;
	} while (std::next_permutation(permutation, permutation + rows));

	return true;
}

template<class T>
static bool MatrixAdd(Matrix<T> *a, Matrix<T> *b, Matrix<T> *out)
{
	return true;
}

template<class T>
static bool MatrixMultiply(Matrix<T> *a, Matrix<T> *b, Matrix<T> *out)
{
	if (a->columns != b->rows) return false;

	out->Create(a->rows, b->columns);
	int k = a->columns;

	for (int row = 0; row < a->rows; row++)
	{
		for (int column = 0; column < b->columns; column++)
		{
			T current = 0;
			for (int i = 0; i < k; i++)
			{
				T leftVal = a->Get(row, i);
				T rightVal = b->Get(i, column);
				current += leftVal*rightVal;
			}
				
			out->Set(row, column, current);
		}
	}

	return true;
}

template<class T>
void Matrix<T>::Print()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			std::cout << data[Idx(i, j)] << '\t';
		}
		std::cout << endl;
	}
}