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
