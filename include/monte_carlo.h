#ifndef CARDS_H
#define CARDS_H

#include <pthread.h>

extern pthread_mutex_t m;
extern int result;

typedef struct Data {
    int thread_id;
    int rounds;
    int hit;
    unsigned int seed;
} Data;

int Play(unsigned int *seed);
void *Process_rounds(void *arg);

#endif