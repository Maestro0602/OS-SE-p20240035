#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

// Volatile flag tells the compiler not to optimize away reads/writes to this variable
volatile sig_atomic_t keep_running = 1;

// Signal handler for SIGINT
void handle_sigint(int sig) {
    // Avoid using printf in signal handlers as it's not async-signal-safe, 
    // but writing a flag is perfectly safe.
    keep_running = 0;
}

// Worker thread function
void* worker_func(void* arg) {
    long thread_id = (long)arg;
    
    while (keep_running) {
        printf("[Thread %ld] Running...\n", thread_id);
        
        // sleep() returns the number of seconds left if interrupted by a signal.
        // We loop it to make sure it respects the shut-down flag instantly.
        unsigned int remaining = 1;
        while (remaining > 0 && keep_running) {
            remaining = sleep(remaining);
        }
    }
    
    printf("[Thread %ld] Exiting cleanly.\n", thread_id);
    pthread_exit(NULL);
}

int main() {
    pthread_t t1, t2;

    // Set up the SIGINT (Ctrl+C) signal handler
    struct sigaction sa;
    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

    printf("Spawning worker threads. Press Ctrl+C to gracefully shut down...\n\n");

    // Spawn two worker threads, passing 1 and 2 as IDs
    if (pthread_create(&t1, NULL, worker_func, (void*)1) != 0) {
        perror("Failed to create thread 1");
        return 1;
    }
    if (pthread_create(&t2, NULL, worker_func, (void*)2) != 0) {
        perror("Failed to create thread 2");
        return 1;
    }

    // Wait for both threads to finish up after keep_running becomes 0
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("\nAll threads cleanly exited. Goodbye.\n");
    return 0;
}
