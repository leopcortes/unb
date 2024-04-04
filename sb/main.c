#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sql.h>

void erros_ponteiro(){
    int *ptr = malloc(sizeof(int)); // memoria alocada mas nao e liberada
    *ptr = 10; // ponteiro nao inicializado

    int *ptr2 = malloc(sizeof(int)); // ponteiro local, pode ser alocado na stack
    free(ptr2);
    *ptr2 = 20; //
}

int main() {
    int y,x;
    y = 5; // variavel nao e usada
    printf("%d", x); //variavel nao inicializada

    scanf("%f",&x); // formato incorreto

    char buffer[10];
    char buffer_maior[20];

    strcpy(buffer, "essa cidade e pequena demais para essa string"); //overflow do buffer
    strcpy(buffer, buffer_maior); //overflow e string de origem nao foi inicializada

    int i = 10;

    while (i > 0){ // loop infinito
        i++;
    }

    int k = 5;
    while(k > 0){
        if(k < 0){ //condicao sempre e falsa
            printf("algo de errado nao esta certo\n");
        }
        k--;
    }

    return 0;
}
