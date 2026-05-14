main.exe: Objects\main.o Objects\funciones.o
	gcc -o main Objects\main.o Objects\funciones.o

Objects\main.o: main.c snake.h
	gcc -c main.c -o Objects\main.o

Objects\funciones.o: funciones.c snake.h
	gcc -c funciones.c -o Objects\funciones.o

clean:	
	del Objects\main.o