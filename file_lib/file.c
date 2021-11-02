#include "file.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

int initialize_array(char* file_name, double* array, long long a_size) {
    FILE* fp;
    if ((fp = fopen(file_name, "r")) == NULL) {
        printf("File error: can't open file\n");
        return 1;
    }
    for (long long i = 0; i < a_size; ++i) {
        if ((fscanf(fp, "%lf", &array[i])) != 1) {
            fclose(fp);
            return 1;
        }
    }
    return 0;
}

int create_and_init(char* file_name, long long a_size) {
    FILE* fp;
    if ((fp = fopen(file_name, "w")) == NULL) {
        printf("File error: can't open file\n");
        return 1;
    }
    srand(time(NULL));
    for (long long i = 0; i < a_size; ++i) {
        fprintf(fp, "%.2f ", (double)(rand()%20001) / 100 - 100);
    }
    return 0;
}
