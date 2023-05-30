#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


/* Синтаксис: 
https://en.m.wikipedia.org/wiki/Exec_(system_call)#C_language_prototypes
int execv (const char *path, char *const argv[]);
    path:  указывает на путь к заменяемому процессу
    argv:  список аргументов
*/

int main()
{
    char* args[] = {"ls", "-l", "-h", "-a", NULL};
    
    int pid = fork();
    if (pid == 0)
    {
        execv("/bin/ls", args);
    }

    system("ps xf > log.txt");
    printf("End from execv.c\n");

    return 0;
}