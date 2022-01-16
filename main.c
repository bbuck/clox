#include "common.h"
#include "chunk.h"
#include "debug.h"

int main(void) {
	Chunk chunk;
	ChunkInit(&chunk);

	ChunkWriteConstant(&chunk, 1.2, 123);
	ChunkWrite(&chunk, kOpReturn, 123);

	DisassembleChunk(&chunk, "test chunk");

	ChunkFree(&chunk);

	return 0;
}
