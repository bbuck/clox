#include "common.h"
#include "chunk.h"
#include "debug.h"

int main(void) {
	Chunk chunk;
	ChunkInit(&chunk);

	int constant_loc = ChunkAddConstant(&chunk, 1.2);
	ChunkWrite(&chunk, kOpConstant, 123);
	ChunkWrite(&chunk, constant_loc, 123);
	ChunkWrite(&chunk, kOpReturn, 123);

	DisassembleChunk(&chunk, "test chunk");

	ChunkFree(&chunk);

	return 0;
}
