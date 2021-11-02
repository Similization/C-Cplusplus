#ifndef DZ1_FUNCTIONS_H
#define DZ1_FUNCTIONS_H

#endif  // DZ1_FUNCTIONS_H

#include <ctype.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct String {  // структура строка
  size_t length;
  char* data;
};

int make_string(struct String* string, char* buffer);

int print_string(struct String* string);

int not_double(char* buffer);

int not_eng_symbols(char* buffer);

int not_integer(char* buffer);
