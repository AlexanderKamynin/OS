#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <sched.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#define NUM_THREADS 2
#define count 5
pthread_t t1, t2;


void handler()
{
    printf("get signal by thread1\n");
    signal(SIGINT, SIG_DFL);
}

void* thread1(void* arg) 
{
    int i;
    printf("Thread [%d] started, pid=%d ppid=%d, \n", 1, getpid(), getppid());
    signal(SIGINT, handler);
    while (1) {
        sleep(1);

        printf("Send signal to pthread 1\n");
        pthread_kill(t1, SIGINT);

        sleep(2);
        printf("Send signal to thread1 again\n");
        pthread_kill(t1, SIGINT);
        //printf("[%d] thread: no signal\n", 1);
    }
}

void* thread2(void* arg) 
{
    int i;
    printf("Thread [%d] started, pid=%d ppid=%d, \n", 2, getpid(), getppid());
    signal(SIGINT, SIG_IGN);
    while (1) {
        sleep(1);
        
        printf("Send signal to pthread 2\n");
        pthread_kill(t2, SIGINT);
        sleep(5);
        //printf("[%d] thread: no signal\n", 2);
    }
}


int main() 
{
    printf("Process with pid %d start\n", getpid());
    pthread_create(&t1, NULL, thread1, NULL);
    sleep(1);
    pthread_create(&t2, NULL, thread2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}