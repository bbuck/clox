#ifndef CLOX_DEBUG_H_
#define CLOX_DEBUG_H_

#include "chunk.h"

void DisassembleChunk(Chunk *chunk, const char *name);
int DisassembleInstruction(Chunk *chunk, size_t offset);

#endif
