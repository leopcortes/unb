#include <stdio.h>
#include <stdlib.h>
#define NUM_LETTERS 26

int memory_leak(), stack_buffer_overflow(), heap_use_after_free();

int main(int argc, char const *argv[])
{
    // memory_leak();
    leak2();
    // leak3();

    return 0;
}

int memory_leak()
{
    // funcao não desaloca memoria

    int *ptr = (int *)malloc(sizeof(int)); // aloca memoria
    int a = 1;

    *ptr = a;
    printf("Pointer address: %p\nPointer value: %d\n", ptr, *ptr);
    // free(ptr);   // desaloca
    return 0;
}

int stack_buffer_overflow()
{
    // acesso endereco fora de variavel (out of bounds variable)
    char alfabeto[NUM_LETTERS];
    for (int i = 0; i < 26; i++)
    {
        alfabeto[i] = 'a' + i;
    }

    int index = NUM_LETTERS + 1;

    printf("alfabeto[%d]: %c\n", index, alfabeto[index]);
    return 0;
}

int heap_use_after_free()
{
    // acesso a memoria depois de liberado (free)
    int *ptr = (int *)malloc(sizeof(int)); // aloca memoria
    int a = 1;
    free(ptr); // desaloca

    *ptr = a;
    printf("Pointer address: %p\nPointer value: %d\n", ptr, *ptr);
    return 0;
}
