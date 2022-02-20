#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main(void) {
	VmInit();

	Chunk chunk;
	ChunkInit(&chunk);

	ChunkWriteConstant(&chunk, 1.2, 123);
	ChunkWriteConstant(&chunk, 3.4, 123);

	ChunkWrite(&chunk, kOpAdd, 123);
	ChunkWriteConstant(&chunk, 5.6, 123);
	ChunkWrite(&chunk, kOpDivide, 123);

	ChunkWrite(&chunk, kOpNegate, 123);
	ChunkWrite(&chunk, kOpReturn, 123);

	DisassembleChunk(&chunk, "test chunk");
	VmInterpret(&chunk);

	ChunkFree(&chunk);

	VmFree();

	return 0;
}
