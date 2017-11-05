#pragma once
#include <iostream>
#include <algorithm>

template<class T>
class Matrix
{
private:
	
	bool created = false;
	// мързел

public:
	T *data = 0;
	inline int Idx(int row, int column);
	int rows = 0;
	int columns = 0;

	~Matrix()
	{
		if (data) delete data;
	}

	void Create(int rows, int columns);
	void MakeUnit();
	void CopyFrom(Matrix<T> *other);
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
	if (created)
	{
		if (this->rows == rows && this->columns == columns) return;

		delete data;
		this->rows = rows;
		this->columns = columns;
		data = new T[rows*columns];
		return;
	}

	this->rows = rows;
	this->columns = columns;
	data = new T[rows*columns];
	created = true;
}

template<class T>
void Matrix<T>::MakeUnit()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			data[Idx(i, j)] = i==j ? 1 : 0;
		}		
	}
}

template<class T>
void Matrix<T>::CopyFrom(Matrix<T> *other)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			int idx = Idx(i, j);
			data[idx] = other->data[idx];
		}
	}
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

	/*cout << "-----\n";
	a->Print();
	cout << endl;
	b->Print();
	cout << endl;*/

	if (out->rows != a->rows || out->columns != b->columns) out->Create(a->rows, b->columns);
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

	/*out->Print();
	cout << "-----\n";*/

	return true;
}

template<class T>
static bool MatrixPower(Matrix<T> *src, int power, Matrix<T> *out)
{
	if (src->rows != src->columns) return false;

	int highest = 31;
	while (!(power & (1 << highest))) highest--;
	highest++;

	highest++;
	Matrix<T> *powers2 = new Matrix<T>[highest]; // степен 2^k
	for (int i = 1; i < highest; i++) powers2[i].Create(src->rows, src->rows);

	highest--;
	out->Create(src->rows, src->rows);
	out->MakeUnit();

	Matrix<T> copy;
	copy.Create(src->rows, src->rows);

	powers2[0] = *src;
	int current = 1;

	if (power & 1)
	{
		out->CopyFrom(src);
	}

	while (current < highest)
	{
		MatrixMultiply(&powers2[current - 1], &powers2[current - 1], &powers2[current]);
		if ((1 << current) & power)
		{
			copy.CopyFrom(out);
			MatrixMultiply(&copy, &powers2[current], out);
		}
		current++;
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