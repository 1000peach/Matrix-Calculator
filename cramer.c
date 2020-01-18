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

	printf("\nLinear System�� ����� ���ϸ��� �Է��ϼ���: ");
	scanf("%s", file_temp);
	strcat(file_n, file_temp);
	fp = fopen(strcat(file_n, ".txt"), "r");
	while (!fp) {
		printf("\n�������� �ʴ� �����Դϴ�. �ùٸ� ���ϸ��� �Է����ּ���: ");
		scanf("%s", file_n);
		fp = fopen(strcat(file_n, ".txt"), "r");
	} // ���ϸ� �Է� ����

	printf("\nLinear System�� ������ �Է��ϼ���: ");
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
	} // ���Ͽ��� Linear System �о� ���̰� ��Ľı��� ����Ͽ� ����
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
		} // ���� coefficient �迭�� �ӽ� �迭�� ����
		for (i = 0; i < L_sys->row_size; i++) {
			temp_arr[i][k] = L_sys->vec_arr[i];
		} // vector b ���� unknown value�� �´� column���� ����

		modi_det = (int)moreDet(temp_arr, L_sys->row_size, L_sys->col_size);
		L_sys->solution[k] = (double)modi_det / (double)L_sys->originDet; // ��Ľ� ����Ͽ� Cramer's rule ����
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
	} // Linear Equation���� ���� Linear System�� ǥ��

	if (isSquare(L_sys->row_size, L_sys->col_size)) {
		if (L_sys->originDet == 0) {
			printf("\n=> Not solvable using Cramer��s rule (determinant = 0)\n\n");
			return;
		}
	}
	else {
		printf("\n=> Not solvable using Cramer��s rule (not square matrix)\n\n");
		return;
	} // Cramer's rule ���� ������ �� �Ǵ�

	cramerRule(L_sys); // Cramer's rule ���� 
	printf("\n=> Solution: ");
	for (i = 0; i < L_sys->row_size; i++) {
		printf("%c = %.2f", 'a' + i, L_sys->solution[i]);
		(i < L_sys->row_size - 1) ? printf(" / ") : printf("\n\n");
	}
} // Linear System�� Linear Equation���� ǥ�� �� cramerRule �̿��� ã�� �ظ� ���

void threeLinearSoltion(LinearSystem L_sys[]) {
	int i;
	printf("\n");
	for (i = 0; i < sys_size; i++) {
		printf("** %d�� Linear System**\n\n", i + 1);
		LinearSolution(&L_sys[i]);
	}
	sys_size = 0;
} // ���Ͽ� ����� 3���� Linear System�� �� ã��