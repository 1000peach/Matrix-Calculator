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
		printf(">> ��� ���� ���α׷� <<\n\n");
		printf("1: ��� �Է�\n\n2: ���� ����\n\n3: ��Ľ� ���\n\n4: �� ã��(Cramer's rule)\n\n5. REF and RREF ���ϱ�\n\nE or e: ���α׷� ����\n\n");

		printf("���ϴ� ���� �޴��� �Է��ϼ���: ");
		scanf(" %c", &key);
		switch (key)
		{
		case '1': // ��� �Է�
			inputMat();
			break;
		case '2': // ��� ����
			mat = loadMat(mat);
			calMat(mat);
			break;
		case '3': // ��Ľ� ���
			mat = loadMat(mat);
			calMatDet(mat);
			break;
		case '4': // Cramer's Rule �̿��� Linear System Solution ã��
			L_sys = loadSystem(L_sys);
			threeLinearSoltion(L_sys);
			break;
		case '5':
			r_mat = loadMat(r_mat);
			REFandRREF(r_mat);
			break;
		case 'e':
		case 'E': // ���α׷� ����
			printf("\n���α׷��� ����Ǿ����ϴ�.\n");
			break;
		default: // �̿� �޴� �Է� ��
			printf("\n�ùٸ� �޴��� �Է����ּ���!\n");
			break;
		}
	} while (key != 'e' && key != 'E');

	return 0;
}