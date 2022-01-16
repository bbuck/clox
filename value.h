#ifndef CLOX_VALUE_H_
#define CLOX_VALUE_H_

#include "common.h"

typedef double Value;

typedef struct {
	int capacity;
	int count;
	Value *values;
} ValueArray;

void ValueArrayInit(ValueArray *array);
void ValueArrayWrite(ValueArray *array, Value value);
void ValueArrayFree(ValueArray *array);

void PrintValue(Value value);

#endif
