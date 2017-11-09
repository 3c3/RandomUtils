#include "Matrix.h"

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

