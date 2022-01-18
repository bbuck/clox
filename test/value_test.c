#include <criterion/criterion.h>

#include "helpers.h"
#include "../value.h"

Test(ValueArray, ValueArrayInit) {
	ValueArray array;
	ValueArrayInit(&array);

	AssertValueArrayInitialized(&array);
}

// NOTE(bbuck): ValueArray uses the same logic to simulate a growable array as Chunk does for
//     Chunk::code so I will omit tests about count and opacity growing.

Test(ValueArray, ValueArrayFree) {
	ValueArray array;
	ValueArrayInit(&array);

	ValueArrayWrite(&array, 2.6);
	ValueArrayFree(&array);

	// it should be initialized again
	AssertValueArrayInitialized(&array);
}


Test(Value, ValueToString) {
	Value value = 2.6;
	char *value_str = ValueToString(value);
	const char *expected = "2.6";

	cr_assert(
		strcmp(expected, value_str) == 0,
		"Expected ValueToString(%g) == \"%s\", but got \"%s\"",
		2.6,
		expected,
		value_str);
	free(value_str);
}
