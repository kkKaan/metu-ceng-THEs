#ifndef HW1_MESSAGE_H
#define HW1_MESSAGE_H

#include <unistd.h>
#include <sys/socket.h>
#include <fcntl.h>

#define PIPE(fd) socketpair(AF_UNIX, SOCK_STREAM, PF_UNIX, fd)

typedef struct coordinate{
    unsigned int x;
    unsigned int y;
} coordinate;

typedef enum incoming_message_type {
    BOMBER_START,
    BOMBER_SEE,
    BOMBER_MOVE,
    BOMBER_PLANT,
    BOMB_EXPLODE,
} imt;

typedef struct bomb_data {
    long interval;
    unsigned int radius;
} bd;

typedef union incoming_message_data {
    coordinate target_position;
    bd bomb_info;
} imd;


typedef struct incoming_message {
    imt type;
    imd data;
} im;

typedef enum outgoing_message_type {
    BOMBER_LOCATION,
    BOMBER_VISION,
    BOMBER_PLANT_RESULT,
    BOMBER_DIE,
    BOMBER_WIN,
} omt;

typedef enum object_type {
    BOMBER,
    BOMB,
    OBSTACLE
} ot;

typedef struct object_data {
    coordinate position;
    ot type;
} od;

typedef union outgoing_message_data {
    unsigned int object_count;
    coordinate new_position;
    int planted;
} omd;


typedef struct outgoing_message {
    omt type;
    omd data;
} om;

int send_message(int socket, om* message);

// Objects should be one continuous array
int send_object_data(int socket, int count, od* objects);

// Do not forget to check if there is data to be read on this socket beforehand.
int read_data(int socket, im* message);

#endif //HW1_MESSAGE_H