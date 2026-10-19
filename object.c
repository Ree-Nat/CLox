#include <stdio.h>
#include <string.h>

#include "memory.h"
#include "object.h"
#include "value.h"
#include "vm.h"



#define ALLOCATE_OBJ(type, objectType) \
    (type*)allocateObject(sizeof(type), objectType)

static Obj* allocateObject(size_t size, ObjType type) {
  Obj* object = (Obj*)reallocate(NULL, 0, size);
  object->type = type;

  object->next = vm.objects;
  vm.objects = object;
  return object;
}

//ch19 challenge create a string by allocating memory
ObjString* createString(int length) {
    ObjString* string = (ObjString*)allocateObject(sizeof(ObjString) + length + 1, OBJ_STRING);
    string->length = length;
    return string;
}


//no need
/*
static ObjString* allocateString(char* chars, int length) {
  ObjString* string = ALLOCATE_OBJ(ObjString, OBJ_STRING);
  string->length = length;
  string->chars = chars;
  return string;
}
*/

//instead take from parameter
ObjString* takeString(char* chars, int length) {
  ObjString* string = copyString(chars, length);
  //return allocateString(chars, length);
  return string;
}

//Copy the string from the parameter instead of buffer allocation
ObjString* copyString(const char* chars, int length) {
    ObjString* string = createString(length);
    memcpy(string->chars, chars, length);
    string->chars[length] = '\0';
    return string;

}

void printObject(Value value) {
  switch (OBJ_TYPE(value)) {
    case OBJ_STRING:
      printf("%s", AS_CSTRING(value));
      break;
  }
}