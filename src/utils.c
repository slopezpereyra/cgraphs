#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "EstructuraGrafo24.h"

u32 max(u32 x, u32 y) {
    return ( x > y ? x : y );
}

u32 min(u32 x, u32 y) {
    return ( x > y ? y : x );
}

void printArray(u32 *array, u32 size){
    for (u32 i = 0; i < size; i++){
        printf("A[%d] = %d\n", i, array[i]);
    }
}

u32* genArray(u32 size){
    u32* array = (u32*)calloc(size, sizeof(u32));
    if (array == NULL){
        printf("Error: calloc failed\n");
        exit(1);
    }
    return(array);
}



void removeElement(u32 **array, u32 *size, u32 index) {
    assert(*size != 0 && index < *size);
    // Shift elements to the left starting from index
    for (u32 i = index; i < *size - 1; i++) {
        (*array)[i] = (*array)[i + 1];
    }

    // Decrease the *size of the array
    *size -= 1;
}

void removeTargetElement(u32 *array, u32 *size, u32 target) {
    for (u32 i = 0; i < *size; i++) {
        if ( array [i] == target) {
            removeElement(&array, size, i);
            break;
        }
    }
}


u32 generate_random_u32() {
    u32 random_num = ((u32)rand() << 16) | (u32)rand();
    return random_num;
}

u32 generate_random_u32_in_range(u32 min, u32 max) {
    u32 range = max - min + 1;
    u32 limit = UINT32_MAX - (UINT32_MAX % range);
    u32 random_num;

    do {
        random_num = generate_random_u32();
    } while (random_num >= limit);

    return (random_num % range) + min;
}
