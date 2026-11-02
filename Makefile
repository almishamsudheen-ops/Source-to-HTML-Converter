SRC:= $(wildcard *.c)
OBJ:=$(patsubst %.c,%.o,$(SRC))
a.out:$(OBJ)
	gcc -o $@ $(OBJ) -Wall

clear:
	rm *.o *.out