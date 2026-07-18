#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// naturally packed struct
typedef struct {
  int y;
  char x;
  char x1;
  char x2;
  char x3;
} point;

int main() {
  FILE *file = fopen("test.bin", "wb");
  if (file == NULL) {
    perror("Error: file not opened.\n");
    return EXIT_FAILURE;
  }

  point p;

  // poison the struct to veryify padding
  memset(&p, 0xAA, sizeof(p));

  // fill in the fields
  p.y = 10;
  p.x = 5;
  p.x1 = 6;
  p.x2 = 8;
  p.x3 = 30;

  size_t num = fwrite(&p, sizeof(point), 1, file);

  if (num != 1) {
    perror("Error: write failed.\n");
    return EXIT_FAILURE;
  }

  fclose(file);
  printf("Data written to test.bin\n");
  return EXIT_SUCCESS;
}
