#include "graphStruct.h"

u32 max(u32 x, u32 y);
u32 min(u32 x, u32 y);

u32* genArray(u32 size);
void printArray(u32 *array, u32 size);
void removeElement(u32 **array, u32 *size, u32 index);
void removeTargetElement(u32 *array, u32 *size, u32 target);
u32 generate_random_u32();
u32 generate_random_u32_in_range(u32 min, u32 max);
