#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


/* Синтаксис: 
https://en.m.wikipedia.org/wiki/Exec_(system_call)#C_language_prototypes
int execle(char const *path, char const *arg0, ..., char const *envp[]);
    path: указывает на путь к исполняемому процессу
    argv: список аргументов 
    envp: это массив указателей на настройки окружения. Вызовы exec с именем, оканчивающимся на e, изменяют среду для нового образа процесса, передавая список параметров среды через аргумент envp.
*/

int main()
{
    //find / -name "ros" 2>/dev/null
    char* env[] = { NULL };

    int pid = fork();
    if (pid == 0)
    {
        execle("/bin/find", "find", "/home", "-name", "*.py", NULL, env);
    }

    system("ps xf > log.txt");
    printf("End from execle.c\n");

    return 0;
}