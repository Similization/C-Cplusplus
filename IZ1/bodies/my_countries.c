#include "my_countries.h"

double pop_density(Country country) {
  return country.population / country.square;
}

void initialize_countries(struct Countries* countries) {
  countries->size = 0;
  countries->capacity = 0;
  countries->data = NULL;
}

int add_countries(struct Countries* countries, Country country) {
  if (countries->size >= countries->capacity) {
    if (countries->capacity == 0) {
      countries->capacity = 1;
    } else {
      countries->capacity *= 2;
    }
    Country* buffer = (Country*)malloc(sizeof(Country) * countries->capacity);
    if (buffer == NULL) {
      return 1;
    }
    for (size_t i = 0; i < countries->size; ++i) {
      buffer[i] = countries->data[i];
    }
    if (countries->data) {
      free(countries->data);
    }
    countries->data = buffer;
  }
  countries->data[countries->size++] = country;
  return 0;
}

int sort_pop_density(struct Countries* countries) {
  if (countries == NULL || countries->data == NULL) {
    printf("Error: countries are empty");
    return 1;  //?
  }
  for (size_t i = 0; i < countries->size - 1; ++i) {
    for (size_t j = i; j < countries->size; ++j) {
      if (pop_density(countries->data[i]) > pop_density(countries->data[j])) {
        Country tmp = countries->data[i];
        countries->data[i] = countries->data[j];
        countries->data[j] = tmp;
      }
    }
  }
  return 0;
}  // сортировка пузырьком

int free_countries(struct Countries* countries) {
  if (countries == NULL || countries->data == NULL) {
    printf("Error: nothing to clear");
    return 1;  //?
  }
  size_t size = countries->size;
  for (size_t i = 0; i < size; ++i) {
    free(countries->data[size - i - 1].capital.data);
  }
  free(countries->data);
  countries->capacity = 0;
  countries->size = 0;
  return 0;
}
