#pragma once
#include "mat.h"

LinearSystem* loadSystem(LinearSystem L_sys[]);
// Linear System �ҷ����� �Լ�
void cramerRule(LinearSystem *L_sys);
void LinearSolution(LinearSystem* L_sys);
void threeLinearSoltion(LinearSystem L_sys[]);
// Cramer's Rule�� �� ã�� �Լ���