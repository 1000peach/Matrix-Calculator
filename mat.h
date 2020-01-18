#pragma once
#define TRUE 1
#define FALSE 0

int mat_size; // ���� load�� �� ����� ��� ���� ����
int sys_size; // ���� load�� �� ����� Linear System ���� ����
int r_mat_size; //rref ����� ��� ����

typedef struct Mat {
	char name;
	int row, column;
	int **arr;
} Mat; // �⺻ ��� ����ü ����

typedef struct PartMat {
	char *part;
	int scala;
	int row, column;
	int **arr;
} PartMat; // ���Ŀ��� �ǿ����ڰ� ���� ����ü ����

typedef struct LinearSystem {
	int originDet;
	int **coe_arr;
	int *vec_arr;
	int row_size;
	int col_size;
	int *unknown;
	double *solution;
} LinearSystem; // �ϳ��� Linear System�� ���� ���� ����ü ����

int** allocArr(int row, int col);
void freeArr(int **arr, int row);
// �޸� �Ҵ� �Լ�

void inputMat();
Mat* loadMat(Mat mat[]);
void printMat(Mat mat);
int searchMat(Mat* mat, char name, int mat_size);
// ��� ó�� �Լ�