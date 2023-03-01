#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define d 27

void rabinKarp(char pattern[], char text[], int q) {
  int m = strlen(pattern);
  int n = strlen(text);
  int i, j;
  int p = 0;
  int t = 0;
  int h = 1;
  int count = 0;
  char *delim = " \t\n\r.,:;!?(){}[]<>\"'\\/";  // delimitadores

  for (i = 0; i < m - 1; i++)
    h = (h * d) % q;

  // Calculate hash value for pattern and text
  for (i = 0; i < m; i++) {
    p = (d * p + tolower(pattern[i])) % q;
    t = (d * t + tolower(text[i])) % q;
  }
    // Find the match
  for (i = 0; i <= n - m; i++) {
    if (p == t) {
      for (j = 0; j < m; j++) {
        if (tolower(text[i + j]) != tolower(pattern[j]))
          break;
      }

      if (j == m &&
          (i == 0 || strchr(delim, text[i - 1]) != NULL) &&  // verificação do delimitador anterior
          (i + m == n || strchr(delim, text[i + m]) != NULL)) {  // verificação do delimitador posterior
        printf("%d ", i);
        count++;
      }
    }

    if (i < n - m) {
      t = (d * (t - tolower(text[i]) * h) + tolower(text[i + m])) % q;

      if (t < 0)
        t = (t + q);
    }
  }
    if (count == 0)
    printf("-1");

  printf("\n");
}

int main() {
  int q = 13;
  char text[10000];
  scanf("%[^\n]", text);
  int qtd;
  scanf("%d\n", &qtd);
  char palavra[1000];
  scanf("%[^\n]", palavra);
  char *pt;
  pt = strtok(palavra, " \t\n\r.,:;!?(){}[]<>\"'\\/");
  while (pt) {
    rabinKarp(pt, text, q);
    pt = strtok(NULL, " \t\n\r.,:;!?(){}[]<>\"'\\/");
  }

  return 0;
}
