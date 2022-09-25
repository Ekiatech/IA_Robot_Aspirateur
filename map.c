#include <stdio.h>
#include <stdlib.h>

#include "map.h"

struct Room create_empty_room(int coordinates[2]) {
    struct Room room;
    room.position[0] = coordinates[0];
    room.position[1] = coordinates[1];
    room.objects[0] = 0;
    room.objects[1] = 0;
    return room;
}

struct Map * create_empty_map(int size, struct Robot * robot) {
    struct Map * map = malloc(sizeof(struct Map));
    map->side_size = size;
    map->robot = robot;
    map->rooms = (struct Room **) malloc(size * sizeof(struct Room *));
    for (int i = 0; i < size; i++) {
        map->rooms[i] = (struct Room *) malloc(size * sizeof(struct Room));
        for (int j = 0; j < size; j++)
        {
            int room_position[2] = {i, j};
            map->rooms[i][j] = create_empty_room(room_position);
        }
    }
    return map;
}

void free_map(struct Map * map) {
    free(map->robot);
    for (int i = 0; i < map->side_size; i++) {
        free(map->rooms[i]);
    }
    free(map->rooms);
    free(map);
}

int choose_object() {
    int random = rand() % 100;
    if (random <= 50)
        return 0;
    else if ((random > 50) && (random <= 90))
        return 1;
    return 2;    
}

int int_in_array(int value, int array[], int size) {
    for (int i = 0; i < size; i++) {
        if (array[i] == value)
            return 1;
    }
    return 0;
}

void gen_random_object(struct Map * map) {
    int gen_object = choose_object();
    int object_has_been_added = 0;
    int total_map_size = map->side_size * map->side_size;
    int tested_rooms = 0;
    int rooms_positions[total_map_size];
    for (int i = 0; i < total_map_size; i++)
        rooms_positions[i] = i; 

    do {
        int random_x = rand() % map->side_size;
        int random_y = rand() % map->side_size;

        int room_number = random_x * map->side_size + random_y;
        int room_not_tested_yet = int_in_array(room_number, rooms_positions, total_map_size);

        if (room_not_tested_yet == 1) {
            rooms_positions[room_number] = -1;
            tested_rooms += 1;

            int first_object = map->rooms[random_y][random_x].objects[0];
            int second_object = map->rooms[random_y][random_x].objects[1];

            if ((first_object == 0) && (second_object != gen_object)) {
                map->rooms[random_y][random_x].objects[0] = gen_object;
                object_has_been_added = 1;
            }
            else if ((second_object == 0) && (first_object != gen_object)) {
                map->rooms[random_y][random_x].objects[1] = gen_object;
                object_has_been_added = 1;
            }
        }
    }
    while ((object_has_been_added == 0) && (tested_rooms != total_map_size));
}