#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mat.h"

int isSquare(int row, int col) {
	if (row != col) {
		return FALSE;
	}
	else {
		return TRUE;
	}
} // 행렬식 계산 가능 유무 반환 (square matrix 판단)

int twoDet(int **arr) {
	return (arr[0][0] * arr[1][1]) - (arr[0][1] * arr[1][0]);
} // 2차원 행렬의 행렬식 계산

int threeDet(int **arr) {
	int **temp, i, j, p = 0, q = 0;
	int result[3], sum = 0;

	temp = allocArr(2, 2);
	for (i = 1; i < 3; i++) {
		for (j = 1; j < 3; j++) {
			temp[i - 1][j - 1] = arr[i][j];
		}
	}
	result[0] = arr[0][0] * twoDet(temp);
	for (i = 1; i < 3; i++) {
		q = 0;
		for (j = 0; j<3; j += 2) {
			temp[p][q] = arr[i][j];
			q++;
		}
		p++;
	}
	result[1] = -1 * arr[0][1] * twoDet(temp);
	for (i = 1; i < 3; i++) {
		for (j = 1; j < 3; j++) {
			temp[i - 1][j - 1] = arr[i][j];
		}
	}
	for (i = 1; i < 3; i++) {
		for (j = 0; j < 2; j++) {
			temp[i - 1][j] = arr[i][j];
		}
	}
	result[2] = arr[0][2] * twoDet(temp);

	for (i = 0; i < 3; i++) {
		sum += result[i];
	}
	return sum;
} // 3차원 행렬의 행렬식 계산 (첫번째 row 선택하여 cofactor 이용해 계산)

int moreDet(int **arr, int row, int col) {
	int index, scala = 1;
	int **temp, result;
	int i, j, p = 0, q = 0;

	if (row < 2) {
		return arr[0][0];
	} // 행렬 요소 하나일 때
	else if (row < 3) {
		return twoDet(arr); // 2차원 행렬일 때
	}
	else if (row < 4) {
		return threeDet(arr);
	} // 3차원 행렬일 때
	else {
		temp = allocArr(row - 1, col - 1);
		for (j = 0; j < col; j++) {
			if (arr[0][j] != 0) {
				scala = arr[0][j];
				index = j;
				break;
			}
		}
		if (!index) {
			return 0;
		}
		for (i = 1; i < row; i++) {
			q = 0;
			for (j = 0; j < col; j++) {
				if (j != index) {
					temp[p][q] = arr[i][j];
					q++;
				}
			}
			p++;
		}
		result = scala * moreDet(temp, row - 1, col - 1);
		return result;
	} // 3차원 이상 행렬일 경우 재귀적 계산
} // 행렬식 계산

void calMatDet(Mat *mat) {
	int result, i;
	for (i = 0; i < mat_size; i++) {
		if (!isSquare(mat[i].row, mat[i].column)) {
			printf("행렬 %c는 square matrix가 아니므로 행렬식을 계산할 수 없습니다.\n\n", mat[i].name);
		} // 행렬식 계산 불가능할 때
		else {
			result = moreDet(mat[i].arr, mat[i].row, mat[i].column);
			printf("행렬 %c의 determinant: %d\n\n", mat[i].name, result);
		} // 행렬식 계산 가능할 때
	}
	printf("\n");
} // 파일에 저장된 모든 행렬의 행렬식 계산