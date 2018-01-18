#include <iostream>
#include "Djurking.h"

using namespace std;

int main()
{
	while (true)
	{
		Matrix<int> a;
		int rows;
		int columns;
		cin >> rows;
		cin >> columns;
		a.Create(rows, columns);

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				cin >> a.data[a.Idx(i, j)];
			}
		}

		cout << "Enter ext columns: ";

		int extColumns;
		cin >> extColumns;

		Matrix<int> b;
		b.Create(rows, extColumns);

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < extColumns; j++)
			{
				cin >> b.data[b.Idx(i, j)];
			}
		}

		DjurkIt(&a, extColumns ? &b : 0);
	}

	return 0;
}