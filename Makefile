all: robot.o map.o queue.o algorithms.o display.o queue_informed_algo.o greedy_best_first_search_depth.o
	gcc -o main main.c robot.o map.o queue.o algorithms.o queue_informed_algo.o greedy_best_first_search_depth.o display.o -pthread -lm -g

robot.o: robot.c robot.h
	gcc -g -Wall -c robot.c

map.o: map.c map.h robot.h
	gcc -g -Wall -c map.c

queue.o: queue.c queue.h map.h
	gcc -g -Wall -c queue.c

algorithms.o: algorithms.c queue.h map.h
	gcc -g -Wall -c algorithms.c

display.o: display.c display.h map.h robot.h
	gcc -g -Wall -c display.c -lm

queue_informed_algo.o: queue_informed_algo.c queue_informed_algo.h map.h
	gcc -g -Wall -c queue_informed_algo.c

greedy_best_first_search_depth.o: greedy_best_first_search_depth.c greedy_best_first_search_depth.h robot.h
	gcc -g -Wall -c greedy_best_first_search_depth.c

clean_o:
	rm -f *.o

clean:
	rm -f main *.o