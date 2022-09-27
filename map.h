#ifndef MAP_H_
#define MAP_H_

/************ ENUMs ************/

struct Robot;

typedef enum {
    NOTHING = 0,
    DUST = 1,
    JEWEL = 2
} Objects;

/************ STRUCTs ************/

struct Room {
    int position[2];
    Objects objects[2];
};

struct Map {
    int side_size;
    struct Room ** rooms;
    struct Robot * robot;
};

/************ FCTs ************/

struct Room create_empty_room(int coordinates[2]);

struct Map * create_empty_map(int size, struct Robot * robot);

void init_map(struct Map * map);

void free_map(struct Map * map);

int choose_dust_or_jewel();

int choose_object();

int int_in_array(int value, int array[], int size);

int place_object(struct Map * map, int x_room, int y_room, int object, int object_has_been_added);

#endif // MAP_H_