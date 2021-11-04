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
// a = 1, b = 1  ---  y = 1*x + 1
TEST(get_formula_datas, 4_datas) {
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
// a = 2, b = 0  ---  y = 2*x + 0
TEST(get_formula_datas, 100_datas) {
  long long a_size = 100;
  double* array = (double*)malloc(sizeof(double) * a_size);
  for (long long i = 0; i < 50; ++i) {
    array[2 * i] = i + 1;
    array[2 * i + 1] = (i + 1) * 2;
  }  // 1 2 2 4 3 6 4 8 ...
  formula_data res = get_formula_datas(array, a_size);
  long double coeff_a = (500 * res.sum_xy - res.sum_x * res.sum_y) /
                        (500 * res.sum_x2 - res.sum_x * res.sum_x);
  long double coeff_b = (res.sum_y - coeff_a * res.sum_x) / 500;
  EXPECT_EQ(2, coeff_a);
  EXPECT_EQ(0, coeff_b);
  free(array);
}
// a = 1/2, b = 2  ---  y = 1/2*x + 2
TEST(get_formula_datas, 1000_datas) {
  long long a_size = 1000;
  double* array = (double*)malloc(sizeof(double) * a_size);
  for (long long i = 0; i < 500; ++i) {
    array[2 * i] = 2 * i - 2;
    array[2 * i + 1] = i + 1;
  }  // -2 1 0 2 2 3 4 4 ...
  formula_data res = get_formula_datas(array, a_size);
  long double coeff_a = (500 * res.sum_xy - res.sum_x * res.sum_y) /
                        (500 * res.sum_x2 - res.sum_x * res.sum_x);
  long double coeff_b = (res.sum_y - coeff_a * res.sum_x) / 500;
  EXPECT_EQ(0.5, coeff_a);
  EXPECT_EQ(2, coeff_b);
  free(array);
}
