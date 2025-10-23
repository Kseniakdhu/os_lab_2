#include <stdlib.h>
#include <time.h>
#include "monte_carlo.h"

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
int result = 0;

int Play(unsigned int *seed) {
    int cards[52];
    for (int j = 0; j < 52; j++) {
        cards[j] = j;
    }

    for (int i = 51; i > 0; i--) {
        int j = rand_r(seed) % (i + 1);
        int temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
    }

    return (cards[0] % 13) == (cards[1] % 13);
}

void *Process_rounds(void *arg) {
    Data *data = (Data *)arg;
    unsigned int seed = time(NULL) ^ data->thread_id;

    for (int i = 0; i < data->rounds; i++) {
        if (Play(&seed)) {
            data->hit++;
        }
    }

    pthread_mutex_lock(&m);
    result += data->hit;
    pthread_mutex_unlock(&m);

    free(data);
    return NULL;
}