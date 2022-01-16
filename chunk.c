#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void ChunkInit(Chunk *chunk) {
	chunk->count = 0;
	chunk->capacity = 0;
	chunk->code = NULL;
	chunk->lines = NULL;
	ValueArrayInit(&chunk->constants);
}

void ChunkWrite(Chunk *chunk, uint8_t byte, int line) {
	if (chunk->capacity == chunk->count) {
		int old_cap = chunk->capacity;
		chunk->capacity = GROW_CAPACITY(old_cap);
		chunk->code = GROW_ARRAY(
			uint8_t, chunk->code, old_cap, chunk->capacity);
		chunk->lines = GROW_ARRAY(
			int, chunk->lines, old_cap, chunk->capacity);
	}

	chunk->code[chunk->count] = byte;
	chunk->lines[chunk->count] = line;
	chunk->count++;
}

int ChunkAddConstant(Chunk *chunk, Value value) {
	ValueArrayWrite(&chunk->constants, value);

	return chunk->constants.count - 1;
}

void ChunkFree(Chunk *chunk) {
	FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
	FREE_ARRAY(int, chunk->lines, chunk->capacity);
	ValueArrayFree(&chunk->constants);
	ChunkInit(chunk);
}
