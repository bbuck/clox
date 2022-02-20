#ifndef CLOX_VM_H_
#define CLOX_VM_H_

#include "chunk.h"
#include "common.h"
#include "value.h"

#define STACK_MAX 256

typedef struct Vm {
	Chunk *chunk;
	uint8_t *ip;
	Value stack[STACK_MAX];
	Value *stack_top;
} Vm;

typedef enum InterpretResult {
	kInterpretOk,
	kInterpretCompileError,
	kInterpretRuntimeError,
} InterpretResult;

void VmInit();
void VmFree();
InterpretResult VmInterpret(Chunk *chunk);
void VmPush(Value value);
Value VmPop();

#endif
