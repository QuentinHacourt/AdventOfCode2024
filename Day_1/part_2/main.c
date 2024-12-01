#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 1000

FILE *openFile(const char *filename, const char *mode);
int readFileToLists(FILE *file, int **list1, int **list2);
void exchange(int *list, int a, int b);
int similarityScore(int *list1, int *list2);
int abs(int number);

FILE *openFile(const char *filename, const char *mode) {
  FILE *file = fopen(filename, mode);
  if (file == NULL) {
    perror("Unable to open file \"data.txt\"");
  }
  return file;
}

int readFileToLists(FILE *file, int **list1, int **list2) {
  *list1 = (int *)malloc(ARRAY_SIZE * sizeof(int));
  *list2 = (int *)malloc(ARRAY_SIZE * sizeof(int));

  size_t index = 0;
  int num1, num2;

  while (fscanf(file, "%d %d", &num1, &num2) == 2) {
    if (index >= ARRAY_SIZE) {
      fprintf(stderr, "Error: too many numbers in file\n");
      free(*list1);
      free(*list2);
      fclose(file);
      return -1;
    }
    (*list1)[index] = num1;
    (*list2)[index] = num2;
    index++;
  }

  return 0;
}

void exchange(int *list, int a, int b) {
  int t = list[a];
  list[a] = list[b];
  list[b] = t;
}

void sort(int *list) {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    int min = i;
    for (int j = i + 1; j < ARRAY_SIZE; j++)
      if (list[j] < list[min])
        min = j;
    exchange(list, i, min);
  }
}

int abs(int number) {
  if (number < 0)
    return -number;

  return number;
}

int countAppearances(int number, int *list) {
  int sum = 0;
  for (int i = 0; i < ARRAY_SIZE; i++)
    if (number == list[i])
      sum++;

  return sum;
}

int similarityScore(int *list1, int *list2) {
  int sum = 0;
  for (int i = 0; i < ARRAY_SIZE; i++) {
    int num = list1[i];
    int amountInList2 = countAppearances(num, list2);
    sum += num * amountInList2;
  }

  return sum;
}

int main() {
  // TODO: read file
  FILE *file = openFile("data.txt", "r");
  if (file == NULL) {
    return 1;
  }

  // TODO: put data in two lists
  int *list1, *list2;
  if (readFileToLists(file, &list1, &list2) == -1) {
    return 1;
  }

  // TODO: sort two lists
  sort(list1);
  sort(list2);

  // TODO: calculate sum of differences
  int sum = similarityScore(list1, list2);

  // TODO: print results
  printf("Sum of differences: %d \n", sum);
}
