/*
 * Exemplo de uso de execve.
 * Executa o programa passado como argumento. 

 * Exemplos:
     execve1 /bin/ls
	 execve1 /bin/ps	
 */

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp) {
  
  if (argc < 2) {
    fprintf (stderr, "Uso: %s cmd arg1 ... argn\n", argv[0]);
    return 1;
  }

  if (fork() == 0) {  /* Processo filho */
    execve(argv[1], &argv[1], envp); 
    fprintf(stderr,"Não conseguiu executar execve.\n");//se rodar essa linha, significa que nao houve troca da imagem do processo -> erro
    return -1;
  }
  else {                   /* Processo pai   */
	  int status;
    wait(&status);
    printf ("Filho terminou sua execução com status %d.\n", status);
  }
  return 0;
}
