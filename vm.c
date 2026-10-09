#include "common.h"
#include "vm.h"
#include <stdio.h>
#include "debug.h"

VM vm;
ValueArray stackArray;

static void resetStack() {
  freeValueArray(&stackArray);
  initValueArray(&stackArray);    
}


void initVM(){
  initValueArray(&stackArray);
  vm.valueArray = &stackArray;
}

void freeVM(){
  freeValueArray(&stackArray);
}



static InterpretResult run() {
  #define READ_BYTE() (*vm.ip++)
  #define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
  #define BINARY_OP(op) \
            do { \ 
              double b = pop(&stackArray); \
              double a = pop(&stackArray); \
              push(a op b); \
            } while (false)

    for (;;) {
  #ifdef DEBUG_TRACE_EXECUTION
      printf("      ");
      for(Value slot = stackArray.values[stackArray.count]; slot < stackArray.count; slot++)
      {
        printf("[ ");
        printValue(slot);
        printf(" ]");
      }
      printf("\n");
      disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
  #endif

      uint8_t instruction;
      switch (instruction = READ_BYTE()) {
        case OP_CONSTANT: {
          Value constant = READ_CONSTANT();
          push(constant);
          break;
        }
      case OP_NEGATE: push(-pop(&stackArray)); break;
      case OP_ADD:      BINARY_OP(+); break;
      case OP_SUBTRACT: BINARY_OP(-); break;
      case OP_MULTIPLY: BINARY_OP(*); break;
      case OP_DIVIDE:   BINARY_OP(/); break;
        case OP_RETURN: {
          printValue(pop(&stackArray));
          printf("\n");
          return INTERPRET_OK;
        }
      }
    }
  #undef READ_BYTE
  #undef READ_CONSTANT
}

InterpretResult interpret(Chunk* chunk) {
    vm.chunk = chunk;
    vm.ip = vm.chunk->code;
    return run();
}

void push(Value value) {
  writeValueArray(&stackArray, value);
}

Value pop(ValueArray* valueArray) {
    Value item = valueArray->values[valueArray->count];
    valueArray->count -= 1;
    return item;
}
