#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "poly.h"

struct poly_t {
  int coeff;
  int exp;
  poly_t *next;
};

int read_int(const char *s, int *i) {
  int val = 0;
  int mul = 1;
  if (s[*i] == '^') {
    *i += 1;
  }
  if (s[*i] == '-') {
    mul = -1;
    *i += 1;
  } else if (s[*i] == '+') {
    *i += 1;
  }
  while (s[*i] == ' ') {
    *i += 1;
  }
  while (isdigit(s[*i])) {
    val *= 10;
    val += s[*i] - '0';
    *i += 1;
  }
  if (val == 0) {
    return 1 * mul;
  }
  return val * mul;
}

poly_t *read_term(const char *s, int *i) {
  int exp = 0;
  while (s[*i] == ' ') {
    *i += 1;
  }
  int coeff = read_int(s, i);
  if (s[*i] == 'x') {
    *i += 1;
    exp = read_int(s, i);
  }
  poly_t *t = calloc(1, sizeof(poly_t));
  t->coeff = coeff;
  t->exp = exp;
  t->next = NULL;
  return t;
}

poly_t *new_poly_from_string(const char *s) {
  int i = 0;
  poly_t *head = read_term(s, &i);
  poly_t *current = head;
  while (s[i - 1] != '\0') {
    current->next = read_term(s, &i);
    current = current->next;
    i += 1;
  }
  return head;
}

void free_poly(poly_t *p) {
  poly_t *current = p;
  while (current != NULL) {
    poly_t *temp = current->next;
    free(current);
    current = temp;
  }
}

poly_t *mul(poly_t *p1, poly_t *p2) {
  poly_t *prod = calloc(1, sizeof(poly_t));
  return prod;
}

void print_poly(poly_t *p) {
  poly_t *current = p;
  bool first = true;
  while (current != NULL) {
    if (current->coeff < 0) {
      printf("- ");
    } else if (!first) {
      printf("+ ");
    }
    if (current->coeff != 1 || current->exp == 0) {
      printf("%d", abs(current->coeff));
    }
    if (current->exp != 0) {
      printf("x");
      if (current->exp != 1) {
        printf("^%d", current->exp);
      }
      printf(" ");
    }
    current = current->next;
    first = false;
  }
  printf("\n");
}
