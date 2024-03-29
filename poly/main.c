#include "poly.h"
#include <stdio.h>

static void poly_test(const char *a, const char *b) {
  poly_t *p;
  poly_t *q;
  poly_t *r;

  printf("Begin polynomial test of (%s) * (%s)\n", a, b);

  p = new_poly_from_string(a);
  q = new_poly_from_string(b);

  print_poly(p);
  print_poly(q);

  r = mul(p, q);

  print_poly(r);

  free_poly(p);
  free_poly(q);
  free_poly(r);

  printf("End polynomial test of (%s) * (%s)\n", a, b);
}

int main(void) {
  poly_test("-642x^113 - 113x^37 - 653x^19 - 330", "427x^32 - 594");
  // putchar('\n');
  // poly_test("x^10000000 + 2", "2x^2 + 3x + 4");

  return 0;
}
