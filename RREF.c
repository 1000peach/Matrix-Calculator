#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RREF.h"
#include "mat.h"

Mat *changeZero(Mat *mat) {
	int i, j, p;
	int *temp = (int *)malloc(sizeof(int) * mat->column);
	int index, flag = 0;
	for (i = 0; i < mat->row; i++) {
		for (j = 0; j < mat->column; j++) {
			if (mat->arr[i][j] != 0) {
				flag = 1;
			}
		}
		if (flag == 0 && i != mat->row - 1) {
			for (p = 0; p < mat->column; p++) {
				temp[p] = mat->arr[mat->row - 1][p];
				mat->arr[mat->row - 1][p] = mat->arr[i][p];
				mat->arr[i][p] = temp[p];
			}
		} // ���� row�� zero row�� �� �� ������ row�� ��ġ ����
		flag = 0;
	}
} // ��Ŀ� zero row ���� �� non-zero row ������ ����

void startRREF(double **mat, char name, int row, int col) {
	double *temp = (double *)malloc(sizeof(double) * col); // ���� �ϴ� �� ���� �迭
	double *div_arr = (double *)malloc(sizeof(double) * col); // temp�� Ȱ���� ERO �迭 ����
	double div; // ���� �� ����
	int i, j, r, c, p, k; // �ݺ� ����

	if (row > 1) {
		for (i = row - 1; i >= 1; i--) {
			r = -1;
			c = -1;
			for (j = 0; j < col; j++) {
				if (mat[i][j] != 0) {
					r = i;
					c = j;
					break;
				}
			}
			if (r == -1 || c == -1) {
				continue;
			} // zero row�� ���� ���� ���� ����
			else {
				for (p = c; p < col; p++) {
					temp[p] = mat[r][p];
					div_arr[p] = mat[r][p];
				}
				for (k = r - 1; k >= 0; k--) {
					if (mat[k][c] != 0) {
						div = mat[k][c] * -1;
						for (p = c; p < col; p++) {
							div_arr[p] *= div;
							mat[k][p] += div_arr[p];
							div_arr[p] = temp[p];
						}
					}
					else {
						continue;
					}
				} // pivot�� �ִ� row�� �� ����� 0 ���� �ƴϸ� ERO ����
			}
		}
	}
	printf("\n");
	printf("��� %C�� RREF:\n", name);
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (mat[i][j] - (int)mat[i][j] != 0) {
				printf("%.1f ", mat[i][j]);
			} // RREF ��Ұ� �Ǽ��� ��
			else {
				printf("%d ", (int)mat[i][j]);
			} // RREF ��Ұ� ������ ��
		}
		printf("\n");
	}
	printf("\n");
} // ����� �Ʒ� -> �� ������ ERO ����

void startREF(Mat *mat) { // ����� �� -> �Ʒ� ������ ERO ����
	double **temp_mat = (double **)malloc(sizeof(double *) * mat->row); // REF �� ���� �迭
	double *temp = (double *)malloc(sizeof(double) * mat->column); // ���� �ϴ� �� ���� �迭
	double *div_arr = (double *)malloc(sizeof(double) * mat->column); // temp�� Ȱ���� ERO �迭 ���� 
	double t, div = 0; // ���� ��, ������ �ϴ� ��� �� ����

	int r, c; // pivot�� index ����
	int i, j, k, p, w, u; // �ݺ� ����

	mat = changeZero(mat); // ���� �� zero row ó��
	for (i = 0; i < mat->row; i++) {
		temp_mat[i] = (double *)malloc(sizeof(double) * mat->column);
	}
	for (i = 0; i < mat->row; i++) {
		for (j = 0; j < mat->column; j++) {
			temp_mat[i][j] = mat->arr[i][j];
		}
	} // ���Ͽ��� �о�� ��� mat�� double �迭�� ���� (REF ���� �Ǽ��� �� �� �����Ƿ�)
	if (mat->row > 1) {
		for (w = 0; w < mat->row - 1; w++) {
			t = temp_mat[w][w];
			if (t == 0) {
				for (u = w; u < mat->column; u++) {
					if (temp_mat[w][u] != 0) {
						t = temp_mat[w][u];
						r = w;
						c = u;
						break;
					}
				}
			}
			else {
				r = w;
				c = w;
			} // ���������� ����� pivot ã�� index ����
			if (t != 1 && t != 0) {
				for (j = c; j < mat->column; j++) {
					if (temp_mat[r][j] != 0) {
						temp_mat[r][j] /= t;
					}
				}
			} // pivot�� 1�� �ƴϸ� 1�� �ǰ� �� ��ü�� ����
			for (j = c; j < mat->column; j++) {
				temp[j] = temp_mat[r][j];
				div_arr[j] = temp_mat[r][j];
			} // ������ ����� ã�� �ٸ� �迭�� ����
			for (i = r + 1; i < mat->row; i++) {
				div = temp_mat[r][c];
				div = (temp_mat[i][c] / div); // 1�� ����� ���� ����
				div *= -1;
				for (k = c; k < mat->column; k++) {
					div_arr[k] *= div; // ���� ���� ������ �࿡ ����
					temp_mat[i][k] += div_arr[k]; // ������ ��ģ dir_arr�� temp_mat�� ERO ����
				}
				for (p = c; p < mat->column; p++) {
					div_arr[p] = temp[p];
				} // ���� ���� ���� �������״� div_arr�� temp�� �����ϸ鼭 �������� ���ƿ�
			}
		}
		i = mat->row - 1;
		k = 0;
		for (j = c + 1; j < mat->column; j++) {
			if (temp_mat[i][j] != 0 && temp_mat[i][j] != 1) {
				div = temp_mat[i][j];
				for (k = j; k < mat->column; k++) {
					temp_mat[i][k] /= div;
				}
				break;
			}
		}
	}
	printf("��� %C�� REF:\n", mat->name); // REF ���
	for (i = 0; i < mat->row; i++) {
		for (j = 0; j < mat->column; j++) {
			if (temp_mat[i][j] - (int)temp_mat[i][j] != 0) {
				printf("%.1f ", temp_mat[i][j]);
			} // REF ��Ұ� �Ǽ��� ��
			else {
				printf("%d ", (int)temp_mat[i][j]);
			} // REF ��Ұ� ������ ��
		}
		printf("\n");
	}
	startRREF(&temp_mat[0], mat->name, mat->row, mat->column); // REF �� RREF ����
}

void REFandRREF(Mat *mat) {
	int i;
	printf("---------- REF, RREF ���� ��� ----------\n\n");
	for (i = 0; i < mat_size; i++) {
		startREF(&mat[i]);
		printf("-----------------------\n");
	}
	printf("\n");
} // ���Ͽ��� �о�� ����� REF, RREF ����