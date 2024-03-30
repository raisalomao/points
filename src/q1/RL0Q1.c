#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define maxCharsperLines 100000

typedef struct {
  double x, y;
} Point;

double calcDistance(Point p1, Point p2) {
  return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

void bubbleSort(Point points[], int n) {
  Point temp;
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      double distanciaI = calcDistance(points[i], (Point){0, 0});
      double distanciaJ = calcDistance(points[j], (Point){0, 0});
      if (distanciaJ < distanciaI) {
        temp = points[i];
        points[i] = points[j];
        points[j] = temp;
      }
    }
  }
}

int main() {
  Point *points;
  char input[maxCharsperLines];
  int numCoordenadas;

  FILE *fileIn = fopen("../q1/base/L0Q1.in", "r");
  FILE *fileOut = fopen("../q1/R0Q1.out", "w");

  while (fgets(input, sizeof(input), fileIn)) {
    numCoordenadas = 0;
    for (int i = 0; input[i] != '\0'; i++) {
      if (input[i] == '(')
        numCoordenadas++;
    }
    points = (Point *)malloc(numCoordenadas * sizeof(Point));

    int index = 0;
    for (int i = 0; input[i] != '\0'; i++) {
      if (input[i] == '(') {
        sscanf(input + i, "(%lf,%lf)", &points[index].x, &points[index].y);
        index++;
      }
    }

    double totalDistance = 0;
    for (int i = 0; i < numCoordenadas - 1; i++)
      totalDistance += calcDistance(points[i], points[i + 1]);

    double shortcutDistance;
    shortcutDistance = calcDistance(points[0], points[numCoordenadas - 1]);

    // Ordena e escreve no arquivo de saída
    bubbleSort(points, numCoordenadas);
    fprintf(fileOut, "points ");
    for (int i = 0; i < numCoordenadas; i++)
      fprintf(fileOut, "(%.0lf,%.0lf) ", points[i].x, points[i].y);

    fprintf(fileOut, "distance %.2lf ", totalDistance);
    fprintf(fileOut, "shortcut %.2lf ", shortcutDistance);

    fprintf(fileOut, "\n");
    free(points);
  }

  fclose(fileIn);
  fclose(fileOut);
  printf("Os pontos foram gravados e ordenados no arquivo de saída.\n");

  return 0;
}