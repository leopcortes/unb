/*
 * Criacao de uma nova thread, com passagem de um inteiro como
 * parametro.
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* f_thread(void *v) {
  int thr_id = *(int *) v;
  printf("Thread %d.\n", thr_id);
  return NULL;
}

int main() {
  pthread_t thr;
  int thr_id = 34;

  pthread_create(&thr, NULL, f_thread, (void*) &thr_id);
  pthread_join(thr, NULL);

  return 0;
}
