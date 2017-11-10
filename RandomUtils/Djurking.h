#pragma once
#include "Matrix.h"
#include <stack>
#include <string>
#include <sstream>

//#define DEBJURK

void DjurkIt(Matrix<int> *src, Matrix<int> *ext);

void DjurkItRec(int pos, Matrix<int>** matrixStack, Matrix<int>** extStack, std::stack<std::string> &actions, bool* usedRows, bool* usedColumns, int cost);

void PrintMatrixStack(Matrix<int>** matrixStack, int idxLast);

void PrintMatrixStack(Matrix<int>** matrixStack, Matrix<int>** extStack, int idxLast);

void CopyMatrixStack(Matrix<int>** src, Matrix<int>** dest, int lastPos);