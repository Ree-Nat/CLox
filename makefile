CC=g++ -g -Wall 
clox: main.c chunk.c debug.c memory.c value.c vm.c scanner.c compiler.c table.c object.c
	cc main.c chunk.c debug.c memory.c value.c scanner.c compiler.c vm.c table.c object.c -o clox -g