#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#include "display.h"
#include "robot.h"
#include "map.h"
#include "queue.h"

#define DEFAULT_MAP_SIDE_SIZE 5
#define DEFAULT_ROBOT_ENERGY 20000

void bfs(struct Map * map) {
    struct Queue * q = create_empty_queue(map);
    int n_coordinates[2] = { map->robot->position[0], map->robot->position[1] };
    struct Node * n = create_empty_node(map, n_coordinates);
    int selected_path[map->side_size * map->side_size][2];

    push_queue(q, n);
    // display_map_and_queue(map, q);
    int object_has_been_found = 0;
    int first_object = 0, second_object = 0;
    int goal_position[2] = {0, 0};
    while (!queue_is_empty(q) && !object_has_been_found) {
        n = pop_queue(q, map);
        first_object = n->room->objects[0];
        second_object = n->room->objects[1];
        if ((first_object != 0) || (second_object != 0)) {
            object_has_been_found = 1;
            goal_position[0] = n->room->position[0];
            goal_position[1] = n->room->position[1];
        }
        // display_map_and_queue(map, q);
    }

    if (q->current_size != 0) {
        int current_path;
        for (int j = 0; j < n->length_path; j++) {
            selected_path[j][0] = n->path[j][0];
            selected_path[j][1] = n->path[j][1];
        }
        selected_path[n->length_path][0] = n->room->position[0];
        selected_path[n->length_path][1] = n->room->position[1];
        printf("Path = ");
        for (int j = 0; j < n->length_path + 1; j++) {
            printf("%d:%d ", selected_path[j][0], selected_path[j][1]);
        }
        printf("\n");
        printf("Goal = %d:%d - ", goal_position[0], goal_position[1]);
        printf("Objects : %d, %d\n", first_object, second_object);

        int objects[2] = { first_object, second_object };
        Action action;
        int x_robot = map->robot->position[0], y_robot = map->robot->position[1];
        int x_goal = selected_path[n->length_path][0], y_goal = selected_path[n->length_path][1];
        int x_next, y_next;
        int step_counter = 0;
        printf("x_goal: %d, y_goal: %d\n", x_goal, y_goal);
        while (!((x_robot == x_goal) && (y_robot == y_goal)) && (action != STOP)) {
            step_counter++;
            x_next = selected_path[step_counter][0];
            y_next = selected_path[step_counter][1];
            if ((x_robot - x_next) > 0)
                action = UP;
            else if ((x_robot - x_next) < 0)
                action = DOWN;
            else if ((y_robot - y_next) > 0)
                action = LEFT;
            else if ((y_robot - y_next) < 0)
                action = RIGHT;
            else
                action = STOP;
            x_robot = x_next;
            y_robot = y_next;
            robot_action(map, action);
        }
        if ((objects[0] == 2) || (objects[2] == 2))
            action = PICK_UP;
        else
            action = CLEAN;
        robot_action(map, action);

        display_map_and_queue(map, q);
    }

    free_node(n);
    free_queue(q);
}




void * robot_loop(struct Map * map) {
    time_t start = time(NULL);
    time_t seconds = 5;
    time_t endwait = start + seconds;

    while (start < endwait) {
        bfs(map);
        start = time(NULL);
    }
    printf("Robot : %ld seconds passed.\n\n", seconds);

    // GET INFO -> BELIEF + GREEDY SEARCH (+ HEURISTIQUE) + BREADTH-FIRST-SEARCH
    // UPDATE STATE -> DESIRE + CHOISIR CHEMIN OPTIMAL
    // CHOOSE ACTION -> INTENTIONS
    // EXECUTE ACTION

    // for (int i = 0; i < 2; i++) {
    //     bfs(map);
    // }
}

void * map_loop(struct Map * map) {
    time_t start = time(NULL);
    time_t seconds = 5;
    time_t endwait = start + seconds;

    while (start < endwait) {
        gen_random_object(map);
        display_map(map);
        sleep(1);
        start = time(NULL);
    }

    printf("\nMap : %ld seconds passed.\n\n", seconds);
}




int main(int argc, char **argv) {
    int map_side_size = DEFAULT_MAP_SIDE_SIZE;
    if (argc >= 2)
        map_side_size = atoi(argv[1]);
    int robot_points = 0;
    int robot_energy = DEFAULT_ROBOT_ENERGY;
    if (argc >= 3)
        robot_energy = atoi(argv[2]);
    time_t t;
    srand((unsigned) time(&t));
    int robot_coordinates[2] = {rand() % map_side_size, rand() % map_side_size};

    struct Robot * robot = create_robot(robot_coordinates, robot_energy);
    struct Map * map = create_empty_map(map_side_size, robot);
    init_map(map);

    pthread_t robot_t, map_t;
    pthread_create(&robot_t, NULL, (void * (*)(void *)) robot_loop, (void *) map);
    pthread_create(&map_t, NULL, (void * (*)(void *)) map_loop, (void *) map);

    pthread_join(robot_t, NULL);
    pthread_join(map_t, NULL);
    
    free_map(map);

    return 0;
}