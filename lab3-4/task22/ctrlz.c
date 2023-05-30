#include <stdio.h>
#include <signal.h>
#include <stdio.h>
#include <sched.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void handler(){
	puts(" - signal Ctrl+Z received");
	signal(SIGTSTP, SIG_DFL); 
}

int main(){
	int pid, ppid;
	pid = getpid();
	ppid = getppid();
	printf("Current pid = %d and ppid = %d\n", pid, ppid);
	signal(SIGTSTP, handler);
	while(1);
	return 0;
}
