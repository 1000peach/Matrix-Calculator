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
} // row, col 값만큼 2차원 배열 동적 할당

void freeArr(int **arr, int row) {
	int i;
	for (i = 0; i < row; i++) {
		free(arr[i]);
	}
	free(arr);
} // 2차원 배열에서 할당된 메모리 해제

void inputMat() {
	char file_n[100] = "./Files/";
	char file_temp[100];
	int **arr;
	int row, column, i, j, k;
	char name;

	printf("\n행렬을 저장할 파일명을 입력하세요: ");
	scanf("%s", file_temp);
	strcat(file_n, file_temp);
	FILE *fp = fopen(strcat(file_n, ".txt"), "a");

	for (k = 0; k < 3; k++) {
		printf("\n%d번 행렬의 이름, row, column을 입력하세요:\n", k + 1);
		scanf(" %c %d %d", &name, &row, &column);
		arr = allocArr(row, column);

		printf("\n행렬의 요소를 행과 열에 맞춰 입력하세요:\n");
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
	printf("%s 파일에 행렬 3개를 성공적으로 저장했습니다!\n\n", file_n);
	return;
} // 파일에 3개의 행렬 정보를 입력 받아 저장

void printMat(Mat mat) {
	int i, j;
	printf("행렬 %c: \n", mat.name);
	for (i = 0; i < mat.row; i++) {
		for (j = 0; j < mat.column; j++) {
			printf("%d ", mat.arr[i][j]);
		}
		printf("\n");
	}
} // mat의 행렬의 모든 원소 출력

Mat* loadMat(Mat mat[]) {
	FILE *fp;
	char file_n[100] = "./Files/", name;
	char file_temp[100];
	int row, column;
	int i, j, k;

	printf("\n연산할 행렬이 저장된 파일명을 입력하세요: ");
	scanf("%s", file_temp);
	strcat(file_n, file_temp);
	fp = fopen(strcat(file_n, ".txt"), "r");
	while (!fp) {
		printf("\n존재하지 않는 파일입니다. 올바른 파일명을 입력해주세요: ");
		scanf("%s", file_n);
		fp = fopen(strcat(file_n, ".txt"), "r");
	} // 파일명 입력 받음

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
	printf("\n파일을 성공적으로 불러왔습니다!\n\n");
	for (i = 0; i < mat_size; i++) {
		printMat(mat[i]);
		printf("\n");
	}
	fclose(fp);
	return mat;
} // 저장된 파일에서 3개 행렬의 정보를 읽어 프로그램에 저장

int searchMat(Mat* mat, char name, int mat_size) {
	int i;
	for (i = 0; i < mat_size; i++) {
		if (name == mat[i].name) {
			return i;
		}
	}
	return -1;
} // 식에 대응되는 이름 가진 행렬 찾음