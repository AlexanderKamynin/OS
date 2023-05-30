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


void handler1()
{
    printf("get signal by thread1\n");
    //signal(SIGINT, SIG_DFL);
}

void handler2()
{
    printf("get signal by thread2\n");
}


void* thread1(void* arg) 
{
    int i;
    printf("Thread [%d] started, pid=%d ppid=%d, \n", 1, getpid(), getppid());
    signal(SIGINT, handler1);
    while (1) {
        sleep(1);
    }
}

void* thread2(void* arg) 
{
    int i;
    printf("Thread [%d] started, pid=%d ppid=%d, \n", 2, getpid(), getppid());
    signal(SIGINT, handler2);
    //signal(SIGINT, SIG_IGN);
    while (1) {
        sleep(1);
    }
}


int main() 
{
    printf("Process with pid %d start\n", getpid());

    pthread_create(&t1, NULL, thread1, NULL);
    sleep(1);
    pthread_create(&t2, NULL, thread2, NULL);
    sleep(1);
    
    // pthread_create(&t2, NULL, thread2, NULL);
    // sleep(1);
    // pthread_create(&t1, NULL, thread1, NULL);

    kill(getpid(), SIGINT);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}