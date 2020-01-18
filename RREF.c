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
		} // 현재 row가 zero row일 시 맨 마지막 row와 위치 변경
		flag = 0;
	}
} // 행렬에 zero row 있을 시 non-zero row 밑으로 보냄

void startRREF(double **mat, char name, int row, int col) {
	double *temp = (double *)malloc(sizeof(double) * col); // 연산 하는 행 저장 배열
	double *div_arr = (double *)malloc(sizeof(double) * col); // temp를 활용해 ERO 배열 저장
	double div; // 나눌 값 저장
	int i, j, r, c, p, k; // 반복 변수

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
			} // zero row일 때는 연산 하지 않음
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
				} // pivot이 있는 row의 윗 행들이 0 값이 아니면 ERO 연산
			}
		}
	}
	printf("\n");
	printf("행렬 %C의 RREF:\n", name);
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (mat[i][j] - (int)mat[i][j] != 0) {
				printf("%.1f ", mat[i][j]);
			} // RREF 요소가 실수일 때
			else {
				printf("%d ", (int)mat[i][j]);
			} // RREF 요소가 정수일 때
		}
		printf("\n");
	}
	printf("\n");
} // 행렬의 아래 -> 위 순으로 ERO 수행

void startREF(Mat *mat) { // 행렬의 위 -> 아래 순으로 ERO 수행
	double **temp_mat = (double **)malloc(sizeof(double *) * mat->row); // REF 값 저장 배열
	double *temp = (double *)malloc(sizeof(double) * mat->column); // 연산 하는 행 저장 배열
	double *div_arr = (double *)malloc(sizeof(double) * mat->column); // temp를 활용해 ERO 배열 저장 
	double t, div = 0; // 나눌 값, 나눠야 하는 요소 등 저장

	int r, c; // pivot의 index 저장
	int i, j, k, p, w, u; // 반복 변수

	mat = changeZero(mat); // 연산 전 zero row 처리
	for (i = 0; i < mat->row; i++) {
		temp_mat[i] = (double *)malloc(sizeof(double) * mat->column);
	}
	for (i = 0; i < mat->row; i++) {
		for (j = 0; j < mat->column; j++) {
			temp_mat[i][j] = mat->arr[i][j];
		}
	} // 파일에서 읽어온 행렬 mat를 double 배열로 복사 (REF 값이 실수가 될 수 있으므로)
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
			} // 위에서부터 행렬의 pivot 찾고 index 저장
			if (t != 1 && t != 0) {
				for (j = c; j < mat->column; j++) {
					if (temp_mat[r][j] != 0) {
						temp_mat[r][j] /= t;
					}
				}
			} // pivot이 1이 아니면 1로 되게 행 전체를 나눔
			for (j = c; j < mat->column; j++) {
				temp[j] = temp_mat[r][j];
				div_arr[j] = temp_mat[r][j];
			} // 연산할 행렬을 찾고 다른 배열에 복사
			for (i = r + 1; i < mat->row; i++) {
				div = temp_mat[r][c];
				div = (temp_mat[i][c] / div); // 1로 만들기 위해 연산
				div *= -1;
				for (k = c; k < mat->column; k++) {
					div_arr[k] *= div; // 연산 값을 적용할 행에 연산
					temp_mat[i][k] += div_arr[k]; // 연산을 마친 dir_arr를 temp_mat에 ERO 연산
				}
				for (p = c; p < mat->column; p++) {
					div_arr[p] = temp[p];
				} // 다음 연산 위해 변형시켰던 div_arr에 temp를 복사하면서 원본으로 돌아옴
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
	printf("행렬 %C의 REF:\n", mat->name); // REF 출력
	for (i = 0; i < mat->row; i++) {
		for (j = 0; j < mat->column; j++) {
			if (temp_mat[i][j] - (int)temp_mat[i][j] != 0) {
				printf("%.1f ", temp_mat[i][j]);
			} // REF 요소가 실수일 때
			else {
				printf("%d ", (int)temp_mat[i][j]);
			} // REF 요소가 정수일 때
		}
		printf("\n");
	}
	startRREF(&temp_mat[0], mat->name, mat->row, mat->column); // REF 후 RREF 수행
}

void REFandRREF(Mat *mat) {
	int i;
	printf("---------- REF, RREF 연산 결과 ----------\n\n");
	for (i = 0; i < mat_size; i++) {
		startREF(&mat[i]);
		printf("-----------------------\n");
	}
	printf("\n");
} // 파일에서 읽어온 행렬의 REF, RREF 연산