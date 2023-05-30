#include <stdio.h>
#include <signal.h>
#include <stdio.h>
#include <sched.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static int count = 5;

void handler()
{
    static int i = 0;
    printf(" - signal Ctrl+C received, i = %d\n", i);
    i++;
    if (i == count) //количество срабатываний текущего обработчика
        signal(SIGINT, SIG_DFL); //восстановление стандартного обработчика
}

int main(){
	int pid, ppid;
	pid = getpid();
	ppid = getppid();
	printf("Current pid = %d and ppid = %d\n", pid, ppid);
	signal(SIGINT, handler);
	while(1){
        // inf
    }
	return 0;
}