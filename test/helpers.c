#include <stdlib.h>

#include <criterion/criterion.h>

#include "helpers.h"

void AssertValueArrayInitialized(ValueArray *array) {
	cr_assert(array->count == 0, "Expected ValueArray::count to be %d, but got %zu", 0, array->count);
	cr_assert(
		array->capacity == 0,
		"Expected ValueArray::capacity to be %d, but got %zu",
		0,
		array->capacity);
	cr_assert(
		array->values == NULL, "Expected ValueArray::values to be NULL, but got %p", array->values);
}
