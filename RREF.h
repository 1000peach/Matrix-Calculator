#pragma once
#include "mat.h"

Mat *changeZero(Mat *mat); // zero row Çà·Ä ¹ØÀ¸·Î º¸³¿
						   // REF, RREF ¿¬»ê
void startREF(Mat *mat);
void startRREF(double **mat, char name, int row, int col);
