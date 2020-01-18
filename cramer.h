#pragma once
#include "mat.h"

LinearSystem* loadSystem(LinearSystem L_sys[]);
// Linear System 불러오는 함수
void cramerRule(LinearSystem *L_sys);
void LinearSolution(LinearSystem* L_sys);
void threeLinearSoltion(LinearSystem L_sys[]);
// Cramer's Rule로 해 찾는 함수들