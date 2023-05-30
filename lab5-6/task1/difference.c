#include <sys/wait.h>
#include<stdio.h>
#include<signal.h>
#include<unistd.h>


void signal_handler(int signum) {
    printf("Received signal %d\n", signum);
}


int main() {
    pid_t pid;
    int status;

    pid = fork(); // создание дочернего процесса

    if (pid < 0) { // проверка на ошибку
        printf("Failed to create child process\n");
        return 1;
    }
    else if (pid == 0) { // обработка в дочернем процессе 
        signal(SIGINT, signal_handler);
        signal(SIGRTMIN, signal_handler);

        printf("Child process is running...\n");
        sleep(10); // дочерний процесс ждет 10 секунд
        printf("Child process is exiting...\n");
    }
    else { // обработка в родительском процессе
        sleep(2); // родительский процесс ждет 2 секунды
        int a=0;
        int b=0;
        printf("Sending signal %d to the child process...\n", SIGINT);
        while(a<5){
                kill(pid, SIGINT);
                a++;
        }
        printf("Sending signal %d to the child process...\n", SIGRTMIN);
        while(b<5){
                kill(pid, SIGRTMIN);
                b++;
        }
        wait(&status); // ожидание завершения дочернего процесса
        printf("Parent process is exiting...\n");
    }
    return 0;
}