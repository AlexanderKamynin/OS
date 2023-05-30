#include <signal.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <time.h>

typedef struct Data Data;
const int COUNT_THREADS = 18;


void printPSTable()
{
    char command[80];
    sprintf(command, "ps -T -p %d -o s,pid,ppid,spid,tgid,thcount,cls,pri,ni,stat,cmd,rtprio > out.txt", getpid());
    system(command);
}


void *processing(void *arg) {
    struct timespec start, end;

    clock_gettime(CLOCK_REALTIME, &start);

    int *id = (int *) arg;
    int tid = syscall(SYS_gettid);
    int pid = getpid();
    int counter = 0;

    printPSTable();

    printf("\nThread_%d with tid = %d and pid = %d is started\n", *id, tid, pid);
    for (int i = 0; i < 100000000; i++) {
        counter = counter * i % 10;
    }

    clock_gettime(CLOCK_REALTIME, &end);
    double process_time = end.tv_sec - start.tv_sec + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("\nThread_%d with id = %d and pid = %d is completed\n", *id, tid, pid);
}


int read_file(int *priorities, int *policies)
{
    FILE *file = fopen("input.txt", "r");

    char line[COUNT_THREADS * 2];
    if(file)
    {
        int i = 0;
        while(fgets(line, COUNT_THREADS * 2, file) != NULL)
        {
            if(i < COUNT_THREADS)
            {
                priorities[i] = atoi(line);
            } else if(i < COUNT_THREADS * 2) {
                policies[i - COUNT_THREADS] = atoi(line);
            }

            i++;
        }
    }
    else
        return -1;

    fclose(file);
    return 0;
}


int main()
{
    pthread_t threads[COUNT_THREADS];
    pthread_attr_t thread_attributes[COUNT_THREADS];
    int priorities[COUNT_THREADS], policies[COUNT_THREADS];

    int all_id[COUNT_THREADS];
    for(int i = 0; i < COUNT_THREADS; i++)
        all_id[i] = i + 1;

    int policy;
    struct sched_param schprm;

    for(int i = 0; i < COUNT_THREADS; i++) {
        pthread_attr_init(&thread_attributes[i]);
    }

    read_file(priorities, policies);

    for(int i = 0; i < COUNT_THREADS; i++)
    {
        pthread_attr_setschedpolicy(&thread_attributes[i], policies[i]);
        schprm.sched_priority = priorities[i];
        pthread_attr_setschedparam(&thread_attributes[i], &schprm);
    }

    for(int i = 0; i < COUNT_THREADS; i++){
        pthread_attr_setinheritsched(&thread_attributes[i], PTHREAD_EXPLICIT_SCHED);
    }

    for(int i = 0; i < COUNT_THREADS; i++)
    {
        pthread_attr_getschedparam(&thread_attributes[i], &schprm);
        pthread_attr_getschedpolicy(&thread_attributes[i], &policy);
        printf("Поток %d, его приоритет = %d\n", i + 1, schprm.sched_priority);
    }

    switch (policy) {
        case SCHED_FIFO: // 1
            printf ("SCHED_FIFO\n");
            break;
        case SCHED_RR: // 2
            printf ("SCHED_RR\n");
            break;
        case SCHED_OTHER: // 0
            printf ("SCHED_OTHER\n");
            break;
        case -1:
            perror ("SCHED_GETSCHEDULER");
            break;
        default:
            printf ("Неизвестная политика планирования\n");
    }

    for(int i = 0; i < COUNT_THREADS; i++)
    {
        if(pthread_create(&threads[i], &thread_attributes[i], processing, &all_id[i]))
            perror("Ошибка при создании потока");
    }

    for(int i = 0; i < COUNT_THREADS; i++)
        pthread_join(threads[i], NULL);

    for(int i = 0; i < COUNT_THREADS; i++)
        pthread_attr_destroy(&thread_attributes[i]);

    return 0;
}