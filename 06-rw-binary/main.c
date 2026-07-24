#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  size_t x;
  size_t y;
} point;

int write_file(const char *path, const point *out) {

  FILE *file = fopen(path, "wb");

  if (file == NULL) {
    perror("fopen");
    return EXIT_FAILURE;
  }

  size_t num = fwrite(out, sizeof *out, 1, file);

  if (num != 1) {
    perror("fwrite");
    fclose(file);
    return EXIT_FAILURE;
  }

  if (fclose(file) != 0) {
    perror("fclose");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int read_file(const char *path, point *out) {
  FILE *file = fopen(path, "rb");

  if (file == NULL) {
    perror("fopen");
    return EXIT_FAILURE;
  }

  size_t num = fread(out, sizeof *out, 1, file);

  if (num != 1) {
    if (feof(file)) {
      fprintf(stderr, "unexpected end of file\n");
    } else if (ferror(file)) {
      perror("fread");
    }
    fclose(file);
    return EXIT_FAILURE;
  }

  fclose(file);

  return EXIT_SUCCESS;
}

int main(void) {

  const char *path = "test.bin";

  point p1 = {.x = 100, .y = 125};
  if (write_file(path, &p1) != EXIT_SUCCESS) {
    return EXIT_FAILURE;
  }

  point p2;
  if (read_file(path, &p2) != EXIT_SUCCESS) {
    return EXIT_FAILURE;
  }

  printf("x: %zu\ny: %zu\n", p2.x, p2.y);

  return EXIT_SUCCESS;
}
