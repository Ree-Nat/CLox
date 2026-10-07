#ifndef clox_chunk_h
#define clox_chunk_h


#include "common.h"
#include "value.h"

typedef enum {
    OP_CONSTANT,
    OP_RETURN,
} OpCode;

typedef struct{
    int count;
    int capacity;
    ValueArray constants;
    uint8_t* code;   /* data */
}Chunk;

void initChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte);
int addConstant(Chunk* chunk, Value value);
void freeChunk(Chunk* chunk);

#endif