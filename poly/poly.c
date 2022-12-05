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

void sort_poly(poly_t *p) {
  poly_t *current = p;
  bool sw = true;
  int temp_coeff, temp_exp;
  while (sw) {
    sw = false;
    current = p;
    while (current != NULL && current->next != NULL &&
           current->next->next != NULL) {
      if (current->next->exp < current->next->next->exp) {
        temp_coeff = current->next->coeff;
        temp_exp = current->next->exp;
        current->next->coeff = current->next->next->coeff;
        current->next->exp = current->next->next->exp;
        current->next->next->coeff = temp_coeff;
        current->next->next->exp = temp_exp;
        sw = true;
      }
      current = current->next;
    }
  }
}

void shorten(poly_t *p) {
  poly_t *current = p;
  poly_t *other;
  poly_t *temp;
  while (current != NULL) {
    other = current;
    while (other != NULL && other->next != NULL) {
      if (current->exp == other->next->exp) {
        current->coeff += other->next->coeff;
        temp = other->next;
        other->next = other->next->next;
        free(temp);
      }
      other = other->next;
    }
    current = current->next;
  }
}

poly_t *mul(poly_t *p1, poly_t *p2) {
  poly_t *prod = calloc(1, sizeof(poly_t));
  poly_t *current = prod;
  poly_t *current_p1 = p1;
  poly_t *current_p2 = p2;

  while (current_p1 != NULL) {
    while (current_p2 != NULL) {
      current->coeff = current_p1->coeff * current_p2->coeff;
      current->exp = current_p1->exp + current_p2->exp;
      current->next = calloc(1, sizeof(poly_t));

      current = current->next;
      current_p2 = current_p2->next;
    }
    current_p2 = p2;
    current_p1 = current_p1->next;
  }
  shorten(prod);
  sort_poly(prod);
  return prod;
}

void print_poly(poly_t *p) {
  poly_t *current = p;
  bool first = true;
  while (current != NULL) {
    if (current->coeff == 0) {
      current = current->next;
      continue;
    }
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
    }
    if (current->next != NULL && current->next->coeff != 0) {
      printf(" ");
    }
    current = current->next;
    first = false;
  }
  printf("\n");
}
