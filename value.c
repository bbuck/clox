#include <stdio.h>
#include <stdlib.h>

#include "memory.h"
#include "value.h"

static const int kValueBufferLength = 1024;

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

void ValueStackInit(ValueStack *stack) {
	stack->top = 0;
	ValueArrayInit(&stack->array);
}

void ValueStackPush(ValueStack *stack, Value value) {
	if (stack->top < stack->array.count) {
		stack->array.values[stack->top] = value;
	} else {
		ValueArrayWrite(&stack->array, value);
	}

	stack->top += 1;
}

Value ValueStackPop(ValueStack *stack) {
	if (stack->top == 0) {
		return 0.0;
	}

	stack->top -= 1;

	return stack->array.values[stack->top];
}

void ValueStackFree(ValueStack *stack) {
	ValueArrayFree(&stack->array);
}

char *ValueToString(Value value) {
	char *buffer = malloc(sizeof(char) * kValueBufferLength);
	for (int i = 0; i < kValueBufferLength; ++i) {
		buffer[i] = '\0';
	}
	int result = snprintf(buffer, kValueBufferLength, "%g", value);
	if (result == 0) {
		fprintf(stderr, "Failed to convert value to string.");
		exit(2);
	}
	buffer[1024] = '\0';

	return buffer;
}

void PrintValue(Value value) {
	char *value_str = ValueToString(value);
	fputs(value_str, stdout);
	free(value_str);
}
