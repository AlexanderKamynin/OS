#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>


static void sigHandler(int sig) 
{
    printf("SIGTRAP catchedn\n");
    static int count = 0;
    if (count++ == 3){
        // востанавливаем старую диспозицию
        printf("set default function for SIGTRAP\n");
        signal(sig,SIG_DFL);
    }
}

int main() 
{
    printf("\nFather started: pid = %i,ppid = %i\n",getpid(),getppid());

    signal(SIGTSTP,sigHandler);
    signal(SIGINT,SIG_IGN);

    int forkRes = fork();
    if(forkRes == 0) 
    {
        // программа-потомок
        printf("\nSon started: pid = %i,ppid = %i\n",getpid(),getppid());
        return 0;
    }
    // программа-родитель
    wait(NULL);
    // ждем сигналов
    for(;;)
    {
        pause();
    }
    return 0;
}