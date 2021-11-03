#include "gtest/gtest.h"

extern "C" {
#include "consist.c"
#include "interface.h"
}

TEST(fdata_initialize, null_data) { EXPECT_EQ(1, fdata_initialize(NULL)); }

TEST(fdata_initialize, not_null_data) {
  formula_data some_data;
  EXPECT_EQ(0, fdata_initialize(&some_data));
}

TEST(get_formula_datas, null_array) {
  formula_data this_data = get_formula_datas(NULL, 0);
  EXPECT_EQ(0, this_data.sum_x);
  EXPECT_EQ(0, this_data.sum_y);
  EXPECT_EQ(0, this_data.sum_xy);
  EXPECT_EQ(0, this_data.sum_x2);
}

TEST(get_formula_datas, not_null_array) {
  long long a_size = 4;
  double* array = (double*)malloc(sizeof(double) * a_size);
  for (long long i = 0; i < a_size; ++i) {
    array[i] = i + 1;
  }  // 1 2 3 4
  formula_data this_data = get_formula_datas(array, a_size);
  EXPECT_EQ(4, this_data.sum_x);
  EXPECT_EQ(6, this_data.sum_y);
  EXPECT_EQ(14, this_data.sum_xy);
  EXPECT_EQ(10, this_data.sum_x2);
  free(array);
}