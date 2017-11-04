#include <iostream>
#include "ComplexNumber.h"

using namespace std;

int main()
{
	char operation;
	ComplexNumber a, b, result;

	while (true)
	{
		cin >> operation;
		if (operation == '+')
		{
			a.Input();
			b.Input();
			result = a + b;
			result.Print();
			cout << endl;
		}
		else if (operation == '-')
		{
			a.Input();
			b.Input();
			result = a - b;
			result.Print();
			cout << endl;
		}
		else if (operation == '*')
		{
			a.Input();
			b.Input();
			result = a * b;
			result.Print();
			cout << endl;
		}
		else if (operation == '/')
		{
			a.Input();
			b.Input();
			result = a / b;
			result.Print();
			cout << endl;
		}
		else cout << "Bad op" << endl;
	}

	/*
	while (true)
	{
		Matrix<long long> a;

		int sqSize;
		cin >> sqSize;

		a.Create(sqSize, sqSize);
		for (int i = 0; i < sqSize; i++)
		{
			for (int j = 0; j < sqSize; j++)
			{
				cin >> a.data[a.Idx(i, j)];
			}
		}
		long long det;
		a.GetDeterminant(&det);
		cout << det << endl;
		cout << endl;
	}

	while (true)
	{
		Matrix<int> a, b;

		int sqSize;
		cin >> sqSize;

		a.Create(sqSize, sqSize);
		for (int i = 0; i < sqSize; i++)
		{
			for (int j = 0; j < sqSize; j++)
			{
				cin >> a.data[a.Idx(i, j)];
			}
		}

		cin >> sqSize;

		b.Create(sqSize, sqSize);
		for (int i = 0; i < sqSize; i++)
		{
			for (int j = 0; j < sqSize; j++)
			{
				cin >> b.data[a.Idx(i, j)];
			}
		}

		cout << "left-mult or right-mult?[l/r]\n";
		char c;
		cin >> c;

		if (c == 'l')
		{
			Matrix<int> result;
			if (MatrixMultiply(&a, &b, &result))
			{
				result.Print();
			}
			else cout << "Imposible";
			cout << endl;
		}
		else
		{
			Matrix<int> result;
			if (MatrixMultiply(&b, &a, &result))
			{
				result.Print();
			}
			else cout << "Imposible";
			cout << endl;
		}
		cout << endl;
	}
	*/

	system("pause");
	return 0;
}