#include "gtest/gtest.h"

extern "C" {
#include "my_countries.h"
}
// print_string()
TEST(print_string, print_ok) {
  struct String str;
  char buffer[] = {'D', 'o', 'r', 'a', '\n'};
  make_string(&str, buffer);
  testing::internal::CaptureStdout();
  print_string(&str);
  std::string output = testing::internal::GetCapturedStdout(), c_str();
  for (size_t i = 0; i < str.length; ++i) {
    ASSERT_EQ(str.data[i], output[i]);
  }
  free(str.data);
}

TEST(print_string, null_input) {
  int err = print_string(NULL);
  EXPECT_EQ(err, 1);
}

// print_countries()
TEST(print_countries, print_ok) {
  struct Countries countries;
  initialize_countries(&countries);

  struct String capital;
  char buffer[] = "Moscow\n";
  make_string(&capital, buffer);

  Country country;
  country.capital = capital;
  country.square = 123.567;
  country.population = 700000;
  add_countries(&countries, country);

  testing::internal::CaptureStdout();
  print_countries(&countries);
  std::string output = testing::internal::GetCapturedStdout(), c_str();
  EXPECT_EQ(output,
            "{square: 123.567000, population: 700000, capital: Moscow}\n");

  free_countries(&countries);
}

TEST(print_countries, countries_data_not_ok) {
  int err = print_countries(NULL);
  EXPECT_EQ(err, 1);
}
