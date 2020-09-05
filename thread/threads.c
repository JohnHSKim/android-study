#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS 4

void *print_message ( void *arg ) {
    printf("Start %d : Thread number %lu\n", (int) arg, pthread_self());
    pthread_exit(0);
}

// pthread has to return void pointer
// and takes a void pointer as an argument
void* myturn( void * arg) {
    for (int i=0; i<8; i++)
    {
        sleep(1);
        printf("My turn! %d\n", i);
    }

    return NULL;
}

void yourturn() {
    for (int i=0; i<3; i++)
    {
        sleep(2);
        printf("Your turn! %d\n", i);
    }
}

int turn_example() {
    pthread_t newthread;
    
    if (pthread_create(&newthread, NULL, myturn, NULL) != 0)
    {
        printf("Error on pthread_create");
        return 0;
    }

    yourturn();

    // main thread and newthread will be in same group by pthread_join
    if (pthread_join(newthread, NULL) != 0)
    {
        printf("Error on pthread_join");
        return 0;
    }
}

int main() {
    // int ret = turn_example();
    pthread_t threads[NTHREADS];
    int ret;
    int status;

    for (int i=0; i < NTHREADS; i++) {
        ret = pthread_create(&threads[i], NULL, print_message, (void *) i);
        pthread_join( threads[i], (void **) &status);
        printf("Thread returns %d\n", status);
    }

    return 0;
}