all: func_temp.exe

func_temp.exe: main.o temp_functions.o
	gcc -o func_temp.exe main.o temp_functions.o

main.o: main.c temp_functions.h
	gcc -c --std=c11 -o main.o main.c

temp_functions.o: temp_functions.c
	gcc -c --std=c11 -o temp_functions.o temp_functions.c

clean:
	del *.o 
	del func_temp.exe