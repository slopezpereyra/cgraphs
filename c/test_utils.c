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






#include "utils.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Test max function
void test_max() {
  assert(max(5, 10) == 10);
  assert(max(10, 5) == 10);
  assert(max(0, 0) == 0);
  assert(max(4294967295U, 1000) == 4294967295U); // Maximum u32 value
  printf("test_max passed\n");
}

// Test min function
void test_min() {
  assert(min(5, 10) == 5);
  assert(min(10, 5) == 5);
  assert(min(0, 0) == 0);
  assert(min(4294967295U, 1000) == 1000);
  printf("test_min passed\n");
}

// Test genArray function
void test_genArray() {
  u32 size = 10;
  u32 *array = genArray(size);
  assert(array != NULL);
  for (u32 i = 0; i < size; i++) {
    assert(array[i] == 0); // Verify all elements are initialized to zero
  }
  free(array);
  printf("test_genArray passed\n");
}

// Test removeElement function
void test_removeElement() {
  u32 size = 5;
  u32 *array = genArray(size);
  for (u32 i = 0; i < size; i++)
    array[i] = i + 1; // array = [1, 2, 3, 4, 5]

  removeElement(&array, &size,
                2); // Remove element at index 2 -> array = [1, 2, 4, 5]
  assert(size == 4);
  assert(array[0] == 1 && array[1] == 2 && array[2] == 4 && array[3] == 5);

  free(array);
  printf("test_removeElement passed\n");
}

// Test removeTargetElement function
void test_removeTargetElement() {
  u32 size = 5;
  u32 *array = genArray(size);
  for (u32 i = 0; i < size; i++)
    array[i] = i + 1; // array = [1, 2, 3, 4, 5]

  removeTargetElement(array, &size,
                      3); // Remove target element 3 -> array = [1, 2, 4, 5]
  assert(size == 4);
  assert(array[0] == 1 && array[1] == 2 && array[2] == 4 && array[3] == 5);

  free(array);
  printf("test_removeTargetElement passed\n");
}

// Test generate_random_u32 function
void test_generate_random_u32() {
  u32 random1 = generate_random_u32();
  u32 random2 = generate_random_u32();
  assert(random1 != random2); // Not guaranteed but likely
  printf("test_generate_random_u32 passed\n");
}

// Test generate_random_u32_in_range function
void test_generate_random_u32_in_range() {
  u32 min = 100, max = 200;
  for (int i = 0; i < 1000; i++) {
    u32 random = generate_random_u32_in_range(min, max);
    assert(random >= min && random <= max);
  }
  printf("test_generate_random_u32_in_range passed\n");
}

void test_swap_pointers() {

  u32 x = 5;
  u32 y = 10;

  swap_u32_pointers(&x, &y);
  assert(x == 10);
  assert(y == 5);
}

// Main function to run all tests
int main() {
  srand((unsigned int)time(NULL)); // Seed random number generator

  test_max();
  test_min();
  test_genArray();
  test_removeElement();
  test_removeTargetElement();
  test_generate_random_u32();
  test_generate_random_u32_in_range();
  test_swap_pointers();

  printf("All tests passed\n");
  return 0;
}
