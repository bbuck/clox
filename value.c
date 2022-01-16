#include <stdio.h>

#include "memory.h"
#include "value.h"

void ValueArrayInit(ValueArray *array) {
	array->values = NULL;
	array->capacity = 0;
	array->count = 0;
}

void ValueArrayWrite(ValueArray *array, Value value) {
	if (array->capacity <= array->count) {
		size_t old_cap = array->capacity;
		array->capacity = GROW_CAPACITY(old_cap);
		array->values = GROW_ARRAY(
			Value, array->values, old_cap, array->capacity);
	}

	array->values[array->count] = value;
	array->count++;
}

void ValueArrayFree(ValueArray *array) {
	FREE_ARRAY(Value, array->values, array->capacity);
	ValueArrayInit(array);
}

void PrintValue(Value value) {
	printf("%g", value);
}
