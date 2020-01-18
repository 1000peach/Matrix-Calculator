#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mat.h"

int** allocArr(int row, int col) {
	int **arr, i;
	arr = (int **)malloc(row * sizeof(int *));
	for (i = 0; i < row; i++) {
		arr[i] = (int *)malloc(col * sizeof(int));
	}
	return arr;
} // row, col ����ŭ 2���� �迭 ���� �Ҵ�

void freeArr(int **arr, int row) {
	int i;
	for (i = 0; i < row; i++) {
		free(arr[i]);
	}
	free(arr);
} // 2���� �迭���� �Ҵ�� �޸� ����

void inputMat() {
	char file_n[100] = "./Files/";
	char file_temp[100];
	int **arr;
	int row, column, i, j, k;
	char name;

	printf("\n����� ������ ���ϸ��� �Է��ϼ���: ");
	scanf("%s", file_temp);
	strcat(file_n, file_temp);
	FILE *fp = fopen(strcat(file_n, ".txt"), "a");

	for (k = 0; k < 3; k++) {
		printf("\n%d�� ����� �̸�, row, column�� �Է��ϼ���:\n", k + 1);
		scanf(" %c %d %d", &name, &row, &column);
		arr = allocArr(row, column);

		printf("\n����� ��Ҹ� ��� ���� ���� �Է��ϼ���:\n");
		for (i = 0; i < row; i++) {
			for (j = 0; j < column; j++) {
				scanf("%d", &arr[i][j]);
			}
		}
		fprintf(fp, "%c %d %d\n", name, row, column);
		for (i = 0; i < row; i++) {
			for (j = 0; j < column; j++) {
				fprintf(fp, "%d ", arr[i][j]);
			}
			fprintf(fp, "\n");
		}
		freeArr(arr, row);
	}
	fclose(fp);
	printf("%s ���Ͽ� ��� 3���� ���������� �����߽��ϴ�!\n\n", file_n);
	return;
} // ���Ͽ� 3���� ��� ������ �Է� �޾� ����

void printMat(Mat mat) {
	int i, j;
	printf("��� %c: \n", mat.name);
	for (i = 0; i < mat.row; i++) {
		for (j = 0; j < mat.column; j++) {
			printf("%d ", mat.arr[i][j]);
		}
		printf("\n");
	}
} // mat�� ����� ��� ���� ���

Mat* loadMat(Mat mat[]) {
	FILE *fp;
	char file_n[100] = "./Files/", name;
	char file_temp[100];
	int row, column;
	int i, j, k;

	printf("\n������ ����� ����� ���ϸ��� �Է��ϼ���: ");
	scanf("%s", file_temp);
	strcat(file_n, file_temp);
	fp = fopen(strcat(file_n, ".txt"), "r");
	while (!fp) {
		printf("\n�������� �ʴ� �����Դϴ�. �ùٸ� ���ϸ��� �Է����ּ���: ");
		scanf("%s", file_n);
		fp = fopen(strcat(file_n, ".txt"), "r");
	} // ���ϸ� �Է� ����

	for (k = 0; k < 20; k++) {
		if (feof(fp))
			break;
		fscanf(fp, "%c %d %d\n", &name, &row, &column);
		mat[k].name = name;
		mat[k].row = row;
		mat[k].column = column;
		mat[k].arr = allocArr(row, column);
		for (i = 0; i < row; i++) {
			for (j = 0; j < column; j++) {
				fscanf(fp, "%d ", &mat[k].arr[i][j]);
			}
		}
	}
	mat_size = k;
	printf("\n������ ���������� �ҷ��Խ��ϴ�!\n\n");
	for (i = 0; i < mat_size; i++) {
		printMat(mat[i]);
		printf("\n");
	}
	fclose(fp);
	return mat;
} // ����� ���Ͽ��� 3�� ����� ������ �о� ���α׷��� ����

int searchMat(Mat* mat, char name, int mat_size) {
	int i;
	for (i = 0; i < mat_size; i++) {
		if (name == mat[i].name) {
			return i;
		}
	}
	return -1;
} // �Ŀ� �����Ǵ� �̸� ���� ��� ã��