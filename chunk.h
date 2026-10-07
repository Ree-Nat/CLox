#ifndef clox_chunk_h
#define clox_chunk_h


#include "common.h"
#include "value.h"

typedef enum {
    OP_CONSTANT,
    OP_CONSTANT_LONG,
    OP_RETURN,
} OpCode;

typedef struct {
  int offset;
  int line;
} LineStart;



typedef struct{
    int count;
    int capacity;
    int* lines;
    ValueArray constants;
    uint8_t* code;   /* data */

    int lineCount;
    int lineCapacity;
    LineStart* lines; 

}Chunk;

void initChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
int addConstant(Chunk* chunk, Value value);
void freeChunk(Chunk* chunk);
void writeConstant(Chunk* chunk, Value value, int line);
int getLine(Chunk* chunk, int instruction);

#endif