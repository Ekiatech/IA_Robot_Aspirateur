all: main.o robot.o map.o display.o
	gcc -g -o main main.o robot.o map.o display.o

robot.o: robot.c robot.h
	gcc -c robot.c

map.o: map.c map.h robot.h
	gcc -c map.c

display.o: display.c display.h map.h robot.h
	gcc -c display.c

clean:
	rm -f main *.o