#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  size_t x;
  size_t y;
} point;

int write_file(void) {

  FILE *file = fopen("test.bin", "wb");

  if (file == NULL) {
    perror("fopen");
    return EXIT_FAILURE;
  }

  point p = {.x = 100, .y = 125};

  size_t num = fwrite(&p, sizeof(p), 1, file);

  if (num != 1) {
    perror("fwite");
    return EXIT_FAILURE;
  }

  fclose(file);
  return EXIT_SUCCESS;
}

int read_file(void) {
  FILE *file = fopen("test.bin", "rb");

  if (file == NULL) {
    perror("fopen");
    return EXIT_FAILURE;
  }

  point p;

  size_t num = fread(&p, sizeof(p), 1, file);

  if (num != 1) {
    if (feof(file)) {
      fprintf(stderr, "enexpected end of file\n");
    } else {
      perror("fread");
    }
    fclose(file);
    return EXIT_FAILURE;
  }

  fclose(file);
  printf("x: %zu\ny: %zu\n", p.x, p.y);

  return EXIT_SUCCESS;
}

int main(void) {

  write_file();
  read_file();

  return EXIT_SUCCESS;
}
