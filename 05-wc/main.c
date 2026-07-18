#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  int count = 0;
  const char *delimiters = " \t\r\n";

  while ((nread = getline(&line, &len, stdin)) != -1) {
    char *token = strtok(line, delimiters);
    while (token != NULL) {
      count++;
      token = strtok(NULL, delimiters);
    }
  }

  printf("total: %d\n", count);
  free(line);
  return EXIT_SUCCESS;
}
