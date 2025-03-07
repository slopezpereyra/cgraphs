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






#ifndef P1_ESTRUCTURAGRAFO24_H
#define P1_ESTRUCTURAGRAFO24_H

#include <stdbool.h>
#include <stdint.h>

typedef unsigned int g_flag;

#define STD_FLAG (0)             // 0000
#define COL_FLAG (1 << 0)        // 0001
#define W_FLAG (1 << 1)          // 0010
#define D_FLAG (1 << 2)          // 0100
#define CAP_FLAG (1 << 3)        // 1000
#define NETFLOW_FLAG (( W_FLAG | D_FLAG ) | CAP_FLAG) // 1110

typedef uint32_t u32;
typedef u32 color;

typedef struct {
  u32 x;
  u32 y;
  u32 *w; // weight, or distance, or flow in case of flow networks
  u32 *c; //  capacity, a limit for the weight/flow
} Edge;

typedef struct {
  u32 n;
  u32 m;
  u32 Δ;
  u32 *_degrees;
  u32 *_outdegrees;
  u32 *_indegrees;
  Edge *_edges;
  u32 _edgeArraySize;
  color *_colors;
  u32 *_firstneighbour;
  bool _formatted;
  g_flag _g_flag;
} Graph;

#endif
