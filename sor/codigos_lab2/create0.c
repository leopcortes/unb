/*
 * Criacao de uma nova thread. Sera que ela sera sempre executada?????
 */
#include <pthread.h>
#include <stdio.h>

void* f_thread(void *v) {
  printf("Nova Thread.\n");
  return NULL;
}

int main() {
  pthread_t thr;
  
  if (pthread_create(&thr, NULL, f_thread, NULL))
    fprintf(stderr, "Erro na criacao da thread. \n");

  return 0;
}
