#include "interface.h"

formula_data get_formula_datas(double* array, long long a_size) {
  formula_data all_datas;
  fdata_initialize(&all_datas);

  /* empty formula_data for error */
  if (!array) {
    return all_datas;
  }

  for (long long i = 0; i < a_size;) {
    all_datas.sum_x += array[i];
    all_datas.sum_y += array[i + 1];
    all_datas.sum_x2 += array[i] * array[i];
    all_datas.sum_xy += array[i] * array[i + 1];
    i += 2;
  }

  return all_datas;
}
