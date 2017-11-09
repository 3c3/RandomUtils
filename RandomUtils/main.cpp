#include <iostream>
#include "Djurking.h"

using namespace std;

int main()
{
	while (true)
	{
		Matrix<int> a;
		int size;
		cin >> size;
		a.Create(size, size);

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				cin >> a.data[a.Idx(i, j)];
			}
		}

		int extColumns;
		cin >> extColumns;

		Matrix<int> b;
		b.Create(size, extColumns);

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < extColumns; j++)
			{
				cin >> b.data[b.Idx(i, j)];
			}
		}

		b.Print();
		//a.Print();

		DjurkIt(&a, &b);
	}

	return 0;
}