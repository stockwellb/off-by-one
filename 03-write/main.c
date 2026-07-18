#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {

  // open a file
  FILE *file = fopen("test.txt", "w");
  if (file == NULL) {
    perror("fopen");
    return EXIT_FAILURE;
  }

  // try to write or report error
  for (int lineno = 0; lineno < 25; lineno++) {
    errno = 0;
    char buf[64];
    snprintf(buf, sizeof(buf), "%d: This is a line of text\n", lineno);
    if (fputs(buf, file) == EOF) {
      if (errno != 0) {
        perror("fputs");
      } else {
        fputs("fputs: write failed\n", stderr);
      }
      fclose(file);
      return EXIT_FAILURE;
    }
  }

  // close the file
  if (fclose(file) == EOF) {
    perror("fclose");
    return EXIT_FAILURE;
  };
  return EXIT_SUCCESS;
}
