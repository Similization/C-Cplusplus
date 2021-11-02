#include "gtest/gtest.h"

extern "C" {
#include "my_countries.h"
}
// pop_density()
TEST(pop_density, normal_number) {
  Country country;
  country.square = 12.5;
  country.population = 25000;
  EXPECT_NEAR(2000, pop_density(country), 1e-7);
}
// initialize_countries()
TEST(initialize_countries, initialization_is_ok) {
  struct Countries countries;
  initialize_countries(&countries);
  EXPECT_EQ(countries.capacity, 0);
  EXPECT_EQ(countries.size, 0);
  int is_eq = countries.data == NULL ? 1 : 0;
  EXPECT_EQ(is_eq, 1);
}
// add_countries()
TEST(add_countries, add_one) {
  struct Countries countries;
  initialize_countries(&countries);

  struct String capital;
  char buffer[] = "Moscow";
  make_string(&capital, buffer);

  Country country;
  country.capital = capital;
  country.square = 123.567;
  country.population = 700000;
  add_countries(&countries, country);

  EXPECT_EQ(countries.capacity, 1);
  EXPECT_EQ(countries.size, 1);
  EXPECT_STREQ(countries.data[0].capital.data, country.capital.data);
  EXPECT_EQ(countries.data[0].square, country.square);
  EXPECT_EQ(countries.data[0].population, country.population);

  free_countries(&countries);
}

TEST(add_countries, add_three) {
  struct Countries countries;
  initialize_countries(&countries);

  struct String capital;
  char buffer[] = "Moscow";
  Country country;

  for (int i = 0; i < 3; ++i) {
    make_string(&capital, buffer);
    country.capital = capital;
    country.square = i + 1;
    country.population = (i + 1) * 10;
    add_countries(&countries, country);

    EXPECT_STREQ(countries.data[i].capital.data, country.capital.data);
    EXPECT_EQ(countries.data[i].square, country.square);
    EXPECT_EQ(countries.data[i].population, country.population);
  }
  EXPECT_EQ(countries.capacity, 4);
  EXPECT_EQ(countries.size, 3);

  free_countries(&countries);
}
// sort_pop_density()
TEST(sort_pop_density, is_sorted) {
  struct Countries countries;
  initialize_countries(&countries);

  struct String capital;
  char buffer[] = "Moscow";
  Country country;

  for (int i = 0; i < 3; ++i) {
    make_string(&capital, buffer);
    country.capital = capital;
    country.square = i + 1;
    country.population = (i + 1) * 10;
    add_countries(&countries, country);
  }
  sort_pop_density(&countries);
  int is_sorted = 1;
  for (size_t i = 0; i < countries.size - 1; ++i) {
    if (pop_density(countries.data[i]) > pop_density(countries.data[i + 1])) {
      is_sorted = 0;
      break;
    }
  }
  EXPECT_EQ(is_sorted, 1);

  free_countries(&countries);
}

TEST(sort_pop_density, is_sorted_in_not_sorted) {
  struct Countries countries;
  initialize_countries(&countries);

  struct String capital;
  char buffer[] = "Moscow";
  Country country;

  for (int i = 0; i < 3; ++i) {
    make_string(&capital, buffer);
    country.capital = capital;
    country.square = 100 - i;
    country.population = 10 - i;
    add_countries(&countries, country);
  }
  sort_pop_density(&countries);
  int is_sorted = 1;
  for (size_t i = 0; i < countries.size - 1; ++i) {
    if (pop_density(countries.data[i]) > pop_density(countries.data[i + 1])) {
      is_sorted = 0;
      break;
    }
  }
  EXPECT_EQ(is_sorted, 1);

  free_countries(&countries);
}

TEST(sort_pop_density, null_input) {
  int err = sort_pop_density(NULL);
  EXPECT_EQ(err, 1);
}

TEST(sort_pop_density, null_data_input) {
  struct Countries countries;
  initialize_countries(&countries);
  int err = sort_pop_density(&countries);
  EXPECT_EQ(err, 1);
}
// free_countries()
TEST(free_countries, is_everything_free) {
  struct Countries countries;
  initialize_countries(&countries);

  struct String capital;
  char buffer[] = "Moscow";
  Country country;

  for (int i = 0; i < 3; ++i) {
    make_string(&capital, buffer);
    country.capital = capital;
    country.square = i + 1;
    country.population = (i + 1) * 10;
    add_countries(&countries, country);
  }
  free_countries(&countries);
  EXPECT_EQ(countries.capacity, 0);
  EXPECT_EQ(countries.size, 0);
}

TEST(free_countries, null_input) {
  int err = free_countries(NULL);
  EXPECT_EQ(err, 1);
}

TEST(free_countries, null_data_input) {
  struct Countries countries;
  initialize_countries(&countries);
  int err = free_countries(&countries);
  EXPECT_EQ(err, 1);
}
