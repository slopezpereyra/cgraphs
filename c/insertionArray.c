#include "insertionArray.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

InsertionArray *createInsertionArray(u32 size) {
  InsertionArray *insArray = (InsertionArray *)malloc(sizeof(InsertionArray));
  insArray->array = genArray(size);
  insArray->size = size;
  return insArray;
}

void insArrayStore(u32 index, u32 value, InsertionArray *insArray) {
  insArray->array[index] = value + 1;
}

u32 insArrayGet(u32 index, InsertionArray *insArray) {
  return (insArray->array[index] - 1);
}

void printInsertionArray(InsertionArray *insArray) {
  for (u32 i = 0; i < insArray->size; i++)
    printf("InsArray[%d] = %d\n", i, insArrayGet(i, insArray));
}

void dumpInsertionArray(InsertionArray *insArray) {
  free(insArray->array);
  free(insArray);
}
