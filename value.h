#ifndef CLOX_VALUE_H_
#define CLOX_VALUE_H_

#include "common.h"

typedef double Value;

typedef struct ValueArray {
	size_t capacity;
	size_t count;
	Value *values;
} ValueArray;

void ValueArrayInit(ValueArray *array);
void ValueArrayWrite(ValueArray *array, Value value);
void ValueArrayFree(ValueArray *array);

char *ValueToString(Value value);
void PrintValue(Value value);

#endif
