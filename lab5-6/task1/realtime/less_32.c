#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>


void handler(int signo, siginfo_t* info, void* context) {
    static int i = 0;
    printf("Received signal %d\n", signo);
    if (signo == 2 || signo == 9){
        i++;
        if (i == 2){
            signal(signo, SIG_DFL);
        }
    }
}

int main() {
    struct sigaction sa;
    union sigval value;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;

    // Установка обработчика для сигналов < 32
    for (int i = 1; i <= 31; i++) {
        sigaction(i, &sa, NULL);
    }

    if (fork() == 0){

        // Отправка сигналов
        for (int i = 1; i <= 8; i++) {
            value.sival_int = i;
            usleep(1000);
            sigqueue(getppid(), i, value);
        }

        for (int i = 8; i >= 1; i--) {
            value.sival_int = i;
            usleep(1000);
            sigqueue(getppid(), i, value);
        }

        sleep(3);
    }

    for (;;)
    {
        pause();
    }

    return 0;
}
