#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define N (10)

static unsigned int stack[N];

int main() {
  unsigned int c, l = 1, len = 0, e;
  int a, b;
  while ((c = getchar()) != EOF) {
    // printf("c: %c;\n", c);
    if (isdigit(c)) {
      a = 0;
      while (isdigit(c)) {
        a = a * 10 + (c - '0');
        c = getchar();
      }
      // printf("i: %d\n", a);
      if (len == 10) {
        e = a + '0';
        goto error;
      }
      stack[len++] = a; // push to stack
    }

    switch (c) {
    case ' ':
      break;
    case '+':
    case '-':
    case '*':
    case '/':
      if (len < 2) {
        e = c;
        goto error;
      }
      b = stack[--len]; // pop a and b from stack
      a = stack[len - 1];
      // printf("bin-op: %d %c %d\n", a, c, b);

      switch (c) {
      case '+':
        a += b;
        break;
      case '-':
        a -= b;
        break;
      case '*':
        a *= b;
        break;
      default:
        if (!b) {
          e = c;
          goto error;
        } else {
          a /= b;
        }
        break;
      }
      stack[len - 1] = a; // push to stack without changing len
      break;
    default:
      switch (c) {
      case '\n':
        if (len == 1) {
          printf("line %d: %d\n", l, stack[len - 1]);
          break;
        }
        printf("line %d: error at \\n\n", l);
        break;
      default:
        e = c;
      error:
        printf("line %d: error at %c\n", l, e);
        while (c != '\n') {
          c = getchar();
        }
        break;
      }
      len = 0;
      l++;
      e = ' ';
    }
  }
}
