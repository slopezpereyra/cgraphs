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

Graph *genCompleteGraph(u32 n);
u32 generate_random_u32();
u32 generate_random_u32_in_range(u32 min, u32 max);
Graph *genConnectedGraph(u32 n, u32 m);
Graph *genConnectedGraph2(u32 n, u32 m);
Graph *fromPruferSequence(u32* seq, u32 seq_len);
u32** genGammaComplements(Graph *G);
Graph *genFromRandomTree(u32 n, u32 m);
Graph *genCGraphUnbound(u32 n);
Graph *genFromKn(u32 n, u32 m);
u32** genGammas(Graph *G);
Graph *randomTree(u32 n);
