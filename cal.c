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
} // 덧셈 연산 가능 판단

int isMulti(int col, int row) {
	if (col == row)
		return TRUE;
	else
		return FALSE;
} // 곱셈 연산 가능 유무 검사

void swapOper(char *swap) {
	if (*swap == '-')
		*swap = '+';
} // scala가 '-'면 를 '+'로 변경

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
			swapOper(&str[i]); // 추출 후 변경 함수
			j++;
		}
	}
	return temp;
} // 계산식에서 scala를 추출하여 배열 반환

void sumResult(PartMat *temp, int size) {
	int i, j, k;
	if (!isAdd(temp, size)) {
		printf("\n행렬의 크기가 일치하지 않아 더할 수 없습니다.\n\n");
		return;
	}
	for (k = 0; k < size - 1; k++) {
		for (i = 0; i < temp[k].row; i++) {
			for (j = 0; j < temp[k].column; j++) {
				temp[k + 1].arr[i][j] = temp[k].arr[i][j] + temp[k + 1].arr[i][j];
			}
		}
	} // 덧셈 계산 부분
	printf("\n계산 결과:\n");
	for (i = 0; i < temp[size - 1].row; i++) {
		for (j = 0; j < temp[size - 1].column; j++) {
			printf("%d ", temp[size - 1].arr[i][j]);
		}
		printf("\n");
	}
	printf("\n");
} // 덧셈 유무 판단해 계산식 출력

void calMat(Mat mat[]) {
	PartMat *temp;
	char *exp, scanf_exp[100], *part[100], *oper;
	int i = 0, j, p, q, r, k;
	int row, col, part_size = 0;
	int index, sum = 0, scala = 1;
	int temp_temp[100][100];
	char temp2, temp3;

	printf("예시에 맞춰 계산 식을 입력해주세요 ex) 2A+3B+5C\n=> ");
	scanf("%s", scanf_exp);

	if (scanf_exp[0] != '+' && scanf_exp[0] != '-') {
		temp2 = scanf_exp[0];
		scanf_exp[0] = '+';
		for (i = 1; i <= strlen(scanf_exp); i++) {
			temp3 = scanf_exp[i];
			scanf_exp[i] = temp2;
			temp2 = temp3;
		} // 입력한 계산식 첫 부분에 scala 생략일 경우 scala 추출 위해 '+' 추가한 형태로 변경
	} // ex) 2A-3B+5C -> +2A-3B+5C
	oper = divOper(scanf_exp); // 식에서 scala 추출 및 계산식에서 scala 부호 변경 ex) +2A+3B+5C

	if (scanf_exp[0] == '+' || scanf_exp[0] == '-') {
		for (i = 0; i < strlen(scanf_exp) - 1; i++) {
			scanf_exp[i] = scanf_exp[i + 1];
		}
		scanf_exp[strlen(scanf_exp) - 1] = NULL;
	} // scala 변경 및 추출 했으므로 첫부분 scala 생략한 계산식 형태로 변경
	  // ex) +2A+3B+5C -> 2A+3B+5C
	i = 0;
	exp = strtok(scanf_exp, "+");
	part[i++] = exp;
	while (exp != NULL) {
		exp = strtok(NULL, "+");
		part[i] = exp;
		i++;
		part_size++;
	} // 계산의 편의성 위해 연산자 '+'를 기준으로 문자열 분리-> 피연산자
	  // ex) part[0] = 2A, part[1] = 3B, part[2] = 5C

	temp = (PartMat *)malloc(part_size * sizeof(PartMat)); // 분리한 문자열(2A) 피연산자, 포함된 행렬의 크기, scala를 담을 구조체
	for (i = 0; i < part_size; i++) {
		temp[i].scala = (oper[i] == '-') ? -1 : 1; // 분리한 문자열 피연산자의 scala로 초기화
		temp[i].part = part[i];
		temp[i].arr = NULL;
	} // temp[i].part 마다 피연산자 대입 ex) 2A, 3B..

	for (k = 0; k < part_size; k++) { // temp[k]의 피연산자 계산-> part[i]를 하나씩 검사하며 계산한 후 temp[k].arr에 저장
		for (i = 0; i < strlen(temp[k].part); i++) {
			if ('0' <= temp[k].part[i] && temp[k].part[i] <= '9') {
				scala = temp[k].part[i] - '0';
				temp[k].scala = temp[k].scala * scala;

				index = searchMat(mat, temp[k].part[i + 1], mat_size);
				if (index == -1) {
					printf("연산식과 일치하는 행렬이 없습니다.\n\n");
					return;
				}
				temp[k].row = mat[index].row;
				temp[k].column = mat[index].column;
				temp[k].arr = allocArr(temp[k].row, temp[k].column);
				// 문자에 대응되는 행렬 찾아서 temp[k]에 저장 ex) 2A에서 A 이름 가진 행렬 정보 찾아옴

				for (p = 0; p < temp[k].row; p++) {
					for (q = 0; q < temp[k].column; q++) {
						temp[k].arr[p][q] = temp[k].scala * mat[index].arr[p][q];
					}
				}
			} // 피연산자의 문자 하나가 숫자일 경우 scala 곱
			else { // 피연산자의 문자 하나가 문자일 경우 대응 행렬 찾아 곱함
				if (temp[k].arr == NULL) {
					index = searchMat(mat, temp[k].part[i], mat_size);
					if (index == -1) {
						printf("연산식과 일치하는 행렬이 없습니다.\n\n");
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
				}  // 피연산자 구조체에 저장된 배열 없을 경우 초기화
				if (temp[k].part[i + 1] != NULL) { // 뒤에 곱할 행렬이 있을 경우
					index = searchMat(mat, temp[k].part[i + 1], mat_size);
					if (index == -1) {
						printf("연산식과 일치하는 행렬이 없습니다.\n\n");
						return;
					}
					if (!isMulti(temp[k].column, mat[index].row)) {
						printf("\n곱셈의 조건인 열과 행의 크기가 일치하지 않아 곱할 수 없습니다.\n\n");
						return;
					} // 곱셈 가능 판단
					row = temp[k].row; // 결과 행렬의 행
					col = mat[index].column; // 결과 행렬의 열

					for (r = 0; r < temp[k].row; r++) {
						for (j = 0; j < mat[index].column; j++) {
							sum = 0;
							for (p = 0; p < temp[k].column; p++) {
								sum += temp[k].arr[r][p] * mat[index].arr[p][j];
							}
							temp_temp[r][j] = sum;
						}
					} // 저장된 배열과 다음 행렬을 연산해 임시 배열에 저장
					freeArr(temp[k].arr, temp[k].row);
					temp[k].row = row;
					temp[k].column = col;
					temp[k].arr = allocArr(temp[k].row, temp[k].column);
					// 새로 계산된 행렬 저장 위해 행렬 정보 및 동적 할당 갱신 
					for (p = 0; p < temp[k].row; p++) {
						for (q = 0; q < temp[k].column; q++) {
							temp[k].arr[p][q] = temp_temp[p][q];
						}
					} // 연산 끝났으므로 기존 피연산자 구조체에 임시 배열 데이터 옮겨 덮어씌움
				}
			}
		}
	}
	sumResult(temp, part_size); // 각각의 계산 결과를 더함
	return;
}