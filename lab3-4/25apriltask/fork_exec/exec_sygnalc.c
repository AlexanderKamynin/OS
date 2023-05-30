#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int signal) {
    printf("Signal %d received by process %d\n", signal, getpid());
}

int main() {
    signal(SIGINT, handler);
    int pid = fork();

    if (pid == -1) {
        perror("fork");
    } else if (pid == 0) { // процесс-потомок
        printf("Child process %d executing...\n", getpid());
        execl("son1", "son1", NULL);
    } else { // процесс-родитель
        printf("Parent process %d executing...\n", getpid());
        sleep(2);
    }

    while (1) {
        sleep(1);
    }

    return 0;
}