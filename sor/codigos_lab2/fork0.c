/*
 * Teste com fork.
 */ 
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

  printf("Antes do fork\n");
  int s = 0;

  if (fork() == 0) {
    s = 1;        
	  printf("Processo filho, &s = %p, s = %d\n", (void*) &s, s);    
  } else {
	  s = 2;
	  sleep(2);    	
	  printf("Processo pai, &s = %p, s = %d\n", (void*) &s, s);    
  }

  return 0;
}
