#include "gtest/gtest.h"

extern "C" {
#include "my_string.h"
}
// make_string()
TEST(make_string, not_null_input) {
  char buffer[] = {'D', 'o', 'r', 'a', '\n'};
  struct String string;
  make_string(&string, buffer);

  EXPECT_EQ(strlen(buffer), string.length);

  free(string.data);
}

TEST(make_string, null_string_input) {
  struct String string;
  int err = make_string(&string, NULL);
  EXPECT_EQ(err, 1);
}

TEST(make_string, null_buffer_input) {
  char buffer[] = {'D', 'o', 'r', 'a', '\n'};
  int err = make_string(NULL, buffer);
  EXPECT_EQ(err, 1);
}

TEST(make_string, null_input) {
  int err = make_string(NULL, NULL);
  EXPECT_EQ(err, 1);
}
// not_double()
TEST(not_double, not_digit_symbols) {
  char buffer[7] = "Moscow";
  int i = not_double(buffer);
  ASSERT_EQ(1, i);
}

TEST(not_double, digit_symbols) {
  char buffer[7] = "12";
  int i = not_double(buffer);
  ASSERT_EQ(0, i);
}

TEST(not_double, digit_and_dot_symbols) {
  char buffer[7] = "12.";
  int i = not_double(buffer);
  ASSERT_EQ(0, i);
}

TEST(not_double, null_input) {
  int err = not_double(NULL);
  ASSERT_EQ(1, err);
}
// not_eng_symbols()
TEST(not_eng_symbols, eng_symbols) {
  char buffer[7] = "Moscow";
  int i = not_eng_symbols(buffer);
  ASSERT_EQ(0, i);
}

TEST(not_eng_symbols, not_eng_symb) {
  char buffer[7] = "9os5ow";
  int i = not_eng_symbols(buffer);
  ASSERT_EQ(1, i);
}

TEST(not_eng_symbols, buffer_is_null) {
  int err = not_eng_symbols(NULL);
  ASSERT_EQ(1, err);
}
// not_integer()
TEST(not_integer, not_digit_symbols) {
  char buffer[7] = "Peter";
  int i = not_integer(buffer);
  ASSERT_EQ(1, i);
}

TEST(not_integer, digit_symbols) {
  char buffer[7] = "12";
  int i = not_integer(buffer);
  ASSERT_EQ(0, i);
}

TEST(not_integer, null_input) {
  int err = not_integer(NULL);
  ASSERT_EQ(1, err);
}
