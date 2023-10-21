/*
 * Criacao de uma nova thread. O comando join garante que a thread main ira
 * esperar pelo fim da execucao da nova thread.
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
    fprintf(stderr, "Erro na criacao da thread.\n");

  if (pthread_join(thr, NULL))
    fprintf(stderr, "Erro na espera pela thread.\n");

  return 0;
}
