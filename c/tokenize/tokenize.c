#include <stdio.h>
#include <string.h>

int main() {
  char s[256];
  printf("string to tokenize: ");
  fgets(s, 256, stdin);
  const char *sep = " ";
  char *token, *last;
  for (token = strtok_r(s, sep, &last); token;
       token = strtok_r(NULL, sep, &last))
    printf("current token: %s\n", token);
  return 0;
}
