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

static int ConstantInstruction(const char *name, Chunk *chunk, size_t offset) {
	Opcode code = chunk->code[offset];

	int constant_loc;
	int offset_change = 2;

	if (code == kOpConstant) {
		constant_loc = chunk->code[offset + 1];
	} else {
		offset_change = 3;
		constant_loc = chunk->code[offset + 1] << 8;
		constant_loc += chunk->code[offset + 2];
	}

	printf("%-16s %4d '", name, constant_loc);
	PrintValue(chunk->constants.values[constant_loc]);
	printf("'\n");

	return offset + offset_change;
}

int DisassembleInstruction(Chunk *chunk, size_t offset) {
	printf("%04zu ", offset);
	int prev_line = ChunkGetLine(chunk, offset - 1);
	int curr_line = ChunkGetLine(chunk, offset);
	if (offset > 0 && curr_line == prev_line) {
		printf("   | ");
	} else {
		printf("%4d ", curr_line);
	}

	uint8_t instruction = chunk->code[offset];
	switch (instruction) {
		case kOpConstant:
			return ConstantInstruction("kOpConstant", chunk, offset);
		case kOpConstant16:
			return ConstantInstruction("kOpConstant16", chunk, offset);
		case kOpAdd:
			return SimpleInstruction("kOpAdd", offset);
		case kOpSubtract:
			return SimpleInstruction("kOpSubtract", offset);
		case kOpMultiply:
			return SimpleInstruction("kOpMultiply", offset);
		case kOpDivide:
			return SimpleInstruction("kOpDivide", offset);
		case kOpNegate:
			return SimpleInstruction("kOpNegate", offset);
		case kOpReturn:
			return SimpleInstruction("kOpReturn", offset);
		default:
			printf("Unknown opcode %d\n", instruction);

			return offset + 1;
	}
}
