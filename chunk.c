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
	if (chunk->capacity <= chunk->count) {
		size_t old_cap = chunk->capacity;
		chunk->capacity = GROW_CAPACITY(old_cap);
		chunk->code = GROW_ARRAY(
			uint8_t, chunk->code, old_cap, chunk->capacity);
	}

	chunk->code[chunk->count] = byte;
	if (chunk->lines == NULL) {
		chunk->lines = LineInfoListCreate();
	}
	LineInfoListAddLine(chunk->lines, line);
	chunk->count++;
}

int ChunkGetLine(Chunk *chunk, size_t instruction_loc) {
	return LineInfoListGetLine(chunk->lines, instruction_loc);
}

void ChunkWriteConstant(Chunk *chunk, Value value, int line) {
	ValueArrayWrite(&chunk->constants, value);
	size_t constant_loc = chunk->constants.count - 1;

	if (constant_loc <= UINT8_MAX) {
		ChunkWrite(chunk, kOpConstant, line);
		ChunkWrite(chunk, constant_loc, line);

		return;
	}

	ChunkWrite(chunk, kOpConstant16, line);
	// take the first 8 bits from a 16 bit number
	int start_loc = (constant_loc & 0xFF00) >> 8;
	int end_loc = (constant_loc & 0xFF);
	ChunkWrite(chunk, start_loc, line);
	ChunkWrite(chunk, end_loc, line);

	// TODO(bbuck): support further levels?
}

void ChunkFree(Chunk *chunk) {
	FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
	ValueArrayFree(&chunk->constants);
	LineInfoListFree(&chunk->lines);
	ChunkInit(chunk);
}
