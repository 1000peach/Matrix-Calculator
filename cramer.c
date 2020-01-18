#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mat.h"
#include "det.h"

LinearSystem* loadSystem(LinearSystem L_sys[]) {
	char file_n[100] = "./Files/";
	char file_temp[100];
	FILE *fp;
	int i = 0, j = 0, p = 0, q = 0;

	printf("\nLinear System이 저장된 파일명을 입력하세요: ");
	scanf("%s", file_temp);
	strcat(file_n, file_temp);
	fp = fopen(strcat(file_n, ".txt"), "r");
	while (!fp) {
		printf("\n존재하지 않는 파일입니다. 올바른 파일명을 입력해주세요: ");
		scanf("%s", file_n);
		fp = fopen(strcat(file_n, ".txt"), "r");
	} // 파일명 입력 받음

	printf("\nLinear System의 개수를 입력하세요: ");
	scanf("%d", &sys_size);

	for (i = 0; i < sys_size; i++) {
		if (feof(fp))
			break;
		fscanf(fp, "%d %d", &L_sys[i].row_size, &L_sys[i].col_size);
		L_sys[i].coe_arr = allocArr(L_sys[i].row_size, L_sys[i].col_size);
		L_sys[i].vec_arr = (int *)malloc(L_sys[i].row_size * sizeof(int));

		for (p = 0; p < L_sys[i].row_size; p++) {
			for (q = 0; q < L_sys[i].col_size; q++) {
				if (feof(fp))
					break;
				if (q < L_sys[i].col_size - 1) {
					fscanf(fp, "%d ", &L_sys[i].coe_arr[p][q]);
				}
				else {
					fscanf(fp, "%d | %d", &L_sys[i].coe_arr[p][q], &L_sys[i].vec_arr[p]);
				}
			}
		}
		L_sys[i].originDet = moreDet(L_sys[i].coe_arr, L_sys[i].row_size, L_sys[i].col_size);
		L_sys[i].solution = (double *)malloc(L_sys[i].col_size * sizeof(double));
	} // 파일에서 Linear System 읽어 들이고 행렬식까지 계산하여 저장
	fclose(fp);
	return L_sys;
}

void cramerRule(LinearSystem *L_sys) {
	int **temp_arr;
	int i, j, k;
	int modi_det;

	temp_arr = allocArr(L_sys->row_size, L_sys->col_size);
	for (k = 0; k < L_sys->row_size; k++) {
		for (i = 0; i < L_sys->row_size; i++) {
			for (j = 0; j < L_sys->col_size; j++)
				temp_arr[i][j] = L_sys->coe_arr[i][j];
		} // 현재 coefficient 배열을 임시 배열에 복사
		for (i = 0; i < L_sys->row_size; i++) {
			temp_arr[i][k] = L_sys->vec_arr[i];
		} // vector b 값을 unknown value에 맞는 column으로 복사

		modi_det = (int)moreDet(temp_arr, L_sys->row_size, L_sys->col_size);
		L_sys->solution[k] = (double)modi_det / (double)L_sys->originDet; // 행렬식 계산하여 Cramer's rule 적용
	}
}

void LinearSolution(LinearSystem *L_sys) {
	int i, j;
	int row, col;

	row = L_sys->row_size;
	col = L_sys->col_size;
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (L_sys->coe_arr[i][j] != 0) {
				if (j != 0) {
					if (L_sys->coe_arr[i][j] >= 1 || L_sys->coe_arr[i][j] == 0) {
						printf("+");
					}
					else if (L_sys->coe_arr[i][j] == -1) {
						printf("-");
					}
				}
				if (L_sys->coe_arr[i][j] != 1 && L_sys->coe_arr[i][j] != -1) {
					printf("%d", L_sys->coe_arr[i][j]);
				}
				printf("%c", 'a' + j);
			}
		}
		printf("=%d\n", L_sys->vec_arr[i]);
	} // Linear Equation으로 나눠 Linear System을 표현

	if (isSquare(L_sys->row_size, L_sys->col_size)) {
		if (L_sys->originDet == 0) {
			printf("\n=> Not solvable using Cramer’s rule (determinant = 0)\n\n");
			return;
		}
	}
	else {
		printf("\n=> Not solvable using Cramer’s rule (not square matrix)\n\n");
		return;
	} // Cramer's rule 적용 가능한 지 판단

	cramerRule(L_sys); // Cramer's rule 적용 
	printf("\n=> Solution: ");
	for (i = 0; i < L_sys->row_size; i++) {
		printf("%c = %.2f", 'a' + i, L_sys->solution[i]);
		(i < L_sys->row_size - 1) ? printf(" / ") : printf("\n\n");
	}
} // Linear System을 Linear Equation으로 표현 후 cramerRule 이용해 찾은 해를 출력

void threeLinearSoltion(LinearSystem L_sys[]) {
	int i;
	printf("\n");
	for (i = 0; i < sys_size; i++) {
		printf("** %d번 Linear System**\n\n", i + 1);
		LinearSolution(&L_sys[i]);
	}
	sys_size = 0;
} // 파일에 저장된 3개의 Linear System의 해 찾음