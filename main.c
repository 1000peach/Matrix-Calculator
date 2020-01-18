#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mat.h"
#include "det.h"
#include "cal.h"
#include "cramer.h"
#include "RREF.h"

int main() {
	char key;
	Mat *mat, *r_mat;
	LinearSystem *L_sys;

	mat_size = 0;
	r_mat_size = 0;

	mat = (Mat *)malloc(20 * sizeof(Mat));
	r_mat = (Mat *)malloc(20 * sizeof(Mat));

	L_sys = (LinearSystem *)malloc(20 * sizeof(LinearSystem));

	do {
		printf(">> 행렬 연산 프로그램 <<\n\n");
		printf("1: 행렬 입력\n\n2: 연산 시작\n\n3: 행렬식 계산\n\n4: 해 찾기(Cramer's rule)\n\n5. REF and RREF 구하기\n\nE or e: 프로그램 종료\n\n");

		printf("원하는 위의 메뉴를 입력하세요: ");
		scanf(" %c", &key);
		switch (key)
		{
		case '1': // 행렬 입력
			inputMat();
			break;
		case '2': // 행렬 연산
			mat = loadMat(mat);
			calMat(mat);
			break;
		case '3': // 행렬식 계산
			mat = loadMat(mat);
			calMatDet(mat);
			break;
		case '4': // Cramer's Rule 이용해 Linear System Solution 찾기
			L_sys = loadSystem(L_sys);
			threeLinearSoltion(L_sys);
			break;
		case '5':
			r_mat = loadMat(r_mat);
			REFandRREF(r_mat);
			break;
		case 'e':
		case 'E': // 프로그램 종료
			printf("\n프로그램이 종료되었습니다.\n");
			break;
		default: // 이외 메뉴 입력 시
			printf("\n올바른 메뉴를 입력해주세요!\n");
			break;
		}
	} while (key != 'e' && key != 'E');

	return 0;
}