#include "file.h"
#include "getopt.h"
#include "interface.h"
#include "malloc.h"

#define MAX_ARRAY_SIZE 100000000

int main(int argc, char* argv[]) {
  double* array;
  if ((array = malloc(sizeof(double) * MAX_ARRAY_SIZE)) == NULL) {
    printf("Unable to allocate memory\n");
    return 1;
  }

  int opt, err = 1;
  char* opts = "-:i:c:";

  while ((opt = getopt(argc, argv, opts)) != -1) {
    switch (opt) {
      case 'i':
        err = initialize_array(optarg, array, MAX_ARRAY_SIZE);
        break;
      case 'c':
        err = create_and_init(optarg, MAX_ARRAY_SIZE);
        return 0;
        break;
      case '?':
        printf("Unknown option: %c\n", optopt);
        break;
      case ':':
        printf("Missing arg for %c\n", optopt);
        break;
      case 1:
        printf("Non-option arg: %s\n", optarg);
        break;
    }
  }

  if (err) {
    free(array);
    return 1;
  }

  /* time start */
  unsigned int start_time = clock();
  formula_data res = get_formula_datas(array, MAX_ARRAY_SIZE);
  unsigned int end_time = clock();
  /* time end */

  long long n = MAX_ARRAY_SIZE / 2;

  long double epsilon = 0.0000001; /* 10^-7 */
  if (n * res.sum_x2 - res.sum_x * res.sum_x < epsilon) {
    printf("Calculation error: division by zero\n");
    return 1;
  }
  long double coeff_a = (n * res.sum_xy - res.sum_x * res.sum_y) /
                        (n * res.sum_x2 - res.sum_x * res.sum_x);
  long double coeff_b = (res.sum_y - coeff_a * res.sum_x) / n;

  printf("The equation of the form: y = a*x + b\n");
  printf("Will be: y = %LF*x + %LF\n", coeff_a, coeff_b);
  printf("Where: a = %LF,  b = %LF\n", coeff_a, coeff_b);
  printf("Runtime: %u\n", end_time - start_time);

  return 0;
}