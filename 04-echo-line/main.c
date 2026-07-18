#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char *line = NULL;
  size_t cap = 0;
  ssize_t n = getline(&line, &cap, stdin);

  if (n == -1) {
    free(line);
    return EXIT_SUCCESS;
  }

  if (n > 0 && line[n] == '\n') {
    line[n - 1] = '\n';
  }

  printf("%s\n", line);
  free(line);

  return EXIT_SUCCESS;
}
