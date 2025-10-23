#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include "monte_carlo.h"

int main(int argc, char *argv[]) {
    int rounds, max_threads_count;
    if (argc != 5) {
        printf("Usage: %s -r <rounds> -t <threads>\n", argv[0]);
        return 1;
    }
    
    if (strcmp(argv[1], "-r") == 0 && strcmp(argv[3], "-t") == 0) {
        rounds = atoi(argv[2]);
        max_threads_count = atoi(argv[4]);
    } 
    else if (strcmp(argv[1], "-t") == 0 && strcmp(argv[3], "-r") == 0) {
        rounds = atoi(argv[4]);
        max_threads_count = atoi(argv[2]);
    } 
    else {
        printf("Usage: %s -r <rounds> -t <threads>\n", argv[0]);
        return 1;
    }

    if (rounds <= 0 || max_threads_count <= 0) {
        fprintf(stderr, "Error: rounds and threads must be positive\n");
        exit(1);
    }

    if (max_threads_count > rounds) {
        max_threads_count = rounds;
    }

    pthread_t threads[max_threads_count];
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    int min_rounds_count = rounds / max_threads_count;
    int remains = rounds % max_threads_count;

    for (int i = 0; i < max_threads_count; i++) {
        Data *data = malloc(sizeof(Data));
        data->thread_id = i;
        data->rounds = min_rounds_count + (i < remains ? 1 : 0);
        data->hit = 0;

        if (pthread_create(&threads[i], NULL, Process_rounds, data) != 0) {
            perror("Failed to create thread");
            exit(1);
        }
    }

    for (int i = 0; i < max_threads_count; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    double probability = (double)result / rounds;
    printf("\n=== RESULTS ===\n");
    printf("Rounds: %d, Threads: %d\n", rounds, max_threads_count);
    printf("Successes: %d/%d = %.6f\n", result, rounds, probability);
    printf("Time: %.6f seconds\n", time_taken);

    pthread_mutex_destroy(&m);
    return 0;
}