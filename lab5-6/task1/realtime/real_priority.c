#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define NUM_SIGNALS 4

void handle_rt_signal(int sig, siginfo_t* info, void* context) 
{
    usleep(10000);
    printf("Handling real-time signal %d with value %d\n", sig, info->si_value.sival_int);
}

void handle_normal_signal(int sig) 
{
    printf("Handling normal signal %d\n", sig);
    if (sig == SIGINT || sig == 9)
    {
        signal(sig, SIG_DFL);
    }
}

int main() 
{
    struct sigaction sa_rt;
    union sigval value;
    sa_rt.sa_sigaction = handle_rt_signal;
    sa_rt.sa_flags = SA_SIGINFO;
    sigemptyset(&sa_rt.sa_mask);

    for (int i = SIGRTMIN; i <= SIGRTMAX; i++) 
    {
        sigaction(i, &sa_rt, NULL);
    }
    // Register normal signals
    for (int i = 1; i <= NUM_SIGNALS; i++) 
    {
        signal(i, handle_normal_signal);
    }
    // Send signals
    if (fork() == 0)
    {
        int order = 1;
        for (int i = 1; i <= NUM_SIGNALS; i++) 
        {
            value.sival_int = order;
            order++;
            printf("Sending normal signal %d\n", i);
            sigqueue(getppid(), i, value);
        }

        printf("Send in one order\n\n\n");
        order = 1;

        for (int i = SIGRTMIN; i < SIGRTMAX; i++) 
        {
            value.sival_int = order;
            order++;
            printf("Sending real-time signal %d\n", i);
            sigqueue(getppid(), i, value);
        }

        printf("Send in another order\n\n\n");
        order = 1;
        for (int i = SIGRTMAX - 1; i >= SIGRTMIN; i--) 
        {
            value.sival_int = order;
            order++;
            printf("Sending real-time signal %d\n", i);
            sigqueue(getppid(), i, value);
        }

        printf("\n\nSignals sent. Sleeping for 3 seconds to allow handling...\n");
        sleep(5);
        return 0;

    }
    for (;;)
    {
        pause();
    }
    return 0;
}