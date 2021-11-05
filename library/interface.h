#pragma once

#include <stdio.h>

typedef struct formula_data {
  long double sum_x;
  long double sum_y;
  long double sum_xy;
  long double sum_x2;
} formula_data;

int fdata_initialize(formula_data* data) {
  if (!data) {
    printf("Data error: data is empty\n");
    return 1;
  }
  data->sum_xy = data->sum_y = 0;
  data->sum_x2 = data->sum_x = 0;
  return 0;
}

formula_data get_formula_datas(double*, long long);
