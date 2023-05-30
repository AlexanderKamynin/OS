#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>


#define SIGNALS_COUNT 4


void signal_handler(int signo, siginfo_t* info, void* context){
    printf("Received signal %d with data %d\n", signo, info->si_value.sival_int);
}


int main(){
    int pid = getpid();
    struct sigaction action;
    union sigval value;

    // настройка обработчика сигнала
    action.sa_sigaction = signal_handler;
    action.sa_flags = SA_SIGINFO;
    sigemptyset(&action.sa_mask);

    for (int i = SIGRTMIN; i < SIGRTMAX; i++){
        sigaddset(&action.sa_mask, i);
    }

    for (int i = 1; i <= SIGNALS_COUNT; i++){
        //sigaction(SIGINT + i, &action, NULL);
        sigaction(SIGRTMIN + i, &action, NULL);
    }

    if (fork() == 0){
        // отправка сигналов
        for (int i = 1; i <= SIGNALS_COUNT; i++){
            value.sival_int = i;
            // printf("Send not real time signal %d with data %d\n", SIGINT + i, value.sival_int);
            // if (sigqueue(pid, SIGINT + i, value) != 0){
            //     perror("sigqueue");
            //     exit(-1);
            // }

            printf("Send real time signal %d with data %d\n", SIGRTMIN + 1, value.sival_int);
            if (sigqueue(pid, SIGRTMIN + 1, value) != 0){
                perror("sigqueue");
                exit(-1);
            }
        }

        for (int i = SIGNALS_COUNT; i >= 1; i--){
            value.sival_int = i;
            // printf("Send not real time signal %d with data %d\n", SIGINT + i, value.sival_int);
            // if (sigqueue(pid, SIGINT + i, value) != 0){
            //     perror("sigqueue");
            //     exit(-1);
            // }

            printf("Send real time signal %d with data %d\n", SIGRTMIN + 1, value.sival_int);
            if (sigqueue(pid, SIGRTMIN + 1, value) != 0){
                perror("sigqueue");
                exit(-1);
            }
        }


        sleep(3);
        return 0;
    }

    for (;;)
    {
        pause();
    }

    return 0;
}