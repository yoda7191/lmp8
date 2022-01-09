GCC_C = gcc -c
GCC_O = gcc -o 
DEL = rm *.o 
FLAGS = -pedantic -Wextra -Wall

standard: main.o alex.o fun_stack.o parser.o 
	$(GCC_O) standard main.o alex.o fun_stack.o parser.o 
	$(DEL)
main.o: main.c parser.h alex.h
	$(GCC_C) main.c $(FLAGS)
alex.o: alex.c alex.h
	$(GCC_C) alex.c $(FLAGS)
fun_stack.o: fun_stack.c fun_stack.h global.h
	$(GCC_C) fun_stack.c $(FLAGS)
parser.o: parser.c parser.h
	$(GCC_C) parser.c $(FLAGS)

test: test_main.o fun_stack.o
	$(GCC_O) test test_main.o fun_stack.o
	$(DEL)
test_main.o: test_main.c fun_stack.h
	$(GCC_C) test_main.c
fun_stack.o: fun_stack.c fun_stack.h global.h