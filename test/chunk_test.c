#include <stdlib.h>
#include <stdint.h>

#include <criterion/criterion.h>

#include "../chunk.h"
#include "helpers.h"

Test(Chunk, capacity) {
	Chunk chunk;
	ChunkInit(&chunk);

	cr_assert(
		chunk.capacity == 0, "Expected Chunk::capacity to be %d, but got %zu", 0, chunk.capacity);

	// after 1 write
	ChunkWrite(&chunk, kOpReturn, 1);
	cr_assert(chunk.count == 1, "Expected Chunk::count to be %d, but got %zu", 1, chunk.count);
	cr_assert(
		chunk.capacity == 8,
		"Expected Chunk::capacity to have expanded to be %d, but got %zu",
		8,
		chunk.capacity);

	// after we exceed capacity
	for (int i = 0; i < 8; ++i) {
		ChunkWrite(&chunk, kOpReturn, i + 2);
	}
	cr_assert(chunk.count == 9, "Expected Chunk::count to be %d, but got %zu", 9, chunk.count);
	cr_assert(
		chunk.capacity == 16,
		"Expected Chunk::capacity to have expanded to be %d, but got %zu",
		16,
		chunk.capacity);
}

Test(Chunk, ChunkInit) {
	Chunk chunk;
	ChunkInit(&chunk);

	cr_assert(chunk.count == 0, "Expected Chunk::count to be %d, but got %zu", 0, chunk.count);
	cr_assert(
		chunk.capacity == 0, "Expected Chunk::capacity to be %d, but got %zu", 0, chunk.capacity);
	cr_assert(chunk.code == NULL, "Expected Chunk::code to be NULL, but got %p", chunk.code);
	cr_assert(chunk.lines == NULL, "Expected Chunk::lines to be NULL, but got %p", chunk.lines);
	AssertValueArrayInitialized(&chunk.constants);
}

Test(Chunk, ChunkWrite) {
	Chunk chunk;
	ChunkInit(&chunk);
	ChunkWrite(&chunk, kOpReturn, 1);

	cr_assert(chunk.count == 1, "Expected Chunk::count to be %d, but got %zu", 1, chunk.count);
	cr_assert(
		chunk.capacity == 8, "Expected Chunk::capacity to be %d, but got %zu", 8, chunk.capacity);
	cr_assert(
		chunk.code[0] == kOpReturn,
		"Expected Chunk::code[0] to be kOpReturn (%d), but got %d",
		kOpReturn,
		chunk.code[0]);
	int line = ChunkGetLine(&chunk, 0);
	cr_assert(line == 1, "Expected the first code item to be on line %d, but got %d", 1, line);
}

Test(Chunk, ChunkWriteConstant_kOpConstant16) {
	Chunk chunk;
	ChunkInit(&chunk);

	for (int i = 0; i <= UINT8_MAX; ++i) {
		ChunkWriteConstant(&chunk, 2.6, 1);
	}

	// kOpConstant is two entries, so (n-1) is the index of the value and (n-2) is the opcode
	size_t last_opcode_index = chunk.count - 2;
	cr_assert(
		chunk.count == (256 * 2),
		"Expected Chunk::count to be %d, but got %zu",
		(256 * 2),
		chunk.count);
	cr_assert(
		chunk.code[last_opcode_index] == kOpConstant,
		"Expected Chunk::code[%zu] to be kOpConstant (%d), but got %d",
		last_opcode_index,
		kOpConstant,
		chunk.code[last_opcode_index]);
	cr_assert(
		chunk.code[last_opcode_index + 1] == 0xff,
		"Expected Chunk::code[%zu] to be %02x, but got %02x",
		last_opcode_index + 1,
		0xff,
		chunk.code[last_opcode_index + 1]);

	// write again, should get kOpConstant16
	ChunkWriteConstant(&chunk, 2.6, 2);

	// kOpConstant16 has 2 operands so (n-1) is the lower half, (n-2) is the upper half, and
	// (n-3) is the opcode
	size_t constant16_index = chunk.count - 3;
	cr_assert(
		chunk.count == (256 * 2) + 3,
		"Expected Chunk::count to be %d, but got %zu",
		(256 * 2) + 3,
		chunk.count);
	cr_assert(
		chunk.code[constant16_index] == kOpConstant16,
		"Expected Chunk::code[%zu] to be kOpConstant16 (%d), but got %d",
		constant16_index,
		kOpConstant16,
		chunk.code[constant16_index]);
	cr_assert(
		chunk.code[constant16_index + 1] == 0x01,
		"Expected Chunk::code[%zu] to be %02x (upper half), but got %02x",
		constant16_index + 1,
		0x01,
		chunk.code[constant16_index + 1]);
	cr_assert(
		chunk.code[constant16_index + 2] == 0x00,
		"Expected Chunk::code[%zu] to be %02x (lower half), but got %02x",
		constant16_index + 2,
		0x00,
		chunk.code[constant16_index + 2]);
	int value_index = ((int) chunk.code[constant16_index + 1]) << 8;
	value_index += chunk.code[constant16_index + 2];
	cr_assert(
		value_index == 0x0100,
		"Expected value_index (overall index) to be %04x, but got %04x",
		0x0100,
		value_index);
}

Test(Chunk, ChunkWriteConstant_DoubleValue) {
	Chunk chunk;
	ChunkInit(&chunk);
	ChunkWriteConstant(&chunk, 2.6, 123);

	cr_assert(chunk.count == 2, "Expected Chunk::count to be %d, but got %zu", 2, chunk.count);
	cr_assert(
		chunk.capacity == 8, "Expected Chunk::capacity to be %d, but got %zu", 8, chunk.capacity);

	cr_assert(
		chunk.code[0] == kOpConstant,
		"Expected Chunk::code[0] to be kOpConstant (%d), but got %d",
		kOpConstant,
		chunk.code[0]);
	cr_assert(chunk.code[1] == 0, "Expected Chunk::code[1] to be %d, but got %d", 0, chunk.code[1]);

	cr_assert(
		chunk.constants.count == 1,
		"Expected Chunk::constants::count to be %d, but got %zu",
		1,
		chunk.constants.count);
	cr_assert(
		chunk.constants.values[0] == 2.6,
		"Expected Chunk::constants::values[0] to be %g, but got %g",
		2.6,
		chunk.constants.values[0]);
}
