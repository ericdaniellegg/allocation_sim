main: main.o file_in.o allocation.o
	gcc main.o file_in.o allocation.o -ggdb -o main

main.o: main.c file_in.h allocation.h file_in.h
	gcc -c main.c

allocation.o: allocation.c file_in.h allocation.h
	gcc -c allocation.c	

file_in.o: file_in.c file_in.h allocation.h
	gcc -c file_in.c

clean:
	rm *.o ; rm main 
