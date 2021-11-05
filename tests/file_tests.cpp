#include "gtest/gtest.h"

extern "C" {
#include "file.h"
}

/* ----- initialize array ----- */

TEST(initialize_array, null_array) {
  char file_name[] = "f.txt";
  EXPECT_EQ(1, initialize_array(file_name, NULL, 0));
}

TEST(initialize_array, null_file) {
  EXPECT_EQ(1, initialize_array(NULL, NULL, 0));
}

TEST(initialize_array, wrong_file) {
  char file_name[] = "f.txt";
  double* array = new double[2];
  for (int i = 0; i < 2; ++i) {
    array[i] = (double)(rand() % 20001) / 100 - 100;
  }
  EXPECT_EQ(1, initialize_array(file_name, array, 2));
  delete[] array;
}

TEST(initialize_array, wrong_file_data) {
  char file_name[] = "f.txt";
  FILE* fp = fopen(file_name, "w");
  EXPECT_EQ(1, (fp != NULL));
  double* array = new double[16];
  for (int i = 0; i < 16; ++i) {
    fprintf(fp, "%c", (char)(i + 97));
  }
  fclose(fp);
  EXPECT_EQ(1, initialize_array(file_name, array, 16));
  EXPECT_EQ(0, remove(file_name));
  delete[] array;
}

TEST(initialize_array, correct_array_data) {
  char file_name[] = "f.txt";
  FILE* fp = fopen(file_name, "w");
  EXPECT_EQ(1, (fp != NULL));
  double* array = new double[16];
  for (int i = 0; i < 16; ++i) {
    fprintf(fp, "%lf ", double(i + 1));
  }
  fclose(fp);
  EXPECT_EQ(0, initialize_array(file_name, array, 16));
  for (int i = 0; i < 16; ++i) {
    EXPECT_EQ(i + 1, array[i]);
  }
  EXPECT_EQ(0, remove(file_name));
  delete[] array;
}

/* ----- create and init ----- */

TEST(create_and_init, null_file) { EXPECT_EQ(1, create_and_init(NULL, 0)); }

TEST(create_and_init, wrong_file) {
  char file_name[] = "f.txt";
  EXPECT_EQ(0, create_and_init(file_name, 0));
}

TEST(create_and_init, correct_datas) {
  char file_name[] = "f.txt";
  FILE* fp = fopen(file_name, "w");
  EXPECT_EQ(1, (fp != NULL));
  fclose(fp);
  EXPECT_EQ(0, create_and_init(file_name, 0));
  EXPECT_EQ(0, remove(file_name));
}
