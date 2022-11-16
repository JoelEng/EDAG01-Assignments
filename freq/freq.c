#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// N is max string length, M is max unique string count
// These numbers have been tried and work with the makefile
#define N (9)
#define M (153)

char **words;
int count[M];

int is_prime(int n) {
  int i;
  for (i = 2; i <= n / 2; i += 1) {
    if (n % i == 0) {
      return 0;
    }
  }
  return n != 1;
}

int word_idx(char s[N]) {
  int i;
  for (i = 0; i < M; i += 1) {
    if (strcmp(s, words[i]) == 0) {
      // printf("FOUND WORD: %d, %s, %s\n", i, s, words[i]);
      return i;
    } else if (strcmp(words[i], "") == 0) {
      // printf("CREATED NEW WORD: %d, %s, %s\n", i, s, words[i]);
      strcpy(words[i], s);
      return i;
    }
  }
  return -1;
}

int main() {
  int i;
  int l = 1;
  int max = 0;
  char *max_word = malloc(N * sizeof(char));
  char s[N];
  int *p = &l;
  words = calloc(M, sizeof(char *));
  for (i = 0; i < M; i += 1) {
    words[i] = calloc(N, sizeof(char));
  }

  while (scanf("%s\n", s) != EOF) {
    // printf("STRING IS: %s\n", s);
    p = &count[word_idx(s)];
    if (is_prime(l++)) {
      printf("trying to delete %s: ", s);
      // printf("*p: %d", *p);
      if (*p == 0) {
        printf("not found\n");
      } else {
        printf("deleted\n");
        *p = 0;
      }
      continue;
    }
    if (*p == 0) {
      printf("added %s\n", s); // should be "counted" if s already exists
    } else {
      printf("counted %s\n", s);
    }
    *p += 1;
  }

  for (i = 0; i < M; i += 1) {
    if (count[i] > max && words[i] > max_word) {
      max = count[i];
      strcpy(max_word, words[i]);
    }
  }
  printf("result: %s %d\n", max_word, max);

  for (i = 0; i < M; i += 1) {
    free(words[i]);
  }
  free(words);
  free(max_word);
  return 0;
}
