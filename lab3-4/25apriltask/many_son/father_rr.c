#include <stdio.h>
#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>

#define SON_COUNT 18
#define CURRENT_POLITICS SCHED_RR


int main () {
    struct sched_param shdprm;
    int pid,ppid, status;
    int n = 60;
    char *arr[SON_COUNT] = {"son1", "son2", "son3", "son4", "son5", "son6",
                            "son7", "son8", "son9", "son10", "son11", "son12",
                            "son13", "son14", "son15", "son16", "son17", "son18"};
    int pid_son[SON_COUNT];
    int prior[SON_COUNT] = {10, 20, 10, 20,
                            10, 20, 10, 20,
                            10, 20, 10, 20,
                            10, 20, 10, 20,
                            10, 20};


    pid = getpid();
    ppid = getppid();
    printf("FATHER PARAMS: pid=%i ppid=%i\n", pid,ppid);
    shdprm.sched_priority = 1;

    if (sched_setscheduler (0, CURRENT_POLITICS, &shdprm) == -1)
    {
        perror ("sched error");
    }

    for (int i=SON_COUNT - 1; i >= 0; i--)
    {
        if((pid_son[i]=fork()) == 0)
        {
            shdprm.sched_priority = prior[i];
            if (sched_setscheduler (pid_son[i], CURRENT_POLITICS, &shdprm) == -1)
                perror ("set sched error");
            execl(arr[i], arr[i], NULL);
        }
    }
    
    return 0;
}