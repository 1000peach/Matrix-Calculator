#pragma once
#include "mat.h"

int isAdd(PartMat *temp, int size);
int isMulti(int col, int row);
// 연산 가능 여부 함수

void swapOper(char *swap);
char* divOper(char str[]);
void calMat(Mat mat[]);
void sumResult(PartMat *temp, int size);
// 행렬 계산 함수