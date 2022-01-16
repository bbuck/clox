#ifndef CLOX_CHUNK_H_
#define CLOX_CHUNK_H_

#include "common.h"
#include "value.h"

typedef enum {
	kOpConstant,
	kOpReturn,
} Opcode;

typedef struct {
	int count;
	int capacity;
	uint8_t *code;
	int *lines;
	ValueArray constants;
} Chunk;

void ChunkInit(Chunk *chunk);
void ChunkWrite(Chunk *chunk, uint8_t byte, int line);
int ChunkAddConstant(Chunk *chunk, Value value);
void ChunkFree(Chunk *chunk);

#endif
