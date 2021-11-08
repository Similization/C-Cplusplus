#pragma once

#include <stdio.h>

typedef struct formula_data {
  long double sum_x;
  long double sum_y;
  long double sum_xy;
  long double sum_x2;
} formula_data;

int fdata_initialize(formula_data*);

formula_data get_formula_datas(double*, long long);
