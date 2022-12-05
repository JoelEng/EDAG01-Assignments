#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define N (10)

int main() {
  unsigned int stack[N];
  unsigned int c, l = 1, len = 0, e, n = 0;
  int a, b;
  while ((c = getchar()) != EOF) {
    // printf("c: %c;\n", c);
    if (isdigit(c)) {
      n = n * 10 + (c - '0');
      // printf("i: %d\n", a);
      if (len == 10) {
        e = n + '0';
        goto error;
      }
      continue;
    }
    if (n > 0) {
      stack[len++] = n; // push num to stack
      n = 0;
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
