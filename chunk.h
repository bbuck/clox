#ifndef CLOX_CHUNK_H_
#define CLOX_CHUNK_H_

#include "common.h"
#include "value.h"
#include "tools/line_encoding.h"

typedef enum Opcode {
	kOpConstant,
	kOpConstant16,
	kOpReturn,
} Opcode;

typedef struct Chunk {
	size_t count;
	size_t capacity;
	uint8_t *code;
	LineInfoList *lines;
	ValueArray constants;
} Chunk;

void ChunkInit(Chunk *chunk);
void ChunkWrite(Chunk *chunk, uint8_t byte, int line);
void ChunkWriteConstant(Chunk *chunk, Value value, int line);
int ChunkGetLine(Chunk *chunk, int instruction_loc);
void ChunkFree(Chunk *chunk);

#endif
