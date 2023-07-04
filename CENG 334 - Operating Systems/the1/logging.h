#ifndef HW1_LOGGING_H
#define HW1_LOGGING_H

#include "message.h"
#include <stdio.h>

typedef struct incoming_message_print {
    pid_t pid; // Process id of the process that the message is received from.
    im *m; // Pointer to the message itself
} imp;

typedef struct outgoing_message_print {
    pid_t pid; // Process id of the process that the message is sent to.
    om *m; // Pointer to the message itself
} omp;

typedef struct obstacle_data {
    coordinate position; // Position of the obstacle
    int remaining_durability; // Remaining durability after the explosion
} obsd;

void print_output(imp *in, omp *out, obsd *obstacle, od* objects);
#endif //HW1_LOGGING_H
