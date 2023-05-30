#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


void on_signal(int sig) {
    printf("Signal %d received\n", sig);
    exit(0);
}

int main() {
    printf("Parent process ID: %d\n", getpid());
    signal(SIGINT, on_signal);

    int pid = fork();
    
    if (pid == -1) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        printf("Child process ID: %d\n", getpid());
    } else {
        printf("Parent process ID: %d, child process ID: %d\n", getpid(), pid);
    }
    
    while (1) {
        sleep(1);
    }
    
    return 0;
}