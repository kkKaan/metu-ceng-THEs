#include "logging.h"

void print_output(imp *in, omp *out, obsd *obstacle, od* objects) {

    if ( in ) {
        if ( !in->m ) {
            perror("You need to fill m pointer.");
            return;
        }
        printf("IN pid:%d mid:%d ", in->pid, in->m->type);
        switch (in->m->type) {
            case BOMBER_MOVE:
                printf("bomber move target:(%d, %d).\n", in->m->data.target_position.x, in->m->data.target_position.y);
                break;
            case BOMBER_SEE:
                printf("bomber see.\n");
                break;
            case BOMBER_START:
                printf("bomber start.\n");
                break;
            case BOMBER_PLANT:
                printf("bomber plant bomb interval:%ld radius:%d.\n", in->m->data.bomb_info.interval, in->m->data.bomb_info.radius);
                break;
            case BOMB_EXPLODE:
                printf("bomb explode.\n");
                break;
        }
    }
    else if ( out ) {
        if ( !out->m ) {
            perror("You need to fill m pointer.");
            return;
        }
        printf("OUT pid:%d mid:%d ", out->pid, out->m->type);
        switch (out->m->type) {
            case BOMBER_LOCATION:
                printf("bomber new location:(%d, %d).\n", out->m->data.new_position.x, out->m->data.new_position.y);
                break;
            case BOMBER_DIE:
                printf("bomber died.\n");
                break;
            case BOMBER_VISION:
                printf("bomber vision object count:%d.\n", out->m->data.object_count);
                for ( int i=0; i<out->m->data.object_count; i++) {
                    printf("object%d position:(%d,%d) type:%d.\n", i+1,
                           objects[i].position.x, objects[i].position.y,
                           objects[i].type);
                }
                break;
            case BOMBER_PLANT_RESULT:
                printf("bomber plant bomb result:%d.\n", out->m->data.planted);
                break;
            case BOMBER_WIN:
                printf("bomber wins.\n");
                break;
        }
    }
    else if ( obstacle ){
        printf("OBS position:(%d,%d) durability:%d.\n", obstacle->position.x, obstacle->position.y, obstacle->remaining_durability);
    }
    else {
        perror("One of the parameters needs to be filled.");
    }
    fflush(stderr);
}