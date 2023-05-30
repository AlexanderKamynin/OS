#include <stdio.h>
#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>

void printPSTable()
{
    char command[80];
    sprintf(command, "ps -o uid,gid,ruid,pid,ppid,pgid,tty,vsz,stat,command,cmd,rtprio > out.txt");
    system(command);
}

int main() {
    struct sched_param shdprm; // значения параметров планирования
    int pid, ppid, status;
    int pids[5];
    int n = 60;
    char* sons[5] = {"son1", "son2", "son3", "son4", "son5"};
    int prior = 10;

    pid = getpid();
    ppid = getppid();
    printf("FATHER PARAMS: pid=%i ppid=%i\n", pid,ppid);
    shdprm.sched_priority = n;
    if (sched_setscheduler (0, SCHED_FIFO, &shdprm) == -1) {
        perror ("SCHED_SETSCHEDULER");
    }

    for (int i=0; i < 5; i++){
		if((pids[i]=fork()) == 0)
		{
		shdprm.sched_priority = prior;
        if (sched_setscheduler (pids[i], SCHED_FIFO, &shdprm) == -1)
                perror ("Ошибка при установке политики планирования");
        execl(sons[i], sons[i], NULL);
		}
    }

    printPSTable();

    for (int i=0; i < 5; i++){
        printf("Процесс с pid = %d завершен\n\n", wait(&status));
    }

    return 0;
}
