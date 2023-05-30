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
#define count 3
pthread_t t1, t2;

void handler1(){
    static int i = 0;
    printf(" - signal Ctrl+C received by thread1, i = %d\n", i);
    i++;
    if (i == count) //количество срабатываний текущего обработчика
        signal(SIGINT, SIG_DFL); //восстановление стандартного обработчика
}

void handler2(){
    static int i = 0;
    printf(" - signal Ctrl+C received by thread2, i = %d\n", i);
    i++;
    if (i == count) //количество срабатываний текущего обработчика
        signal(SIGINT, SIG_DFL); //восстановление стандартного обработчика
}


void* thread1(void* arg) 
{
    int i;
    printf("Thread [%d] started\n", 1);
    //signal(SIGINT, handler1);
    while (1) {
        sleep(3);
        printf("[%d] thread: no signal\n", 1);
    }
}

void* thread2(void* arg) 
{
    int i;
    printf("Thread [%d] started\n", 2);
    signal(SIGINT, handler2);
    while (1) {
        sleep(3);
        printf("[%d] thread: no signal\n", 2);
    }
}


int main() 
{
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}