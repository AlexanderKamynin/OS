#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int signal) {
    printf("Signal %d received by process %d\n", signal, getpid());
}


int main()
{
    int pid, ppid;
    signal(SIGTERM, handler);
    pid = getpid();
    ppid = getppid();
    printf("\n Son parameters was: pid=%i, ppid=%i\n", pid, ppid);

    while (1) {
        sleep(1);
    }
    return 0;
}