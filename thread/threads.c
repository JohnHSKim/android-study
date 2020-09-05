#include <stdio.h>
#include <pthread.h>

// pthread has to return void pointer
// and takes a void pointer as an argument
void* myturn( void * arg) {
    for (int i=0; i<10; i++)
    {
        sleep(1);
        printf("My turn!\n");
    }

    return NULL;
}

void yourturn() {
    for (int i=0; i<3; i++)
    {
        sleep(2);
        printf("Your turn!\n");
    }
}

int main() {
    pthread_t newthread;
    pthread_create(&newthread, NULL, myturn, NULL);
    yourturn();

    return 0;
}