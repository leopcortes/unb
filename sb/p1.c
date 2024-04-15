#include <stdio.h>
#include <stdlib.h>

int xoqp(char *s[]){
  int n;
  for(n = strlen(s)-1; n>=0; n--)
    if(s[n] != ' ' && s[n] != '\t' && s[n] != '\n') break;
  s[n+1] = '\0';
  return n;
}

int main(int argc, char const *argv[]) {

  char *str[10]= "ola, mundo";
  int x;
  x = xoqp(&str);
  printf("%d aaa", x);
  printf("str: %s", str);

  return 0;
}