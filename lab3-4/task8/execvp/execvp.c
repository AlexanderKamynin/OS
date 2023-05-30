#include <unistd.h>
#include <stdio.h>

/* Синтаксис: 
https://en.m.wikipedia.org/wiki/Exec_(system_call)#C_language_prototypes
int execvp (const char *file, char *const argv[]);
    файл:  указывает на имя файла, связанное с исполняемым файлом. 
    argv:  массив указателей на символы с нулевым завершением. 
*/

int main()
{
    char* args[] = {"./exec1", NULL};
    execvp(args[0], args);

    printf("End from execvp.c\n");

    return 0;
}