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
} // ��Ľ� ��� ���� ���� ��ȯ (square matrix �Ǵ�)

int twoDet(int **arr) {
	return (arr[0][0] * arr[1][1]) - (arr[0][1] * arr[1][0]);
} // 2���� ����� ��Ľ� ���

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
} // 3���� ����� ��Ľ� ��� (ù��° row �����Ͽ� cofactor �̿��� ���)

int moreDet(int **arr, int row, int col) {
	int index, scala = 1;
	int **temp, result;
	int i, j, p = 0, q = 0;

	if (row < 2) {
		return arr[0][0];
	} // ��� ��� �ϳ��� ��
	else if (row < 3) {
		return twoDet(arr); // 2���� ����� ��
	}
	else if (row < 4) {
		return threeDet(arr);
	} // 3���� ����� ��
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
	} // 3���� �̻� ����� ��� ����� ���
} // ��Ľ� ���

void calMatDet(Mat *mat) {
	int result, i;
	for (i = 0; i < mat_size; i++) {
		if (!isSquare(mat[i].row, mat[i].column)) {
			printf("��� %c�� square matrix�� �ƴϹǷ� ��Ľ��� ����� �� �����ϴ�.\n\n", mat[i].name);
		} // ��Ľ� ��� �Ұ����� ��
		else {
			result = moreDet(mat[i].arr, mat[i].row, mat[i].column);
			printf("��� %c�� determinant: %d\n\n", mat[i].name, result);
		} // ��Ľ� ��� ������ ��
	}
	printf("\n");
} // ���Ͽ� ����� ��� ����� ��Ľ� ���