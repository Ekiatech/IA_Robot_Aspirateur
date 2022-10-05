#include "greedy_best_first_search_depth.h"

struct node* get_best_node(struct queue* q){
    struct node* best_node = q->first;
    int max = best_node->room->heuristic;
    struct node* temp = q->first;
    while (temp->next != NULL){
        if (max < temp->next->room->heuristic){
            max = temp->next->room->heuristic;
            best_node = temp->next;
        }
        temp = temp->next;
    }
    return best_node;
}

int is_neighbor_from(struct node* node_from, struct node* node){
    for (int i = 0; i < node_from->room->nbr_neighbors; i++){
        if (node_from->room->neighbors[i] == node->room)
            return 1;
    }
    return 0;
}

int not_depth_reached(struct queue* q_path, int depth, struct node* initial_node){
    if (q_path->first == NULL)
        return -1;
    
    struct node* node = q_path->last;
    int n = 1;
    while (is_neighbor_from(initial_node, node) == 0){
        node = node->add_by_this_node;
        n++;
    }
    if (n == depth)
        return 1;
    return -1;
}

void push_the_good_path(struct queue* q_path, struct node* initial_node, struct node* the_good_path[], int depth){
    struct node* n = q_path->last;
    int i = depth;
    while (i > 0){
        the_good_path[i-1] = n;
        remove_from_queue(q_path, n);
        n = n->add_by_this_node;
        i--;
    }
}

void push_nodes_in_waiting_queue(struct Map* map, struct queue* q_waiting, struct node* best_node){
    for (int a = 0; a < best_node->room->nbr_neighbors; a++){
        if (best_node->room->neighbors[a] != best_node->add_by_this_node->room){
            struct node* temp_node = create_node(map, best_node->room->neighbors[a]->position[0], 
            best_node->room->neighbors[a]->position[1], best_node);
            push(q_waiting, temp_node);
        }
    }
}

struct node** greedy_best_first_search_depth(struct Map* map, int depth){
    struct queue* q_waiting = create_empty_queue_informed();
    struct queue* q_path = create_empty_queue_informed();
    heuristic(map);

    int i = map->robot->position[0];
    int j = map->robot->position[1];
    struct node* initial_node = create_node(map, i, j, NULL);
    
    for (int a = 0; a < initial_node->room->nbr_neighbors; a++){
        struct node* temp_node = create_node(map, initial_node->room->neighbors[a]->position[0], 
        initial_node->room->neighbors[a]->position[1], initial_node);
        push(q_waiting, temp_node);
    }

    int the_good_path_reached = -1;
    while (the_good_path_reached == -1){
        struct node* best_node = get_best_node(q_waiting);
        best_node = remove_from_queue(q_waiting, best_node);

        push(q_path, best_node);
        push_nodes_in_waiting_queue(map, q_waiting, best_node);

        the_good_path_reached = not_depth_reached(q_path, depth, initial_node);
    }
    
    struct node** the_good_path = malloc(depth * sizeof(struct node));

    push_the_good_path(q_path, initial_node, the_good_path, depth);

    free(initial_node);
    free_queue_informed(q_waiting);
    free_queue_informed(q_path);

    return the_good_path;
}

Action which_side_to_move(int i, int j, struct Room* to){
    int new_i = to->position[0];
    int new_j = to->position[1];

    if (new_i == i - 1 && new_j == j)
        return UP;
    else if (new_i == i + 1 && new_j == j)
        return DOWN;
    else if (new_i == i && new_j == j - 1)
        return LEFT;
   return RIGHT;
}

int follow_path_greedy(struct Map* map, struct node* path[], int depth, int limit){
    int i = map->robot->position[0];
    int j = map->robot->position[1];

    int n = 0;
    int actions = 0;
    while (n < depth){
        display_map(map);
        struct node* node = path[n];
        Action action = which_side_to_move(i, j, node->room);
        robot_action(map, action);
        actions++;
        if (actions == limit)
            return 1;

        if (node->room->objects[0] == JEWEL || node->room->objects[1] == JEWEL){
            robot_action(map, PICK_UP);
            actions++;
        }
        if (actions == limit)
            return 1;

        if (node->room->objects[0] == DUST || node->room->objects[1] == DUST){
            robot_action(map, CLEAN);
            actions++;
        }
        if (actions == limit)
            return 1;

        gen_random_object(map);

        i = node->room->position[0];
        j = node->room->position[1];
        n++;
    }
    return 0;
}

void free_node_tab(struct node** path, int depth){
    for (int i = 0; i < depth; i++){
        path[i]->previous = NULL;
        path[i]->next = NULL;
        free(path[i]);
    }
}

int best_gbfs_nb_actions(struct Map* map, int depth){
    int stats_sums[MAX_ACTIONS];
    for (int i = 0; i < MAX_ACTIONS; i++)
        stats_sums[i] = 0;

    int current_points = 0;
    for (int i = 1; i <= MAX_ACTIONS; i++) {
        for (int j = 0; j < NB_LEARNING_LOOPS; j++) {
            current_points = map->robot->points;
            struct node** path = greedy_best_first_search_depth(map, depth);
            follow_path_greedy(map, path, depth, i);
            free_node_tab(path, depth);
            stats_sums[i - 1] += (map->robot->points - current_points);
        }
    }

    int max = stats_sums[0];
    int best_nb_actions = 1;
    for (int i = 1; i < MAX_ACTIONS; i++) {
        if (stats_sums[i] > max) {
            max = stats_sums[i];
            best_nb_actions = i + 1;
        }
    }

    return best_nb_actions;
}