#pragma once

#include "pthread.h"
#include "unistd.h"
#include "stdio.h"

typedef struct formula_data {
    long double sum_x;
    long double sum_y;
    long double sum_xy;
    long double sum_x2;
} formula_data;

formula_data get_formula_datas(double* , long long);
