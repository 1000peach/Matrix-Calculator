#pragma once
#define TRUE 1
#define FALSE 0

int mat_size; // 파일 load할 때 저장된 행렬 개수 저장
int sys_size; // 파일 load할 때 저장된 Linear System 개수 저장
int r_mat_size; //rref 출력할 행렬 저장

typedef struct Mat {
	char name;
	int row, column;
	int **arr;
} Mat; // 기본 행렬 구조체 정의

typedef struct PartMat {
	char *part;
	int scala;
	int row, column;
	int **arr;
} PartMat; // 계산식에서 피연산자가 갖는 구조체 정의

typedef struct LinearSystem {
	int originDet;
	int **coe_arr;
	int *vec_arr;
	int row_size;
	int col_size;
	int *unknown;
	double *solution;
} LinearSystem; // 하나의 Linear System이 갖는 정보 구조체 정의

int** allocArr(int row, int col);
void freeArr(int **arr, int row);
// 메모리 할당 함수

void inputMat();
Mat* loadMat(Mat mat[]);
void printMat(Mat mat);
int searchMat(Mat* mat, char name, int mat_size);
// 행렬 처리 함수