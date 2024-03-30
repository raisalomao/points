#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS_PER_LINE 100000
#define MAX_PALAVRAS_POR_LINHA 10000
#define MAX_COORDENADAS_POR_LINHA 10000

typedef struct {
  char palavra[100];
} Strings;

typedef struct {
  double x, y;
} Coordenadas;

typedef struct {
  int inteiro;
} Inteiros;

typedef struct {
  float real;
} Floats;

int isWord(const char *str) {
  for (int i = 0; str[i] != '\0'; i++) {
    if (!isalpha(str[i])) {
      return 0;
    }
  }
  return 1;
}

void ordenarInteiros(Inteiros inteiros[], int n) {
  Inteiros temp;
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (inteiros[j].inteiro > inteiros[j + 1].inteiro) {
        temp = inteiros[j];
        inteiros[j] = inteiros[j + 1];
        inteiros[j + 1] = temp;
      }
    }
  }
}

void ordenarFloats(Floats reais[], int n) {
  Floats temp;
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (reais[j].real > reais[j + 1].real) {
        temp = reais[j];
        reais[j] = reais[j + 1];
        reais[j + 1] = temp;
      }
    }
  }
}

void ordemAlfabetica(Strings palavras[], int n) {
  Strings temp;
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      if (strcmp(palavras[j].palavra, palavras[i].palavra) < 0) {
        temp = palavras[i];
        palavras[i] = palavras[j];
        palavras[j] = temp;
      }
    }
  }
}

void ordenarCoordenadas(Coordenadas pontos[], int n) {
  Coordenadas temp;
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      double distI = sqrt(pow(pontos[i].x, 2) + pow(pontos[i].y, 2));
      double distJ = sqrt(pow(pontos[j].x, 2) + pow(pontos[j].y, 2));
      if (distJ < distI) {
        temp = pontos[i];
        pontos[i] = pontos[j];
        pontos[j] = temp;
      }
    }
  }
}

int main() {

  Inteiros numInt[MAX_PALAVRAS_POR_LINHA];
  Floats numFloat[MAX_PALAVRAS_POR_LINHA];
  Strings words[MAX_PALAVRAS_POR_LINHA];
  Coordenadas points[MAX_COORDENADAS_POR_LINHA];

  char entrada[MAX_CHARS_PER_LINE];
  FILE *fileIn = fopen("../q2/base/L0Q2.in", "r");
  FILE *fileOut = fopen("../q2/R0Q2.out", "w");

  while (fgets(entrada, sizeof(entrada), fileIn)) {
    int numPalavras = 0, numCoords = 0, numInteiros = 0, numFloats = 0;

    char *token = strtok(entrada, " \n");
    while (token != NULL) {
      float num = atof(token);
      if ((int)num == num)
        numInt[numInteiros++].inteiro = (int)num;
      else
        numFloat[numFloats++].real = num;

      if (isWord(token)) {
        if (numPalavras < MAX_PALAVRAS_POR_LINHA) {
          strcpy(words[numPalavras].palavra, token);
          numPalavras++;
        }
      } else if (strstr(token, "(") != NULL) {
        if (numCoords < MAX_COORDENADAS_POR_LINHA)
          sscanf(token, "(%lf,%lf)", &points[numCoords].x,
                 &points[numCoords].y);
        numCoords++;
      }
      token = strtok(NULL, " \n");
    }

    ordemAlfabetica(words, numPalavras);
    ordenarInteiros(numInt, numInteiros);
    ordenarFloats(numFloat, numFloats);
    ordenarCoordenadas(points, numCoords);

    fprintf(fileOut, "str:");
    if (numPalavras == 0) {
      fprintf(fileOut, " ");
    } else {
      for (int i = 0; i < numPalavras; i++)
        fprintf(fileOut, "%s ", words[i].palavra);
    }

    fprintf(fileOut, "int:");
    for (int i = 0; i < numInteiros; i++) {
      if (numInt[i].inteiro != 0)
        fprintf(fileOut, "%d ", numInt[i].inteiro);
      if (numInt[i].inteiro == 0 && numInteiros == 1)
        fprintf(fileOut, " ");
    }

    fprintf(fileOut, "float:");
    if (numFloats == 0) {
      fprintf(fileOut, " ");
    } else {
      for (int i = 0; i < numFloats; i++) {
        if ((numFloat[i].real * 10) - (int)(numFloat[i].real * 10) == 0.0)
          fprintf(fileOut, "%.1f ", numFloat[i].real);
        else
          fprintf(fileOut, "%.2f ", numFloat[i].real);
      }
    }

    fprintf(fileOut, "p:");
    for (int i = 0; i < numCoords; i++) {
      if ((int)points[i].x == points[i].x && (int)points[i].y == points[i].y)
        fprintf(fileOut, "(%.0lf,%.0lf) ", points[i].x, points[i].y);
      else
        fprintf(fileOut, "(%.1lf,%.1lf) ", points[i].x, points[i].y);
    }
    fprintf(fileOut, "\n");
  }

  fclose(fileIn);
  fclose(fileOut);
  printf("Os argumentos foram gravados no arquivo de saída.\n");

  return 0;
}