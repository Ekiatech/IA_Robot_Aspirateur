#include <stdio.h>
#include <stdlib.h>

#include "algorithms.h"
#include "robot.h"
#include "display.h"

int ACTIONS_COUNTER = 0;

/************ BFS ************/

int select_action_move(int line_robot, int column_robot, int line_next, int column_next) {
    Action action;
    if ((line_robot - line_next) > 0)
        action = UP;
    else if ((line_robot - line_next) < 0)
        action = DOWN;
    else if ((column_robot - column_next) > 0)
        action = LEFT;
    else if ((column_robot - column_next) < 0)
        action = RIGHT;
    else
        action = STOP;
    return action;
}

int select_action_collect(int objects[2]) {
    Action action = STOP;
    if ((objects[0] == 2) || (objects[1] == 2)) {
        action = PICK_UP;
        ACTIONS_COUNTER++;
    }
    else if ((objects[0] == 1) || (objects[1] == 1)) {
        action = CLEAN;
        ACTIONS_COUNTER++;
    }
    return action;
}


void follow_path(struct Map * map, int objects[2], int ** selected_path, int length_path, int nb_action_btw_update_map) {
    // INIT
    Action action = UP;
    int line_goal = selected_path[length_path][0], column_goal = selected_path[length_path][1];
    int line_robot = map->robot->position[0], column_robot = map->robot->position[1];
    int line_next, column_next, step_counter = 0;

    printf("line_goal : %d, column_goal : %d\n", line_goal, column_goal);
    // MOVE
    while (!((line_robot == line_goal) && 
            (column_robot == column_goal)) && 
            (action != STOP) && 
            (step_counter < nb_action_btw_update_map) && 
            (map->robot->energy > 0)) {
        step_counter++;
        line_next = selected_path[step_counter][0];
        column_next = selected_path[step_counter][1];
        action = select_action_move(line_robot, column_robot, line_next, column_next);        
        line_robot = line_next;
        column_robot = column_next;
        robot_action(map, action);
        ACTIONS_COUNTER++;
        if (ACTIONS_COUNTER % 2 == 0)
            gen_random_object(map);
    }
    if ((step_counter < nb_action_btw_update_map) && (map->robot->energy > 0)) {
        // PICK_UP or CLEAN
        action = select_action_collect(objects);
    }
    else
        action = STOP;
    printf("Action = %d\n", action);

    // DO Action
    robot_action(map, action);

    if (ACTIONS_COUNTER % 2 == 0)
        gen_random_object(map);
}

int ** retrieve_path(struct Node * n) {
    int ** selected_path;
    selected_path = malloc(sizeof(int *) * (n->length_path + 1));
    for (int i = 0; i < (n->length_path + 1); i++)
        selected_path[i] = malloc(sizeof(int *) * 2);

    for (int j = 0; j < n->length_path; j++) {
        selected_path[j][0] = n->path[j][0];
        selected_path[j][1] = n->path[j][1];
    }
    selected_path[n->length_path][0] = n->room->position[0];
    selected_path[n->length_path][1] = n->room->position[1];

    return selected_path;
}

void bfs(struct Map * map, int nb_action_btw_update_map) {
    // INIT
    struct Queue * q = create_empty_queue(map);
    int n_coordinates[2] = { map->robot->position[0], map->robot->position[1] };
    struct Node * n = create_empty_node(map, n_coordinates);
    int object_has_been_found = 0, objects[2] = {0, 0}, goal_position[2] = {0, 0};
    int ** selected_path;

    // 1 push + pop unitil empty queue
    push_queue(q, n);
    // display_map_and_queue(map, q);
    while (!queue_is_empty(q) && !object_has_been_found) {
        n = pop_queue(q, map);
        objects[0] = n->room->objects[0];
        objects[1] = n->room->objects[1];
        if ((objects[0] != 0) || (objects[1] != 0)) {
            object_has_been_found = 1;
            goal_position[0] = n->room->position[0];
            goal_position[1] = n->room->position[1];
        }
        // display_map_and_queue(map, q);
    }

    selected_path = retrieve_path(n);
    display_path_goal_objects(n, selected_path, objects, goal_position);
    follow_path(map, objects, (int **) selected_path, n->length_path, nb_action_btw_update_map);
    display_map_and_queue(map, q);

    // Free
    free_node(n);
    free_queue(q);
    // for (int i = 0; i < (n->length_path + 1); i++)
    //     free(selected_path[i]);
    // free(selected_path);
}

int best_nb_actions_bfs(struct Map * map) {
    int stats_sums[MAX_DISTANCE - 1];
    for (int i = 0; i < MAX_DISTANCE; i++)
        stats_sums[i] = 0;

    int current_points = 0;
    for (int i = 1; i <= MAX_DISTANCE; i++) {
        for (int j = 0; j < NB_LEARNING_LOOPS; j++) {
            current_points = map->robot->points;
            bfs(map, i);
            stats_sums[i - 1] += (map->robot->points - current_points);
        }
    }

    int max = 0, best_nb_actions = 1;
    for (int i = 0; i < MAX_DISTANCE; i++) {
        if (stats_sums[i] > max) {
            max = stats_sums[i];
            best_nb_actions = i + 1;
        }
    }

    return best_nb_actions;
}