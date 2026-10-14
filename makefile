CFLAGS = -Wall -Wextra -g -O0
clox: main.c chunk.c debug.c memory.c value.c vm.c scanner.c compiler.c 
	cc main.c chunk.c debug.c memory.c value.c scanner.c compiler.c vm.c -o clox