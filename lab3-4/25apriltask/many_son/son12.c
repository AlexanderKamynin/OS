#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <math.h>


int main()
{
    struct sched_param shdprm; // Значения параметров планирования
    char* son_name = "SON12";
    int son_number = 12;
    int i, pid,ppid;
    pid=getpid();
    ppid=getppid();
    printf("CREATE %s: pid=%i ppid=%i", son_name, pid,ppid);

    printf ("\tполитика планирования:");
    switch (sched_getscheduler (0)) {
    case SCHED_FIFO:
        printf ("SCHED_FIFO\n");
        break;
    case SCHED_RR:
        printf ("SCHED_RR\n");
        break;
    case SCHED_OTHER:
        printf ("SCHED_OTHER\n");
        break;
    case -1:
        perror ("SCHED_GETSCHEDULER");
        break;
    default:
        printf ("Неизвестная политика планирования\n");
    }

    double res = 0;
    for (int i = 0; i< 100000; i++)
    {
        res = sqrt(i * (res + 1));
        if (i % 1000 == 0)
            printf("%d", son_number);
    }

    if (sched_getparam (0, &shdprm) == 0)
        printf ("\n\t%s END: приоритет процесса: %d\n", son_name, shdprm.sched_priority);
    else
        perror ("SCHED_GETPARAM");

    return 0;
}