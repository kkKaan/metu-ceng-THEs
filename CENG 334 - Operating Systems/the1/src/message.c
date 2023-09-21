#include "message.h"

int send_message(int socket, om* message) {
    return write(socket, message, sizeof(om));
}

int send_object_data(int socket, int count, od* objects) {
    return write(socket, objects, count * sizeof(od));
}

int read_data(int socket, im* message) {
    return read(socket, message, sizeof(im));
}

