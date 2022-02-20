#ifndef CLOX_VALUE_H_
#define CLOX_VALUE_H_

#include "common.h"

typedef double Value;

typedef struct ValueArray {
	size_t capacity;
	size_t count;
	Value *values;
} ValueArray;

typedef struct ValueStack {
	size_t top;
	ValueArray array;
} ValueStack;

void ValueArrayInit(ValueArray *array);
void ValueArrayWrite(ValueArray *array, Value value);
void ValueArrayFree(ValueArray *array);

void ValueStackInit(ValueStack *stack);
void ValueStackPush(ValueStack *stack, Value value);
Value ValueStackPop(ValueStack *stack);
void ValueStackFree(ValueStack *stack);

char *ValueToString(Value value);
void PrintValue(Value value);

#endif
