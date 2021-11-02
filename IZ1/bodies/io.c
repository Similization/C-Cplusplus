#include <errno.h>

#include "my_countries.h"

int print_string(struct String* string) {  // вывод строки (для себя)
  if (string == NULL) {
    printf("Error: your string is empty");
    return 1;
  }
  for (size_t i = 0; i < string->length; ++i) {
    printf("%c", string->data[i]);
  }
  return 0;
}

int print_countries(struct Countries* countries) {
  if (countries == NULL) {
    printf("Error: your countries are empty");
    return 1;
  }
  for (size_t i = 0; i < countries->size; ++i) {
    printf("{square: %lf, population: %u, capital: %s}\n",
           countries->data[i].square, countries->data[i].population,
           countries->data[i].capital.data);
  }
  return 0;
}

int input_data(struct Countries* countries) {
  const int max_size = 256;
  char buffer[max_size];

  struct String capital;
  double square;
  unsigned int population;
  Country country;
  int err = 0;

  while (!feof(stdin)) {
    if (fgets(buffer, max_size, stdin) != NULL && !not_eng_symbols(buffer)) {
      err = make_string(&capital, buffer);
      if (err) {
        return 1;
      }
    } else
      continue;
    if (fgets(buffer, max_size, stdin) != NULL && !not_double(buffer)) {
      square = strtod(buffer, NULL);
    } else {
      free(capital.data);
      continue;
    }
    if (fgets(buffer, max_size, stdin) != NULL && !not_integer(buffer)) {
      population = strtol(buffer, NULL, 10);
    } else {
      free(capital.data);
      continue;
    }
    country.population = population;
    country.square = square;
    country.capital = capital;
    err = add_countries(countries, country);
    if (err) {
      return 1;
    }
  }
  if (countries->size) {
    print_countries(countries);
  }
  return 0;
}