#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mat.h"

int isAdd(PartMat *temp, int size) {
	int i;
	for (i = 0; i < size - 1; i++) {
		if (temp[i].row != temp[i + 1].row || temp[i].column != temp[i + 1].column) {
			return FALSE;
		}
	}
	return TRUE;
} // ���� ���� ���� �Ǵ�

int isMulti(int col, int row) {
	if (col == row)
		return TRUE;
	else
		return FALSE;
} // ���� ���� ���� ���� �˻�

void swapOper(char *swap) {
	if (*swap == '-')
		*swap = '+';
} // scala�� '-'�� �� '+'�� ����

char* divOper(char str[]) {
	char *temp;
	int i, j = 0, size = 0;
	for (i = 0; i < strlen(str); i++) {
		if (str[i] == '+' || str[i] == '-')
			size++;
	}
	temp = (char *)malloc(size * sizeof(char));
	for (i = 0; i < strlen(str); i++) {
		if (str[i] == '+' || str[i] == '-') {
			temp[j] = str[i];
			swapOper(&str[i]); // ���� �� ���� �Լ�
			j++;
		}
	}
	return temp;
} // ���Ŀ��� scala�� �����Ͽ� �迭 ��ȯ

void sumResult(PartMat *temp, int size) {
	int i, j, k;
	if (!isAdd(temp, size)) {
		printf("\n����� ũ�Ⱑ ��ġ���� �ʾ� ���� �� �����ϴ�.\n\n");
		return;
	}
	for (k = 0; k < size - 1; k++) {
		for (i = 0; i < temp[k].row; i++) {
			for (j = 0; j < temp[k].column; j++) {
				temp[k + 1].arr[i][j] = temp[k].arr[i][j] + temp[k + 1].arr[i][j];
			}
		}
	} // ���� ��� �κ�
	printf("\n��� ���:\n");
	for (i = 0; i < temp[size - 1].row; i++) {
		for (j = 0; j < temp[size - 1].column; j++) {
			printf("%d ", temp[size - 1].arr[i][j]);
		}
		printf("\n");
	}
	printf("\n");
} // ���� ���� �Ǵ��� ���� ���

void calMat(Mat mat[]) {
	PartMat *temp;
	char *exp, scanf_exp[100], *part[100], *oper;
	int i = 0, j, p, q, r, k;
	int row, col, part_size = 0;
	int index, sum = 0, scala = 1;
	int temp_temp[100][100];
	char temp2, temp3;

	printf("���ÿ� ���� ��� ���� �Է����ּ��� ex) 2A+3B+5C\n=> ");
	scanf("%s", scanf_exp);

	if (scanf_exp[0] != '+' && scanf_exp[0] != '-') {
		temp2 = scanf_exp[0];
		scanf_exp[0] = '+';
		for (i = 1; i <= strlen(scanf_exp); i++) {
			temp3 = scanf_exp[i];
			scanf_exp[i] = temp2;
			temp2 = temp3;
		} // �Է��� ���� ù �κп� scala ������ ��� scala ���� ���� '+' �߰��� ���·� ����
	} // ex) 2A-3B+5C -> +2A-3B+5C
	oper = divOper(scanf_exp); // �Ŀ��� scala ���� �� ���Ŀ��� scala ��ȣ ���� ex) +2A+3B+5C

	if (scanf_exp[0] == '+' || scanf_exp[0] == '-') {
		for (i = 0; i < strlen(scanf_exp) - 1; i++) {
			scanf_exp[i] = scanf_exp[i + 1];
		}
		scanf_exp[strlen(scanf_exp) - 1] = NULL;
	} // scala ���� �� ���� �����Ƿ� ù�κ� scala ������ ���� ���·� ����
	  // ex) +2A+3B+5C -> 2A+3B+5C
	i = 0;
	exp = strtok(scanf_exp, "+");
	part[i++] = exp;
	while (exp != NULL) {
		exp = strtok(NULL, "+");
		part[i] = exp;
		i++;
		part_size++;
	} // ����� ���Ǽ� ���� ������ '+'�� �������� ���ڿ� �и�-> �ǿ�����
	  // ex) part[0] = 2A, part[1] = 3B, part[2] = 5C

	temp = (PartMat *)malloc(part_size * sizeof(PartMat)); // �и��� ���ڿ�(2A) �ǿ�����, ���Ե� ����� ũ��, scala�� ���� ����ü
	for (i = 0; i < part_size; i++) {
		temp[i].scala = (oper[i] == '-') ? -1 : 1; // �и��� ���ڿ� �ǿ������� scala�� �ʱ�ȭ
		temp[i].part = part[i];
		temp[i].arr = NULL;
	} // temp[i].part ���� �ǿ����� ���� ex) 2A, 3B..

	for (k = 0; k < part_size; k++) { // temp[k]�� �ǿ����� ���-> part[i]�� �ϳ��� �˻��ϸ� ����� �� temp[k].arr�� ����
		for (i = 0; i < strlen(temp[k].part); i++) {
			if ('0' <= temp[k].part[i] && temp[k].part[i] <= '9') {
				scala = temp[k].part[i] - '0';
				temp[k].scala = temp[k].scala * scala;

				index = searchMat(mat, temp[k].part[i + 1], mat_size);
				if (index == -1) {
					printf("����İ� ��ġ�ϴ� ����� �����ϴ�.\n\n");
					return;
				}
				temp[k].row = mat[index].row;
				temp[k].column = mat[index].column;
				temp[k].arr = allocArr(temp[k].row, temp[k].column);
				// ���ڿ� �����Ǵ� ��� ã�Ƽ� temp[k]�� ���� ex) 2A���� A �̸� ���� ��� ���� ã�ƿ�

				for (p = 0; p < temp[k].row; p++) {
					for (q = 0; q < temp[k].column; q++) {
						temp[k].arr[p][q] = temp[k].scala * mat[index].arr[p][q];
					}
				}
			} // �ǿ������� ���� �ϳ��� ������ ��� scala ��
			else { // �ǿ������� ���� �ϳ��� ������ ��� ���� ��� ã�� ����
				if (temp[k].arr == NULL) {
					index = searchMat(mat, temp[k].part[i], mat_size);
					if (index == -1) {
						printf("����İ� ��ġ�ϴ� ����� �����ϴ�.\n\n");
						return;
					}
					temp[k].row = mat[index].row;
					temp[k].column = mat[index].column;

					temp[k].arr = allocArr(temp[k].row, temp[k].column);
					for (p = 0; p < temp[k].row; p++) {
						for (q = 0; q < temp[k].column; q++) {
							temp[k].arr[p][q] = mat[index].arr[p][q] * temp[k].scala;
						}
					}
				}  // �ǿ����� ����ü�� ����� �迭 ���� ��� �ʱ�ȭ
				if (temp[k].part[i + 1] != NULL) { // �ڿ� ���� ����� ���� ���
					index = searchMat(mat, temp[k].part[i + 1], mat_size);
					if (index == -1) {
						printf("����İ� ��ġ�ϴ� ����� �����ϴ�.\n\n");
						return;
					}
					if (!isMulti(temp[k].column, mat[index].row)) {
						printf("\n������ ������ ���� ���� ũ�Ⱑ ��ġ���� �ʾ� ���� �� �����ϴ�.\n\n");
						return;
					} // ���� ���� �Ǵ�
					row = temp[k].row; // ��� ����� ��
					col = mat[index].column; // ��� ����� ��

					for (r = 0; r < temp[k].row; r++) {
						for (j = 0; j < mat[index].column; j++) {
							sum = 0;
							for (p = 0; p < temp[k].column; p++) {
								sum += temp[k].arr[r][p] * mat[index].arr[p][j];
							}
							temp_temp[r][j] = sum;
						}
					} // ����� �迭�� ���� ����� ������ �ӽ� �迭�� ����
					freeArr(temp[k].arr, temp[k].row);
					temp[k].row = row;
					temp[k].column = col;
					temp[k].arr = allocArr(temp[k].row, temp[k].column);
					// ���� ���� ��� ���� ���� ��� ���� �� ���� �Ҵ� ���� 
					for (p = 0; p < temp[k].row; p++) {
						for (q = 0; q < temp[k].column; q++) {
							temp[k].arr[p][q] = temp_temp[p][q];
						}
					} // ���� �������Ƿ� ���� �ǿ����� ����ü�� �ӽ� �迭 ������ �Ű� �����
				}
			}
		}
	}
	sumResult(temp, part_size); // ������ ��� ����� ����
	return;
}