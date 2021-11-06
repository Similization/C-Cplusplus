#include <pthread.h>
#include <unistd.h>

#include "foo.c"
#include "interface.h"

pthread_mutex_t mutex;

typedef struct thread_info {
  long long a_size;   /* array size */
  double* array;      /* point to array */
  size_t thread_num;  /* number of current thread */
  formula_data* data; /* point to formula's datas */
} thread_info;

void* sum_formula_datas(void* args) {
  if (!args) {
    return NULL;
  }

  thread_info cur_thread = *((thread_info*)args);
  size_t threads_count = 100;
      //sysconf(_SC_NPROCESSORS_ONLN); /* get count of threads */
  printf("Threads count in sum: %lu\n", threads_count);
  formula_data cur_data;
  int elemts_between = threads_count * 2, err = 0;
  if ((err = fdata_initialize(&cur_data)) != 0) {
    return NULL;
  }

  for (long long i = cur_thread.thread_num * 2; i < cur_thread.a_size;) {
    cur_data.sum_x += cur_thread.array[i];
    cur_data.sum_y += cur_thread.array[i + 1];
    cur_data.sum_x2 += cur_thread.array[i] * cur_thread.array[i];
    cur_data.sum_xy += cur_thread.array[i] * cur_thread.array[i + 1];
    i += elemts_between;
  }

  if ((err = pthread_mutex_lock(&mutex)) != 0) {
    printf("Mutex error: can't lock mutex, status = %d\n", err);
    return NULL;
  }

  cur_thread.data->sum_x += cur_data.sum_x;
  cur_thread.data->sum_y += cur_data.sum_y;
  cur_thread.data->sum_x2 += cur_data.sum_x2;
  cur_thread.data->sum_xy += cur_data.sum_xy;

  if ((err = pthread_mutex_unlock(&mutex)) != 0) {
    printf("Mutex error: can't unlock mutex, status = %d\n", err);
    return NULL;
  }
  return args;
}

formula_data get_formula_datas(double* array, long long a_size) {
  formula_data all_datas;
  fdata_initialize(&all_datas);

  /* empty formula_data for error */
  formula_data error_data;
  fdata_initialize(&error_data);

  if (!array) {
    return error_data;
  }

  size_t threads_max_count = 100;
      //sysconf(_SC_NPROCESSORS_ONLN); /* get count of threads */
  printf("Threads count in gfd: %lu\n", threads_max_count);
  pthread_t threads[threads_max_count];   /* array of threads */
  thread_info f_datas[threads_max_count]; /* array of threads information */

  for (size_t i = 0; i < threads_max_count; ++i) {
    f_datas[i].a_size = a_size;
    f_datas[i].array = array;
    f_datas[i].thread_num = i;
    f_datas[i].data = &all_datas;
  }

  pthread_mutex_init(&mutex, NULL);  // create mutex

  int err = 0;

  /* create threads */
  for (size_t i = 0; i < threads_max_count; ++i) {
    if ((err = pthread_create(&threads[i], NULL, sum_formula_datas,
                              (void*)&f_datas[i])) != 0) {
      printf("Thread error: can't create thread, status = %d\n", err);
      return error_data;
    }
  }

  /* join threads */
  for (size_t i = 0; i < threads_max_count; ++i) {
    if ((err = pthread_join(threads[i], NULL)) != 0) {
      printf("Thread error: can't join thread, status = %d\n", err);
      return error_data;
    }
  }

  pthread_mutex_destroy(&mutex);  // destroy mutex

  return all_datas;
}
