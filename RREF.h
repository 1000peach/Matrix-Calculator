#pragma once
#include "mat.h"

Mat *changeZero(Mat *mat); // zero row ��� ������ ����
						   // REF, RREF ����
void startREF(Mat *mat);
void startRREF(double **mat, char name, int row, int col);
