#include <stdio.h>

static char input[2046];

int main(int argc, char** argv) {
  puts("Lipsy version 0.0.1");
  while (1) {
    fputs("lispy> ", stdout);
    fgets(input, 2048, stdin);
    printf("No you're a %s", input);
  }
  puts("done");
  return 1;
}
