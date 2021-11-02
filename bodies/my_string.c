#include "my_string.h"

int make_string(struct String* string, char* buffer) {  // создание строки
  if (buffer == NULL || string == NULL) {
    printf("Error: your buffer is empty");
    return 1;  //?
  }
  string->length = strlen(buffer);
  if ((string->data = (char*)malloc(sizeof(char) * string->length)) == NULL) {
    return 1;
  }
  for (size_t i = 0; i < string->length - 1; ++i) {
    string->data[i] = buffer[i];
  }
  string->data[string->length - 1] = '\0';
  return 0;
}

int not_double(char* buffer) {  // проверка на то, что все символы - символы
                                // сила с плавающей точкой
  if (buffer == NULL) {
    printf("Error: buffer is empty");
    return 1;
  }
  size_t len = strlen(buffer);
  if (buffer[len - 1] == '\n') {
    len -= 1;
  }
  int have_dot_flag = 0;
  for (size_t i = 0; i < len; ++i) {
    if (!isdigit(buffer[i])) {
      if (!have_dot_flag && buffer[i] == '.') {
        have_dot_flag++;
      } else {
        return 1;
      }
    }
  }
  return 0;
}

int not_eng_symbols(char* buffer) {  // проверка на то, что все символы строки
                                     // принадлежат англ.алфавиту
  if (buffer == NULL) {
    printf("Error: buffer is empty");
    return 1;
  }
  size_t len = strlen(buffer);
  if (buffer[len - 1] == '\n') {
    len -= 1;
  }
  for (size_t i = 0; i < len; ++i) {
    if (!isalpha(buffer[i])) return 1;
  }
  return 0;
}

int not_integer(char* buffer) {  // проверка на то, что все символы - цифры
  if (buffer == NULL) {
    printf("Error: buffer is empty");
    return 1;
  }
  size_t len = strlen(buffer);
  if (buffer[len - 1] == '\n') {
    len -= 1;
  }
  for (size_t i = 0; i < len; ++i) {
    if (!isdigit(buffer[i])) {
      return 1;
    }
  }
  return 0;
}
