#include <stdio.h>

#include "debug.h"
#include "value.h"

void DisassembleChunk(Chunk *chunk, const char *name) {
	printf("== %s ==\n", name);

	for (int offset = 0; offset < chunk->count;) {
		offset = DisassembleInstruction(chunk, offset);
	}
}

static int SimpleInstruction(const char *name, int offset) {
	printf("%s\n", name);

	return offset + 1;
}

static int ConstantInstruction(const char *name, Chunk *chunk, int offset) {
	uint8_t constant_loc = chunk->code[offset + 1];
	printf("%-16s %4d '", name, constant_loc);
	PrintValue(chunk->constants.values[constant_loc]);
	printf("'\n");

	return offset + 2;
}

int DisassembleInstruction(Chunk *chunk, int offset) {
	printf("%04d ", offset);
	if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1]) {
		printf("   | ");
	} else {
		printf("%4d ", chunk->lines[offset]);
	}

	uint8_t instruction = chunk->code[offset];
	switch (instruction) {
		case kOpConstant:
			return ConstantInstruction("kOpConstant", chunk, offset);
		case kOpReturn:
			return SimpleInstruction("kOpReturn", offset);
		default:
			printf("Unknown opcode %d\n", instruction);

			return offset + 1;
	}
}
