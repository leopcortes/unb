/*
 * Retorno 0 (NULL) para sinalizar execucao bem sucedida.
 * Nova thread envia valor para thread main via pthread_exit.
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void* f_thread(void *v) {
  int r;
  printf("Valor a ser retornado: ");
  scanf("%d", &r);
  pthread_exit((void*)r);
} 

int main() {
  pthread_t thr;
  int retorno;

  pthread_create(&thr, NULL, f_thread, NULL);

  pthread_join(thr, (void **) &retorno); 

  if (retorno == 0)
      printf("Thread encerrou normalmente.\n");
  else
      printf("Thread encerrou com valor: %d\n", retorno);

  return 0;
}


