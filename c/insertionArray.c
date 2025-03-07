/** MIT License
 *
 * Copyright (c) 2024 Santiago López Pereyra
 *
 * santiagolopezpereyra@gmail.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * The software is provided "as is", without warranty of any kind, express or
 * implied, including but not limited to the warranties of merchantability,
 * fitness for a particular purpose, and noninfringement. In no event shall the
 * authors or copyright holders be liable for any claim, damages, or other
 * liability, whether in an action of contract, tort, or otherwise, arising from,
 * out of or in connection with the software or the use or other dealings in the
 * software.
 */






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
