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






#include "graphStruct.h"

u32 max(u32 x, u32 y);
u32 min(u32 x, u32 y);

u32 *genArray(u32 size);
void printArray(u32 *array, u32 size);
void removeElement(u32 **array, u32 *size, u32 index);
void removeTargetElement(u32 *array, u32 *size, u32 target);
u32 generate_random_u32();
u32 generate_random_u32_in_range(u32 min, u32 max);
void swap_u32_pointers(u32 *x, u32 *y);
u32 findMin(u32 arr[], u32 size);
