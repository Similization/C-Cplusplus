#pragma once

#ifndef DZ1_FUNCTIONS_H
#define DZ1_FUNCTIONS_H

#endif  // DZ1_FUNCTIONS_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "my_string.h"

typedef struct {  // структура страна
  double square;
  unsigned int population;
  struct String capital;
} Country;

double pop_density(Country country);

struct Countries {  // структура вектор стран
  size_t capacity;
  size_t size;
  Country* data;
};

void initialize_countries(struct Countries* countries);

int add_countries(struct Countries* countries,
                  Country country);  // добавление страны

int print_countries(struct Countries* countries);  // вывод стран

int sort_pop_density(struct Countries* countries);  // сортировка пузырьком

int free_countries(struct Countries* countries);  //

int input_data(struct Countries* countries);  //
