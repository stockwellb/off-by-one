#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int x;
  int y;
} point;

int main() {
  point matrix[2][5] = {{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}},
                        {{-1, -1}, {-2, -2}, {-3, -3}, {-4, -4}, {-5, 5}}};
  size_t nitems = sizeof(matrix) / sizeof(matrix[0][0]);
  size_t nrows = sizeof(matrix) / sizeof(matrix[0]);
  size_t ncols = sizeof(matrix[0]) / sizeof(matrix[0][0]);
  printf("nitems: %lu\n", nitems);
  printf("nrows: %lu\n", nrows);
  printf("ncols: %lu\n", ncols);
  printf("--------------\n");

  for (size_t row = 0; row < nrows; row++) {
    for (size_t col = 0; col < ncols; col++) {
      point p = matrix[row][col];
      printf("point: %d,%d\n", p.x, p.y);
    }
  }

  printf("--------------\n");

  // This UB and written just to prove a point (LOL)
  // point *matrix_ptr = &matrix[0][0];
  // for (size_t i = 0; i < nitems; i++) {
  //  point p = *matrix_ptr;
  //  printf("point: %d,%d\n", p.x, p.y);
  //  matrix_ptr++;
  //}
}
