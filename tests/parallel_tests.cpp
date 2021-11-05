#include "gtest/gtest.h"

extern "C" {
#include "interface.h"
#include "parallel.c"
}

TEST(sum_formula_datas, null_args) { EXPECT_EQ(NULL, sum_formula_datas(NULL)); }

TEST(sum_formula_datas, not_null_args) {
  double* array = new double[100];
  for (int i = 0; i < 100; ++i) {
    array[i] = i + 1;
  }

  formula_data data;
  EXPECT_EQ(0, fdata_initialize(&data));

  thread_info t_info;
  t_info.a_size = 100;
  t_info.array = array;
  t_info.data = &data;
  t_info.thread_num = 0;

  EXPECT_EQ(1, (sum_formula_datas((void*)&t_info) != NULL));
  delete[] array;
}
