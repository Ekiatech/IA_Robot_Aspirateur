all: main.o robot.o map.o queue.o display.o queue_informed_algo.o
	gcc -o main main.o robot.o map.o queue.o display.o queue_informed_algo.o -pthread -lm && make clean_o

robot.o: robot.c robot.h
	gcc -g -Wall -c robot.c

map.o: map.c map.h robot.h
	gcc -g -Wall -c map.c

queue.o: queue.c queue.h map.h
	gcc -g -Wall -c queue.c

display.o: display.c display.h map.h robot.h
	gcc -g -Wall -c display.c -lm

queue_informed_algo.o: queue_informed_algo.c queue_informed_algo.h map.h
	gcc -g -Wall -c queue_informed_algo.c


clean_o:
	rm -f *.o

clean:
	rm -f main *.o