#include "interface.h"

int fdata_initialize(formula_data* data) {
  if (!data) {
    printf("Data error: data is empty\n");
    return 1;
  }
  data->sum_xy = data->sum_y = 0;
  data->sum_x2 = data->sum_x = 0;
  return 0;
}
