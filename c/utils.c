/**
 * @file utilities.c
 * @brief Utility functions for graph operations and array manipulation.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphStruct.h"

/**
 * @brief Returns the maximum of two unsigned integers.
 * @param x First unsigned integer.
 * @param y Second unsigned integer.
 * @return Maximum of x and y.
 */
u32 max(u32 x, u32 y) {
    return (x > y ? x : y);
}

/**
 * @brief Returns the minimum of two unsigned integers.
 * @param x First unsigned integer.
 * @param y Second unsigned integer.
 * @return Minimum of x and y.
 */
u32 min(u32 x, u32 y) {
    return (x > y ? y : x);
}

/**
 * @brief Prints the elements of an array.
 * @param array Pointer to the array to print.
 * @param size Number of elements in the array.
 */
void printArray(u32 *array, u32 size) {
    for (u32 i = 0; i < size; i++) {
        printf("A[%d] = %d\n", i, array[i]);
    }
}

/**
 * @brief Generates an array of unsigned integers initialized to zero.
 * @param size Number of elements in the array.
 * @return Pointer to the generated array.
 */
u32* genArray(u32 size) {
    u32* array = (u32*)calloc(size, sizeof(u32));
    if (array == NULL) {
        printf("Error: calloc failed\n");
        exit(1);
    }
    return array;
}

/**
 * @brief Removes an element at a specified index from an array.
 * @param array Pointer to the array of unsigned integers.
 * @param size Pointer to the size of the array.
 * @param index Index of the element to remove.
 */
void removeElement(u32 **array, u32 *size, u32 index) {
    assert(*size != 0 && index < *size);
    for (u32 i = index; i < *size - 1; i++) {
        (*array)[i] = (*array)[i + 1];
    }
    *size -= 1;
}

/**
 * @brief Removes the first occurrence of a target element from an array.
 * @param array Pointer to the array of unsigned integers.
 * @param size Pointer to the size of the array.
 * @param target The element to remove.
 */
void removeTargetElement(u32 *array, u32 *size, u32 target) {
    for (u32 i = 0; i < *size; i++) {
        if (array[i] == target) {
            removeElement(&array, size, i);
            break;
        }
    }
}

/**
 * @brief Generates a random unsigned 32-bit integer.
 * @return A random unsigned 32-bit integer.
 */
u32 generate_random_u32() {
    u32 random_num = ((u32)rand() << 16) | (u32)rand();
    return random_num;
}

/**
 * @brief Generates a random unsigned 32-bit integer within a specified range.
 * @param min Minimum value of the range.
 * @param max Maximum value of the range.
 * @return A random unsigned 32-bit integer within the range [min, max].
 */
u32 generate_random_u32_in_range(u32 min, u32 max) {
    u32 range = max - min + 1;
    u32 limit = UINT32_MAX - (UINT32_MAX % range);
    u32 random_num;

    do {
        random_num = generate_random_u32();
    } while (random_num >= limit);

    return (random_num % range) + min;
}
