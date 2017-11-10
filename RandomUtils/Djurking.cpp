#include "Djurking.h"

using namespace std;

Matrix<int> **bestStack, **bestExtStack;
int bestStackPos;
int bestCost;
stack<string> bestActions;

// Джурка добре и вече памет не тече (или поне по-малко)
void DjurkIt(Matrix<int> *src, Matrix<int> *ext)
{
	int stackSize = src->rows;
	if (src->columns > stackSize) stackSize = src->columns;
	stackSize++;

	Matrix<int>** stack = new Matrix<int>*[stackSize];
	memset(stack, 0, sizeof(Matrix<int>*)*stackSize);

	Matrix<int>** extStack = new Matrix<int>*[stackSize];
	memset(extStack, 0, sizeof(Matrix<int>*)*stackSize);

	bestStack = new Matrix<int>*[stackSize];
	memset(bestStack, 0, sizeof(Matrix<int>*)*stackSize);

	bestExtStack = new Matrix<int>*[stackSize];
	memset(bestExtStack, 0, sizeof(Matrix<int>*)*stackSize);
	
	bool* usedRows = new bool[src->rows];
	bool* usedColumns = new bool[src->columns];
	memset(usedRows, 0, src->rows);
	memset(usedColumns, 0, src->columns);	
	
	bestCost = 999999;

	stack[0] = new Matrix<int>(src);
	if (ext) extStack[0] = new Matrix<int>(ext);
	
	std::stack<string> actions;

	DjurkItRec(0, stack, extStack, actions, usedRows, usedColumns, 0);

	cout << "Best djurking cost: " << bestCost << endl;
	
	if (ext)
	{
		PrintMatrixStack(bestStack, bestExtStack, bestStackPos);
	}
	else PrintMatrixStack(bestStack, bestStackPos);

	for (int i = 0; i < stackSize; i++)
	{
		if (bestStack[i]) delete bestStack[i];
		if (stack[i]) delete stack[i];
	}

	delete[] usedColumns;
	delete[] usedRows;
	delete[] bestStack;
	delete[] stack;

	if (ext)
	{
		for (int i = 0; i < stackSize; i++)
		{
			if (extStack[i]) delete extStack[i];
			if (bestExtStack[i]) delete bestExtStack[i];
		}
	}

	delete[] extStack;
	delete[] bestExtStack;
}

int gcd(int a, int b) 
{
	return b == 0 ? a : gcd(b, a % b);
}

void DjurkItRec(int pos, Matrix<int>** matrixStack, Matrix<int>** extStack, stack<string> &actions, bool* usedRow, bool* usedColumn, int cost)
{
	Matrix<int>* current = matrixStack[pos];

	bool pushed = false;

	for (int column = 0; column < current->columns; column++)
	{
		if (usedColumn[column]) continue; // вече е изджуркан тоя стълб
		usedColumn[column] = true;

		for (int row = 0; row < current->rows; row++)
		{
			if (usedRow[row]) continue; // ползвали сме реда
			if (current->Get(row, column) == 0) continue; // няма смисъл с този

			bool negative = false; // по-удобно
			
			stringstream currentAction;
			currentAction << "Selected: R" << row + 1 << " C" << column+1 <<" -> ";

			int value = current->Get(row, column);
			if (value < 0)
			{
				value = -value;
				negative = true;
			}
			int djurkingCost = 0;

			Matrix<int>* target = new Matrix<int>(current); // матрицата след едно джуркане
			Matrix<int> *newExt = 0;
			if (extStack[pos])
			{
				//extStack[pos]->Print();
				//cout << endl;
				newExt = new	Matrix<int>(extStack[pos]);
			}

			for (int i = 0; i < current->rows; i++)
			{
				if (i == row) continue; // да не се занулим нали
				if (target->Get(i, column) == 0) continue; // готова работа

				int nonzero = target->Get(i, column);
				int positive = nonzero ? nonzero : -nonzero;

				if (positive % value == 0)
				{
					int coef = -nonzero / value;
					if (negative) coef = -coef;

					djurkingCost++; // точно се дели, добро джуркане
					target->AddRow(row, i, coef);
					if (newExt) newExt->AddRow(row, i, coef);
					currentAction << "R" << i + 1 << " " << coef << ", ";
					
				}
				else
				{
					djurkingCost += 5; // трябва да се умножи, лошо джуркане
					int nok = positive*value / gcd(positive, value);

					int coef = -nok / value;
					if (negative) coef = -coef;

					target->MultiplyRow(i, nok / positive);
					target->AddRow(row, i, coef);
					if (newExt)
					{
						newExt->MultiplyRow(i, nok / positive);
						newExt->AddRow(row, i, coef);
					}

					currentAction << (nok / positive) << "R" << i + 1 << " " << coef << ", ";
				}
			}

			usedRow[row] = true;
			matrixStack[pos + 1] = target;
			if (newExt)
			{
				extStack[pos + 1] = newExt;
				//newExt->Print();
				//cout << endl;
			}

			string str = currentAction.str();
			actions.push(str);

			DjurkItRec(pos + 1, matrixStack, extStack, actions, usedRow, usedColumn, cost + djurkingCost);

			actions.pop();
			usedRow[row] = false;
			pushed = true;
			delete target;
			matrixStack[pos + 1] = 0;
			if (newExt)
			{
				delete newExt;
				extStack[pos + 1] = 0;
			}
		}
		usedColumn[column] = false;
	}

	if (!pushed) // край на джуркането
	{
		if (cost < bestCost)
		{
			bestCost = cost;
			bestStackPos = pos;
			CopyMatrixStack(matrixStack, bestStack, pos);

			if (extStack[0]) CopyMatrixStack(extStack, bestExtStack, pos);

			bestActions = actions;
		}
	}
}

void CopyMatrixStack(Matrix<int>** src, Matrix<int>** dest, int lastPos)
{
	for (int i = 0; i <= lastPos; i++)
	{
		if (dest[i]) delete dest[i];
		dest[i] = new Matrix<int>(src[i]);
	}
}

void PrintMatrixStack(Matrix<int>** matrixStack, int idxLast)
{
	string* actions = new string[bestActions.size()];
	int idx = bestActions.size() - 1;
	while (!bestActions.empty())
	{
		actions[idx--] = bestActions.top();
		bestActions.pop();
	}

	for (int i = 0; i <= idxLast; i++)
	{
		matrixStack[i]->Print();
		if (i < idxLast) cout << actions[i] << endl;
		cout << endl;
	}
}

void PrintMatrixStack(Matrix<int>** matrixStack, Matrix<int>** extStack, int idxLast)
{
	int rows = matrixStack[0]->rows;
	int columns = matrixStack[0]->columns;
	int extColumns = extStack[0]->columns;

	string* actions = new string[bestActions.size()];
	int idx = bestActions.size() - 1;
	while (!bestActions.empty())
	{
		actions[idx--] = bestActions.top();
		bestActions.pop();
	}

	for (int i = 0; i <= idxLast; i++)
	{
		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c < columns; c++) cout << matrixStack[i]->Get(r,c) << '\t';
			cout << "|\t";
			for (int c = 0; c < extColumns; c++) cout << extStack[i]->Get(r,c) << '\t';
			cout << endl;			
		}
		if (i < idxLast) cout << actions[i] << endl;
		cout << endl;
	}
}