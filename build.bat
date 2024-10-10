#chcp UTF-8
gcc -c --std=c99 -o temp_functions.o temp_functions.c
gcc -c --std=c99 -o main.o main.c
gcc -o func_temp.exe main.o temp_functions.o
pause
func_temp.exe -h -m12
