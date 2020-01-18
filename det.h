#pragma once
#include "mat.h"

int isSquare(int row, int col);
int twoDet(int **arr);
int threeDet(int **arr);
int moreDet(int **arr, int row, int col);
void calMatDet(Mat *mat);
// 행렬식 계산 함수