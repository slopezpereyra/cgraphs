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






/**
 * @file insertionArray.c
 * @brief Implementation of an Insertion Array. This struct
 * is trivially simple. However, its use makes code more readable whenever
 * dealing with insertion arrays.
 *
 */

#ifndef INSERTION_ARRAY_H
#define INSERTION_ARRAY_H

#include <stdint.h>
typedef uint32_t u32;

typedef struct {
  u32 *array;
  u32 size;
} InsertionArray;

InsertionArray *createInsertionArray(u32 size);
void insArrayStore(u32 index, u32 value, InsertionArray *insArray);
u32 insArrayGet(u32 index, InsertionArray *insArray);
void printInsertionArray(InsertionArray *insArray);
void dumpInsertionArray(InsertionArray *insArray);

#endif // INSERTION_ARRAY_H
