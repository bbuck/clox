#include <stdio.h>

#include "debug.h"
#include "value.h"
#include "vm.h"

Vm vm;

static void VmResetStack() {
	vm.stack_top = vm.stack;
}

void VmInit() {
	vm.chunk = NULL;
	vm.ip = NULL;
	VmResetStack();
}

void VmFree() {
	vm.chunk = NULL;
	vm.ip = NULL;
	VmResetStack();
}

static InterpretResult Run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define READ_CONSTANT16() (                \
	vm.chunk->constants.values[            \
		(READ_BYTE() << 8) + READ_BYTE()])
#define BINARY_OP(op) \
	do { \
		double b = VmPop(); \
		double a = VmPop(); \
		VmPush(a op b); \
	} while (false)

	while (true) {
#ifdef DEBUG_TRACE_EXECUTION
		fputs("          ", stdout);
		for (Value *slot = vm.stack; slot < vm.stack_top; ++slot) {
			fputs("[ ", stdout);
			PrintValue(*slot);
			fputs(" ]", stdout);
		}
		puts("");

		DisassembleInstruction(vm.chunk, (size_t)(vm.ip - vm.chunk->code));
#endif
		uint8_t instruction;
		switch (instruction = READ_BYTE()) {
			case kOpConstant: {
				Value constant = READ_CONSTANT();
				VmPush(constant);

				break;
			}
			case kOpConstant16: {
				Value constant = READ_CONSTANT16();
				VmPush(constant);

				break;
			}

			// mathematical binary operations
			case kOpAdd: BINARY_OP(+); break;
			case kOpSubtract: BINARY_OP(-); break;
			case kOpMultiply: BINARY_OP(*); break;
			case kOpDivide: BINARY_OP(/); break;

			case kOpNegate:
				VmPush(-VmPop());

				break;
			case kOpReturn: {
				PrintValue(VmPop());
				puts("");

				return kInterpretOk;
			}
		}
	}

#undef BINARY_OP
#undef READ_CONSTANT16
#undef READ_CONSTANT
#undef READ_BYTE
}

InterpretResult VmInterpret(Chunk *chunk) {
	vm.chunk = chunk;
	vm.ip = vm.chunk->code;

	return Run();
}

void VmPush(Value value) {
	*vm.stack_top = value;
	vm.stack_top++;
}

Value VmPop() {
	vm.stack_top--;

	return *vm.stack_top;
}