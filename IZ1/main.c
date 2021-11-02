#include "my_countries.h"

int main() {
  struct Countries countries;
  initialize_countries(&countries);

  printf(
      "The program waits for data to arrive in the following order: \
    \ncapital (char*)\nsquare (double)\npopulation (unsigned int)\n");
  printf(
      "If an error occurs in any of the lines, the program ignores all "
      "previously received information.\n");
  printf("Enter information:\n");

  if (input_data(&countries)) {
    printf("Memory allocation failure");
    return 1;
  }

  if (!sort_pop_density(&countries)) {
    printf("Sorted countries by population density:\n");
    print_countries(&countries);
    free_countries(&countries);
  } else {
    return 1;
  }
  return 0;
}
